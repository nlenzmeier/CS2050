#include "game.h"

int fight(Player* playerList, Hero* heroes, Boss* boss)
{
    if(!heroes || !boss || !playerList)
    {
        //No idea how'd I get here, but just in case.
        printf("ERROR: parameters to fightFxns\n");
        freePlayerList(playerList);
        return -1;
    }
    //utility pointer, to move down the list.
    //Just in case we need to get back to the top of the turn order.
    Player* currentActor = playerList;
    //will reference the list of decisions the boss is using for the applicable turns.
    //This will need to be reset once the list of decisions runs out. 
    bossDecision* bossStack = NULL;
    
    while(1)
    {
        //Shows everyone's health on the screen, in a fashion that's pretty. 
        printFightStatus(heroes, boss);
        //The user decides what all the heroes do next. 
        getDecisions(heroes);
        //run through the turn order. Fastest player goes first, all the way to the slowest player. 
        while(currentActor != NULL)
        {
            if(bossStack == NULL)
            {
                //if the boss needs a new set of decisions, that has to be found before
                //anything happens. Otherwise, it will just use what is already there.
                bossStack = getNewListInTree(boss->root, boss->health);
                if(!bossStack)
                {
                    freePlayerList(playerList);
                    printf("ERROR: boss stack is NULL!\n");
                    return -1;
                }
            }
            //If the player is the boss, do his actions.
            if(currentActor->boss != NULL)
            {
                //he'll attack a random hero, I guess.
                Hero* defender = &heroes[rand() % NUMHEROES];
                //make sure the guy he's attacking is alive.
                while(defender->health == 0)
                {
                    defender = &heroes[rand() % NUMHEROES];
                }
                //get next thing from the list of decisions
                boss->nextAction = bossStack->type;
                evaluateDecision(defender, boss, 1);
                //get the next decision prepped. 
                bossStack = bossStack->next;
            }
            //If the player is a hero, just do his action. There's only one boss for now,
            //so that hero will just be attacking him if he's attacking. 
            else
            {
                evaluateDecision(currentActor->hero, boss, 0);
            }
            //remove the player that was just done, and go to the next guy.
            currentActor = currentActor->next;
            free(playerList);
            playerList = currentActor;
        }
        //turn order was exhausted, so a new one has to be made.
        //As of this version, we technically could just use the same list over and over,
        //but if we wanted to have stat modifying actions later, we'd need a whole new list
        //each time. 
        currentActor = createNewPlayerList(heroes, boss);
        if(!currentActor)
        {
            printf("ERROR: turn order list creation failed.\n");
            return -1;
        }
        int check = 0;
        //checks to see if anyone is dead. If they are, they shouldn't be in the list. 
        playerList = resizeListAndCheckBoss(currentActor, &check);
        if(!playerList)
        {
            printf("ERROR: turn order list resizing failed.\n");
            return -1;
        }
        //the check was done above, sees if the boss is dead. If the boss is dead, game's over.
        if(check == 1)
        {
            //as of now, this is the only way to win the fight. 
            freePlayerList(playerList);
            return 0;
        }
        //reset this utility pointer. Just to be consistent. 
        currentActor = playerList;
        //checks to see how many players are left in the turn order once the dead ones 
        //are filtered out. 
        //I have literally no idea why Netbeans complains about this function. Yes, I declared it.
        if(countHeroesInFight(currentActor) < 1)
        {
            //if everyone's dead, game's over.
            freePlayerList(playerList);
            return 1;
        }
    }
    //I should never get here, but just in case...
    printf("ERROR: unexpected code execution\n");
    return -1;
}

Player* resizeListAndCheckBoss(Player* playerList, int* check)
{
    //go through the list similar to what is done in the fight function.
    Player* currentActor = playerList;
    Player* prev = playerList;
    while(currentActor != NULL)
    {
        //if the player is a boss
        if(currentActor->boss != NULL)
        {
            if(currentActor->boss->health <= 0)
            {
                //if the boss is dead, game over. 
                //freePlayerList(playerList);
                *check = 1;
                return playerList;
            }
            prev = currentActor;
            currentActor = currentActor->next;
        }
        else
        {
            //check for a dead hero.
            if(currentActor->hero->health <= 0)
            {
                //finds out where the hero is in the list, and repairs the list accordingly.
                if(currentActor == playerList)
                {
                    playerList = playerList->next;
                    free(currentActor);
                    prev = playerList;
                    currentActor = playerList;
                }
                else if(currentActor->next == NULL)
                {
                    prev->next = NULL;
                    free(currentActor);
                    break;
                }
                else
                {
                    prev->next = currentActor->next;
                    free(currentActor);
                    currentActor = prev->next;
                }
            }
            else
            {
                //if hero isn't dead, move to next one.
                prev = currentActor;
                currentActor = currentActor->next;
            }
        }
    }
    //return the newly updated list of all players that are alive. 
    return playerList;
}

int countHeroesInFight(Player* list)
{
    if (list == NULL){
        return 0;
    }
    if (list->hero != NULL){
        return 1 + countHeroesInFight(list->next);
    }
    else {
        return countHeroesInFight(list->next);
    }
}

//This is a recursive function that counts the number of heroes
int compareHeroes(const void* obj1, const void* obj2){
    Hero* a = (Hero*)obj1;
    Hero* b = (Hero*)obj2;
    
    return a->speed - b->speed;
}

Player* createNewPlayerList(Hero* heroes, Boss* boss)
{
    qsort(heroes, 3, sizeof(Hero),compareHeroes);
    Player* queue = NULL;
    int i = 0;
    int bossAvailable = 1;
    while (i< 3){
       Player* node = malloc(sizeof(Player));
       if (heroes[i].speed < boss->speed || bossAvailable == 0){
           node->hero = &heroes[i++];
           node->boss=NULL;
       }
       else {
           node->hero = NULL;
           node->boss = boss;
           bossAvailable = 0;
       }
       node->next = queue;
       queue = node;  
    }
    return queue;
    
//    My practice work:    
//    Player* p1 = malloc(sizeof(Player));
//    p1->hero = &heroes[0];
//    Player* p2 = malloc(sizeof(Player));
//    p2->hero = &heroes[1];
//    Player* p3 = malloc(sizeof(Player)); 
//    p3->hero = &heroes[2];
//    Player* b = malloc(sizeof(Player));
//    b->boss = boss;
//    
//    //sort them or add fastest to the Q, then 2nd farthest, etc
//    
//    int pass;
//    int j, i;
//    Hero tmp;
//    int x = 0;
//    
//    for (i = 0; i < 3; i++){
//        for (j = 0; j< 1; j++){
//            if (heroes[i].speed > heroes[j].speed){
//                tmp = heroes[j];
//                heroes[j] = heroes[i];
//                heroes[i] = tmp;
//            }
//        }
//    }
//    
//    for (i = 0; i> 3; i++){
//        if (boss->speed > heroes[i].speed){
//            x++;
//        }
//    }
//    
//    if (x == 0){
//        b->next=p1;
//        p1->next=p2;
//        p2->next=p3;
//        p3->next=NULL;
//        
//        return b;
//    }
//    
//    if (x == 1){
//        p1->next=b;
//        b->next=p2;
//        p2->next=p3;
//        p3->next=NULL;
//        
//        return p1;
//    }
//    
//    if (x == 2){
//        p2->next=b;
//        p1->next=p2;
//        b->next=p3;
//        p3->next=NULL;
//        
//        return p2;
//    }
//    
//    if (x == 3){
//        p3->next=b;
//        p1->next=p3;
//        p2->next=p1;
//        b->next=NULL;
//        
//        return p3;
//    }
    
//    What David had:
//    int i=0,j=0,x=0;   //counters
//    Player* p0=NULL;    //initialize pointers for the hero and boss
//    //Player* p1=NULL;
//    //Player* p2=NULL;
//    //Player* p3=NULL;
//    Hero array[3];
//    array[0]=heroes[0];
//    array[1]=heroes[1];
//    array[2]=heroes[2];
//    
//    Hero* tmp=NULL; //use for bubble sort
//    for(i=0;i<3;i++)
//    {
//        for(j=0;j<3-i;j++)
//        {
//            if(heroes[j].speed>heroes[j+1].speed)
//            {
//                tmp=&array[j];
//                array[j]=array[j+1];
//                array[j+1]=*tmp;
//            }
//                
//        }
//    }
//    
//    int bossFlag = 0;
//    i = 0;
//    Player* curr=malloc(sizeof(Player));
//    p0=curr;
//    while(i < 3){
//        curr->next = malloc(sizeof(Player));
//        curr=curr->next;
//        if(array[i].speed < boss->speed && bossFlag == 0)
//        {
//            curr->boss=boss;
//            bossFlag = 1;
//            curr->next=NULL;
//        }
//        else{
//            curr->hero=&array[i];
//            //Insert hero as next player
//            i++;
//            curr->next=NULL;
//        }
//    }
//    
//    if(bossFlag == 0)
//    {
//        curr->next=malloc(sizeof(Player));
//        curr->next->boss=boss;
//        curr->next->next=NULL;
//        //Insert boss as next player
//    }
//    return p0;
    
}

void printFightStatus(Hero* heroes, Boss* boss)
{
    int i;
    for(i = 0; i < 3; i++)
    {
        printf("--------%s----------", heroes[i].name);
        if(i == 1)
        {
            printf("\t\t\t\t--------%s----------\n", boss->name);
        }
        else
        {
            printf("\n");
        }
        printf("\t%d/%d", heroes[i].health, heroes[i].maxHealth);
        if(i == 1)
        {
            printf("\t\t\t\t\t%d/%d\n", boss->health, boss->maxHealth);
        }
        else
        {
            printf("\n");
        }
    }
}

void getDecisions(Hero* heroes)
{
    printf("\n\n");
    int i = 0;
    for(i; i < 3; i++)
    {
        if(heroes[i].health > 0)
        {
            printf("Choose your action for %s: \n", heroes[i].name);
            printf("0: Attack\n1: Defend\n2: Heal\n");
            printf(">");
            int choice; 
            scanf("%d", &choice);
            while(0 > choice || choice > 2)
            {
                printf("Invalid choice. Try again: \n");
                printf(">");
                scanf("%d", &choice);
            }
            heroes[i].decision = choice;
        }
    }
}

void evaluateDecision(Hero* hero, Boss* boss, int takingAction)
{
    if (takingAction == 0){
        
        if (hero->decision == DEFEND){
            return;
        }
        if (hero->decision == HEAL){
            if (hero->hasHealed == 0){
                hero->health = hero->maxHealth;
                hero->hasHealed = 1;
            }
            else if(hero->hasHealed == 1){
                int rand_num = rand()%(200 - 50 + 1) + 50;
                if (hero->health + rand_num > 200){
                    hero->health = 200;
                }
                else {
                    hero->health += rand_num;
                }
            }
        }
        if (hero->decision == ATTACK && boss->nextAction == DEFEND){
            boss->health -= ((hero->attack + hero->sword->damage) * 0.3 - boss->defense); 
        }
        else if (hero->decision == ATTACK && boss->nextAction != DEFEND){
            boss->health -= hero->attack + hero->sword->damage + 50 - boss->defense;
        }
    }
    
    if (takingAction == 1){

        if (boss->nextAction == HEAL){
            int heal = rand()%(150 - 50 + 1) + 50;
            if (boss->health + heal > 200){
                boss->health = 200;
            }
            else{
                boss->health += heal;
            }
        }

        if (boss->nextAction == DEFEND){
            return;
        }
        if (boss->nextAction == ATTACK && hero->decision == DEFEND){
            hero->health -= ((hero->defense + hero->shield->defense) * 0.3) - boss->attack;
        }
        else if (boss->nextAction == ATTACK && hero->decision != DEFEND){
            hero->health -= boss->attack * 1.5;
        }
    }
}