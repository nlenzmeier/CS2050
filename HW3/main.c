/* 
 * File:   main.c
 * Author: Nicolle Lenzmeier
 * NALYV2
 * HW3
 *
 * Created on November 15, 2015, 10:32 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"

int main(int argc, char** argv) {
    //there will be random stuff later!
    srand(time(NULL));
    Player* playerStack = NULL;
    Hero* heroes = NULL;
    Boss* boss = NULL;
    importDataAndMakeActorOrder(&playerStack, &heroes, &boss);
    //could have done a return value for importData, but I think this works too.
    if(!heroes || !boss || !playerStack)
    {
        //here we might have a playerList, but I don't think so. Will do just in case.
        printf("ERROR: import did not work correctly.\n");
        freePlayerList(playerStack);
        freeMemory(heroes, boss);
        return (EXIT_FAILURE);
    }
    
    //Heavy lifting function. 
    int result = fight(playerStack, heroes, boss);
    if(result == 1)
    {
        printf("The boss won! Game over.\n");
    }
    else if(result == -1)
    {
        //do more here? idk. 
        printf("An error occurred. Please check the source code for more details.\n");
    }
    else
    {
        printf("You won! Congratulations!\n");
    }
    freeMemory(heroes, boss);
    return (EXIT_SUCCESS);
}

void importDataAndMakeActorOrder(Player** playerStack, Hero** heroes, Boss** boss)
{
    FILE* bossFile = fopen("bossInfo.txt", "r");
    FILE* heroesFile = fopen("heroes.txt", "r");
    FILE* itemsFile = fopen("EquippedItems.txt", "r");
    if(!bossFile || !heroesFile || !itemsFile)
    {
        printf("ERROR: a file did not open correctly.\n");
        return;
    }
    
    //This is all for loading bosses.
    int numBosses = 1;
    bossDecisionNode* node;
    bossDecision* subNode;
    *boss = malloc(sizeof(Boss));
    int i;
    //technically, I should accommodate for more than one enemy in a given boss fight, 
    //which is what the for loop is for, but for our purposes I don't need it. The rest of the code
    //just assumes there's only one boss, which would need to be changed accordingly.
    for(i = 0; i < numBosses; i++)
    {
        //get the actual boss name and stats
        if(fscanf(bossFile, "%s", (*boss)[i].name) != 1)
        {
            //conveniently, freeing is taken care of in main, so I only have to free
            //temporary stuff made in this fxn when applicable.
            printf("ERROR: did not read boss name.\n");
            return;
        }
        if(fscanf(bossFile, "%d %d %d %d %d", 
                &((*boss)[i].health), &((*boss)[i].defense), &((*boss)[i].speed),
                &((*boss)[i].attack), &((*boss)[i].luck)) != 5)
        {
            printf("ERROR: boss stats not read in.\n");
            return;
        }
        //for other bosses, make separate files. For now, we'll just use this boss. 
        
        //maxHealth is made so that the boss can't heal up to higher than his max. 
        (*boss)[i].maxHealth = (*boss)[i].health;
        int counter = 0;
        while(!feof(bossFile))
        {
        	if(counter == 56)
        	{
        		break;
        	}
            //read in all of the decisions for the boss. The structure is as follows:
            //Node
            //  ...
            //  ->topOfStack
            //      ->decision->decision->...
            node = malloc(sizeof(bossDecisionNode));
            if(fscanf(bossFile, "%d %d", &(node->healthMin), &(node->healthMax)) != 2)
            {
                printf("ERROR: node health range was not read in\n");
                free(node);
                return;
            }
            node->leftNode = NULL;
            node->rightNode = NULL;
            node->topOfStack = NULL;
            int j;
            if(fscanf(bossFile, "%d", &j) != 1)
            {
                printf("ERROR: number of decisions for node not read in.\n");
                free(node);
                return;
            }
            //Netbeans plz
            int k;
            for(k = j; k > 0; k--)
            {
                if(k > 0)
                {
                    
                }
                //puts together the stack of decisions, where each decision is read separately.
                subNode = malloc(sizeof(bossDecisionNode));
                subNode->next = NULL;
                if(fscanf(bossFile, "%d", (int*)&(subNode->type)) != 1)
                {
                    printf("ERROR: decision not read in.\n");
                    free(subNode);
                    //That's annoying. Will be lazy and not put it in a fxn.
                    bossDecision* next = node->topOfStack;
                    while(node->topOfStack)
                    {
                        next = node->topOfStack->next;
                        free(node->topOfStack);
                        node->topOfStack = next;
                    }
                    free(node);
                    return;
                }
                //takes the subnode, which is a decision, and adds it to the list of decisions.
                node->topOfStack = addDecisionNodeToList(node->topOfStack, subNode);
                if(!node->topOfStack)
                {
                    printf("ERROR: decision not added to stack.\n");
                    bossDecision* next = node->topOfStack;
                    while(node->topOfStack)
                    {
                        next = node->topOfStack->next;
                        free(node->topOfStack);
                        node->topOfStack = next;
                    }
                    free(node);
                    return;
                }
            }
            //when the stack is made, the node with that stack is added to the tree.
            //Tree is as follows:
            //                         Node
            //                 healthmin, health max
            //          Node                        Node
            //  healthmin, healthmax        healthmin, healthmax
            //  ...                                     ...
            //where each node has a range of values for which that node applies.
            (*boss)[i].root = addNodeToDecisionTree((*boss)[i].root, node);
            if(!(*boss)[i].root)
            {
                printf("ERROR: node not added to boss decision tree, or the root is corrupted.\n");
                bossDecision* next = node->topOfStack;
                while(node->topOfStack)
                {
                    next = node->topOfStack->next;
                    free(node->topOfStack);
                    node->topOfStack = next;
                }
                free(node);
                return;
            }
            counter++;
        }
    }
    
    //boss import done. Now for the heroes. 
    
    *heroes = malloc(sizeof(Hero)*3);
    for(i = 0; i < 3; i++)
    {
        //each hero will have a sword and shield that comes with it.
        if(fscanf(heroesFile, "%s | %d | %d | %d | %d | %d", 
                (*heroes)[i].name,&((*heroes)[i].health),&((*heroes)[i].defense)
                ,&((*heroes)[i].speed),&((*heroes)[i].attack),(&(*heroes)[i].luck)) != 6)
        {
            printf("ERROR: hero %d not read in correctly.\n", i);
            return;
        }
        (*heroes)[i].shield = NULL;
        (*heroes)[i].sword = NULL;
        (*heroes)[i].shield = malloc(sizeof(Shield));
        (*heroes)[i].sword = malloc(sizeof(Sword));
        if(!(*heroes)[i].shield || !(*heroes)[i].sword)
        {
            //it appears that malloc can be checked for NULL on the return, but not sure.
            printf("ERROR: the sword and shield for hero %d not malloced.\n", i);
            return;
        }
        if(fscanf(itemsFile, "%s | %d | %d | %d", ((*heroes)[i].shield)->name,
                &(((*heroes)[i].shield)->price), &(((*heroes)[i].shield)->defense),
                &(((*heroes)[i].shield)->weight)) != 4)
        {
            printf("ERROR: shield info for hero %d not read in.\n", i);
            return;
        }
        if(fscanf(itemsFile, "%s | %d | %d", ((*heroes)[i].sword)->name,
                &(((*heroes)[i].sword)->price), &(((*heroes)[i].sword)->damage)) != 3)
        {
            printf("ERROR: sword info for hero %d not read in.\n", i);
            return;
        }
        (*heroes)[i].maxHealth = (*heroes)[i].health;
    }
    
    //creates the stack of players for turn 1 in the fight. The stacks that are made 
    //are based off of the players' speeds, where the fastest player goes first. 
    *playerStack = createNewPlayerList(*heroes, *boss);
    if(!(*playerStack))
    {
        printf("ERROR: Player Stack not initialized!\n");
    }
    //don't have to error check this. That's already technically done in main.
}

void freeMemory(Hero* heroes, Boss* boss)
{
    //technically only frees the heroes and boss, but everything else should be freed
    //by this point.
    if(heroes)
    {
        int i = 0;
        for(i = 0; i < 3; i++)
        {
            free(heroes[i].sword);
            free(heroes[i].shield);
        }
        free(heroes);
    }
    if(boss)
    {
        freeTree(boss->root);
        free(boss);
    }
}

void freeTree(bossDecisionNode* root)
{
    if (root == NULL){
        return;
    }
    freeTree(root->leftNode);
    freeTree(root->rightNode);
    freeList(root->topOfStack);
    free(root);
}

void freePlayerList(Player* playerList)
{
    //frees the list for the turn order in case there is one. For the purpose of various places where 
    //error checking occurs. 
    //NOTE: does not free the stuff in players, that is done in freeMemory.
    Player* tmp = playerList;
    while(playerList)
    {
        tmp = playerList->next;
        free(playerList);
        playerList = tmp;
    }
}

void freeList(bossDecisionNode* root){
    bossDecision* prev = root->topOfStack;
    bossDecision* curr = root->topOfStack;
    while (curr != NULL){
        curr = curr->next;
        free(prev);
        prev = prev->next;
    }
}