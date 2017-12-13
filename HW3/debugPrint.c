#include "game.h"

//Prints out all the hero data to make sure everything was imported correctly. 
void printHeroes(Hero* heroes)
{
    int i;
    for(i = 0; i < 3; i++)
    {
        printf("%d: %s\n\tHealth: %dhp\n\tAttack: %d\n\tDefense: %d\n\tSpeed: %d\n\tLuck: %d\n", 
            i, heroes[i].name, heroes[i].health, heroes[i].attack, 
            heroes[i].defense, heroes[i].speed, heroes[i].luck);
        printf("Items for %s\n", heroes[i].name);
        if(heroes[i].shield != NULL)
        {
            printf("\tShield: %s\n\tPrice: %d\tDefense: %d\tWeight: %dkg\n",
                heroes[i].shield->name, heroes[i].shield->price, 
                heroes[i].shield->defense, heroes[i].shield->weight);
        }
        else
        {
            printf("\tShield: None\n");
        }
        if(heroes[i].sword != NULL)
        {
            printf("\tSword:\n\t%s\n\tPrice: %d\tDamage: %d\n",
                heroes[i].sword->name, heroes[i].sword->price, 
                heroes[i].sword->damage);
        }
        else
        {
            printf("\tSword: None\n");
        }
    }
}

//Prints out the boss and his decisions, to make sure they were imported correctly.
void printBoss(Boss* boss)
{
    printf("Name: %s\n\tHealth: %d\n\tDefense: %d\n\tSpeed: %d\n\tAttack: %d\n\tLuck: %d\n",
        boss->name, boss->health, boss->defense, boss->speed, boss->attack, boss->luck);
    bossDecisionNode* root = boss->root;
    inorderPrint(root);
}

//Prints out all decisions for each node in the decision tree, using inorder traversal. 
//Because it's inorder, it will print out the decisions for the health range of 0-X first, then the 
//decisions for (X+1)-(Y), then (Y+1)-Z, etc, all the way to (A)-(Full health)
//Very useful function! I would highly recommend using this.
void inorderPrint(bossDecisionNode* root)
{
    if(root)
    {
        inorderPrint(root->leftNode);
        printf("---------NODE----------\n");
        printf("Min health: %d\nMax health: %d\n", root->healthMin, root->healthMax);
        printf("Decisions: ");
        bossDecision* tmp = root->topOfStack;
        while(tmp)
        {
            switch(tmp->type)
            {
                case 0:
                    printf("Attack->");
                    break;
                case 1:
                    printf("Defend->");
                    break;
                case 2:
                    printf("Heal->");
                    break;
                default:
                    printf("ERROR->");
                    break;
            }
            tmp = tmp->next;
        }
        printf("New stack\n");
        inorderPrint(root->rightNode);
    }
}

//Makes sure the player list for the turn order was created correctly.
//Also very useful! Highly recommend you use.
void printPlayerList(Player* playerList)
{
    Player* tmp = playerList;
    while(tmp)
    {
        if(tmp->boss)
        {
            printf("%s->", tmp->boss->name);
        }
        else
        {
            printf("%s->", tmp->hero->name);
        }
        tmp = tmp->next;
    }
    printf("End\n");
}

//Make sure the decisions for each hero was read in correctly from the user.
void printDecisions(Hero* heroes)
{
    int i;
    for(i = 0; i < 3; i++)
    {
        printf("%s choice: ", heroes[i].name);
        switch(heroes[i].decision)
        {
            case 0:
                printf("Attack\n");
                break;
            case 1:
                printf("Defend\n");
                break;
            case 2:
                printf("Heal\n");
                break;
            default:
                printf("ERROR\n");
        }
    }
}