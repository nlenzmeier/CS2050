/* 
 * File:   main.c
 * Author: Nicolle Lenzmeier
 * LAB F
 * Pawprint: NALYV2
 * Homework 1
 * Created on September 3, 2015, 8:51 AM
 */

#include <stdio.h>
#include <stdlib.h>

//All of the structures used
typedef struct category
{
    char name[20];
    int numInCategory;
} Category;

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
    int weight;
} Sword;

typedef struct footwear
{
    char name[50];
    int price;
    int defense;
    int weight;
} Footwear;

typedef struct headgear
{
    char name[50];
    int price;
    int defense;
    int weight;
} Headgear;

typedef struct hero
{
    char name[30];
    int health;
    int defense;
    int speed;
    int attack;
    int luck;
} Hero;


//Prototypes
void mainMenu();
void highScores();
void newGame();
void processHeroes();
void weaponSelection();
void shieldSelection(Shield* shields, int numShields);
void swordSelection(Sword* swords, int numSwords);
void footwearSelection(Footwear* footwear, int numFootwear);
void headgearSelection(Headgear* headgear, int numHeadgear);

//Allows the other functions to connect together (also what comes up on our screen)
int main(int argc, char** argv) {
    mainMenu();
 
    return (EXIT_SUCCESS);
}

//Displays the menu of options you are allowed to use for the game
void mainMenu(){
    int option;
    while (1) {
        printf("Welcome! Please select an option:");
        printf("\n\n1. New Game ");
        printf("\n\n2. High Scores ");
        printf("\n\n3. Exit Game\n\n");
        scanf("%d", &option);
        if (option >= 1 && option <= 3){
            break;
        } 
        printf("\nInvalid selection. Try again.");
    }
    switch (option){
        case 1:
            newGame();
            break;
        case 2:
            highScores();
            break;
        case 3:
            printf("Exiting the game.");
            return;
    }
}
    

//Displays the high scores. We pull in a text file and load it to our main screen
void highScores(){
    printf("Username: Scores:\n");
    FILE*fp = fopen("highScores.txt", "r");
    if (fp == NULL){
        printf("Failed to open the file\n");
        return;
    }
    
    char username[10];
    int score = 0;
    while(1){
        fscanf(fp, "%s %d", username, &score);
        printf("%s %d\n", username, score);
        if(feof(fp)){
            break;
        }
    }
    
    fclose(fp);
    printf("\n");
    mainMenu();
}

//when the user types option 1, they are brought here. This creates the game and asks for the user's name
void newGame(){
    char name[20];
    printf("\n\n\nWhat is your name?  \n\n", name);
    scanf("%s", name);
    printf("\n\nHello %s. Welcome to the gauntlet.\n\n\n", name);
    printf("Hero Data:\n\n");
    
    FILE*fp=fopen("userInfo.txt", "w");
    if(fp==NULL){
        printf("Could not open the heroes data file");
        return;
    }
    fprintf(fp, "%s\n", name);
    
    fclose(fp);
    processHeroes();
}

//takes a binary text file and converts it to English for the user to see their hero options. 
//Then they are able to select their top three choices.This is later then stored in a newly created file for the program to reference later
void processHeroes(){
    FILE*fp=fopen("HeroesFile.txt", "r");
    if(fp==NULL){
        printf("Could not open the heroes data file");
        return;
    }
    
    printf("\n\nHero Data:\n");
    Hero heroes[5];
    int i=0;
    fread(heroes, sizeof(Hero),5,fp);
    for(i=0; i<5; i++){
        printf("\n%s"
            "\nHealth: %dhp"
            "\nAttack: %d"
            "\nDefense: %d"
            "\nSpeed: %d"
            "\nLuck: %d\n\n", heroes[i].name, heroes[i].health, heroes[i].attack,heroes[i].defense, heroes[i].speed, heroes[i].luck);
    }
    
    int champ1=0, champ2=0, champ3=0;
    
    printf("\n\nChoose the first hero you wish to add to your team (1-5): ");
    scanf("%d", &champ1);;
    while(champ1<1||champ1>5){
        printf("\nIncorrect choice. Choose again: ");
        scanf("%d", &champ1);
    }
    printf("\nExcellent choice! Choose again: ");
    scanf("%d", &champ2);
    while(champ2<1||champ2>5||champ2==champ1){
        printf("\nIncorrect choice. Choose again: ");
        scanf("%d", &champ2);
    }
    printf("\nExcellent choice! Choose again: ");
    scanf("%d", &champ3);
    while(champ3<1||champ3>5||champ3==champ1||champ3==champ2){
        printf("\nIncorrect choice. Choose again: ");
        scanf("%d", &champ3);
    }
    printf("\n\nHero choices saved successfully.");
    
    FILE*phero=fopen("champselection.txt", "wb");
    if(phero==NULL){
        printf("Could not open file.");
        return;
    }
     fprintf(phero, "%s %d %d %d %d %d\n", heroes[champ1-1].name, heroes[champ1-1].health, heroes[champ1-1].attack, heroes[champ1-1].defense, heroes[champ1-1].speed, heroes[champ1-1].luck);
     fprintf(phero, "%s %d %d %d %d %d\n", heroes[champ2-1].name, heroes[champ2-1].health, heroes[champ2-1].attack, heroes[champ2-1].defense, heroes[champ2-1].speed, heroes[champ2-1].luck);
     fprintf(phero, "%s %d %d %d %d %d\n", heroes[champ3-1].name, heroes[champ3-1].health, heroes[champ3-1].attack, heroes[champ3-1].defense, heroes[champ3-1].speed, heroes[champ3-1].luck);

     fclose(phero);
     fclose(fp);
     weaponSelection();
     return;
}
///BECAUSE I HAD NO FREAKING HOW TO DO THIS, THIS IS MY EXTRA, POINTLESS WORK. ENJOY.
    //I WORK HARD GOSH DARN IT!
//   
//    
//    Hero Calen;
//    int check=0;
//    check=fread(&Calen,sizeof(Hero),1,fp);
//    if(check==0){
//        printf("Failed to open file.\n");
//        return;
//    }
//    printf("\n%s"
//            "\nHealth: %dhp"
//            "\nAttack: %d"
//            "\nDefense: %d"
//            "\nSpeed: %d"
//            "\nLuck: %d\n", Calen.name, Calen.health, Calen.attack, Calen.defense, Calen.speed, Calen.luck);
//    
//    Hero Roc;
//    check=fread(&Roc,sizeof(Hero),1,fp);
//    if(check==0){
//        printf("\nFailed to read file.\n");
//        return;
//    }
//    printf("\n%s"
//            "\nHealth: %dhp"
//            "\nAttack: %d"
//            "\nDefense: %d"
//            "\nSpeed: %d"
//            "\nLuck:%d\n", Roc.name, Roc.health, Roc.attack, Roc.defense, Roc.speed, Roc.luck);
//    
//    Hero Brennor;
//    check=fread(&Brennor,sizeof(Hero),1,fp);
//    if(check==0){
//        printf("\nFailed to read file.\n");
//        return;
//    }
//    printf("\n%s\nHealth: %dhp\nAttack: %d\nDefense: %d\nSpeed: %d\nLuck:%d\n", Brennor.name, Brennor.health, Brennor.attack, Brennor.defense, Brennor.speed, Brennor.luck);
//    
//    Hero Uldreiyn;
//    check=fread(&Uldreiyn,sizeof(Hero),1,fp);
//    if(check==0){
//        printf("\nFailed to read file.\n");
//        return;
//    }
//    printf("\n%s\nHealth: %dhp\nAttack: %d\nDefense: %d\nSpeed: %d\nLuck:%d\n", Uldreiyn.name, Uldreiyn.health, Uldreiyn.attack, Uldreiyn.defense, Uldreiyn.speed, Uldreiyn.luck);
//    
//    Hero Thane;
//    check=fread(&Thane,sizeof(Hero),1,fp);
//    if(check==0){
//        printf("\nFailed to read file.\n");
//        return;
//    }
//    printf("\n%s\nHealth: %dhp\nAttack: %d\nDefense: %d\nSpeed: %d\nLuck:%d\n", Thane.name, Thane.health, Thane.attack, Thane.defense, Thane.speed, Thane.luck);
//    
//   
//    
//    int champ1=0, champ2=0, champ3=0;
//    printf("\n\nChoose the first hero you wish to add to your team (1-5): ");
//    scanf("%d", &champ1);;
//    while(champ1<1||champ1>6){
//        printf("\nIncorrect choice. Choose again: ");
//        scanf("%d", &champ1);
//    }
//    printf("\nExcellent choice! Choose again: ");
//    scanf("%d", &champ2);
//    while(champ2<1||champ2>6||champ2==champ1){
//        printf("\nIncorrect choice. Choose again: ");
//        scanf("%d", &champ2);
//    }
//    printf("\nExcellent choice! Choose again: ");
//    scanf("%d", &champ3);
//    while(champ3<1||champ3>6||champ3==champ1||champ3==champ2){
//        printf("\nIncorrect choice. Choose again: ");
//        scanf("%d", &champ3);
//    }
//    printf("\n\nHero choices saved successfully.");
//    
//    
//    FILE*phero=fopen("champselection.txt", "w");
//    if(phero==NULL){
//        printf("Could not open the heroes data file");
//        return;
//    }
//    fprintf(phero, "%d %d %d\n", champ1, champ2, champ3);
//            
//            
//    fclose(fp);
//    fclose(phero)

//Displays a category menu for which the user can decide what weapons they would like to view. This will then take them to the functions below
void weaponSelection(){
    FILE*fp=fopen("CategoryList.txt", "r");
     if (fp == NULL){
        printf("Failed to open the file\n");
        return;
    }
    Shield *shields=malloc(sizeof(struct shield));
    Sword*sword=malloc(sizeof(struct sword));
    Footwear*foot=malloc(sizeof(struct footwear));
    Headgear*hg=malloc(sizeof(struct headgear));
    
    
    
    printf("\nSelect a category to see its items:");
    
    Category selection[4];
    int i=0;
    fread(selection, sizeof(Category), 4, fp);
    for (i=0; i<4;i++){
        printf("\n%d: %s", i, selection[i].name);
    }
    int sldnum = selection[0].numInCategory;
    
    printf("\n4: Quit");
    
    int option;
    printf("\n\nOption:");
    scanf("%d", &option);
    if(option < 0 || option > 4){
        printf("Invalid choice. Try again:");
        scanf("%d", &option);
    }
    if(option == 0){
        shieldSelection(shields, selection[0].numInCategory);
    }
    if(option == 1){
        swordSelection(sword, selection[1].numInCategory);
    }
    if(option == 2){
        footwearSelection(foot, selection[2].numInCategory);
    }
    if(option == 3){
        headgearSelection(hg, selection[3].numInCategory);
    }
    if(option == 4){
        mainMenu();
    }
}

//Displays the whole binary text file in English, allowing the user to see what shields are available
//Returns back to WeaponSelection afterwards. 
void shieldSelection(Shield* shields, int numShields){
    FILE*sldptr=fopen("ItemsFile.txt", "rb+");
    if(sldptr==NULL){
        printf("Could not open the file");
    }
    else{
    printf("\n\nItem Data:\n\n");
    
    int i;
    for(i=0; i<numShields; i++){
        fread(shields, sizeof(struct shield), 1,sldptr);
        printf("%s \nPrice: $%d \nMultiplier: %d \nWeight: %dkg\n", shields->name, shields->price, shields->defense, shields->weight);
        }
    }
    printf("\n\n\n");
    fclose(sldptr);
    weaponSelection();
}

//Displays the whole binary text file in English, allowing the user to see what swords are available
//Returns back to WeaponSelection afterwards.
void swordSelection(Sword* swords, int numSwords){
    FILE*ptr=fopen("ItemsFile.txt", "rb+");
    if(ptr==NULL){
        printf("Could not open the file");
    }
    else{
        printf("\n\nItem Data:\n\n");
    }
   
    int i;
    fseek(ptr, 8*sizeof(struct sword), SEEK_SET);
    for(i=0; i< numSwords; i++){
       fread(swords, sizeof(struct sword), 1, ptr);
       printf("%s \nPrice: $%d \nMultiplier: %d \nWeight: %dkg\n", swords->name, swords->price, swords->damage, swords->weight);
    }
    printf("\n\n\n");
    fclose(ptr);
    weaponSelection();
}

//Displays the whole binary text file in English, allowing the user to see what footwear is available
//Returns back to WeaponSelection afterwards.
void footwearSelection(Footwear* footwear, int numFootwear){
    FILE*ftp=fopen("ItemsFile.txt", "rb+");
    if(ftp==NULL){
        printf("Could not open the file");
    }
    else{
        printf("\n\nItem Data:\n\n");
    }
    
    int i;
    fseek(ftp, 18*sizeof(struct footwear), SEEK_SET);
    for(i=0; i<numFootwear; i++){
        fread(footwear, sizeof(struct footwear), 1, ftp);
        printf("%s \nPrice: $%d \nMultiplier: %d \nWeight: %dkg\n", footwear->name, footwear->price, footwear->defense, footwear->weight);
    }
    printf("\n\n\n");
    fclose(ftp);
    weaponSelection();
}

//Displays the whole binary text file in English, allowing the user to see what headgear is available.
//Returns back to WeaponSelection afterwards.
void headgearSelection(Headgear* headgear, int numHeadgear){
    FILE*hgp=fopen("ItemsFile.txt", "rb+");
    if(hgp==NULL){
        printf("Could not open the file");
    }
    else{
        printf("\n\nItem Data:\n\n");
    }
    
    int i;
    fseek(hgp, 23*sizeof(struct headgear), SEEK_SET);
    for(i=0; i<numHeadgear; i++){
        fread(headgear, sizeof(struct headgear), 1, hgp);
        printf("%s \nPrice: $%d \nMultiplier: %d \nWeight: %dkg\n", headgear->name, headgear->price, headgear->defense, headgear->weight);
    }
    printf("\n\n\n");
    fclose(hgp);
    weaponSelection();
}