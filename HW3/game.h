
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NUMHEROES 3

typedef enum type
{
    ATTACK,
    DEFEND,
    HEAL
} decisionType;

typedef struct bossDecision_
{
    decisionType type;
    struct bossDecision_* next;
} bossDecision;

typedef struct bossDecisionNode_
{
    struct bossDecisionNode_* leftNode;
    struct bossDecisionNode_* rightNode;
    int healthMin;
    int healthMax;
    bossDecision* topOfStack;
} bossDecisionNode;

typedef struct shield
{
    char name[50];
    int price;
    int defense;
    int weight;
} Shield;

typedef struct sword
{
    char name[50];
    int price;
    int damage;
} Sword;

typedef struct hero
{
    char name[30];
    int health;
    int maxHealth;
    int defense;
    int speed;
    int attack;
    int luck;
    decisionType decision;
    Shield* shield;
    Sword* sword;
    //can only heal fully once, so false means hero heals for a fraction
    bool hasHealed;
} Hero;

typedef struct boss
{
    char name[30];
    int health;
    int maxHealth;
    int defense;
    int speed;
    int attack;
    int luck;
    bossDecisionNode* root;
    decisionType nextAction; 
} Boss;

typedef struct players
{
    Hero* hero;
    Boss* boss;
    struct players* next;
} Player;

void importDataAndMakeActorOrder(Player** playerStack, Hero** heroes, Boss** boss);
bossDecision* addDecisionNodeToList(bossDecision* top, bossDecision* newTop);
bossDecisionNode* addNodeToDecisionTree(bossDecisionNode* root, bossDecisionNode* newNode);


int countHeroesInFight(Player* list);

void freeMemory(Hero* heroes, Boss* boss);
void freeTree(bossDecisionNode* root);
void freePlayerList(Player* playerList);
void freeList(bossDecisionNode* root);

int fight(Player* playerList, Hero* heroes, Boss* boss);
void getDecisions(Hero* heroes);
void evaluateDecision(Hero* hero, Boss* boss, int takingAction);
bossDecision* getNewListInTree(bossDecisionNode* root, int currentBossHealth);
Player* createNewPlayerList(Hero*, Boss*);
Player* resizeListAndCheckBoss(Player* playerList, int* check);
void printFightStatus(Hero* heroes, Boss* boss);

void printHeroes(Hero* heroes);
void printBoss(Boss* boss);
void inorderPrint(bossDecisionNode* root);
void printPlayerList(Player* playerList);
void printDecisions(Hero* heroes);
/*
 * 
 */