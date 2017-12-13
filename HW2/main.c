/* HOMEWORK 2
 * File:   main.c
 * Author: Nicolle Lenzmeier
 * NALYV2
 * Lab F
 *
 * Created on October 16, 2015, 12:47 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct shield
{
    char name[50];
    int price;
    int defense;
    int weight;
    struct shield* nextShield;
} Shield;
typedef struct sword
{
    char name[50];
    int price;
    int damage;
    struct sword* nextSword;
} Sword;

typedef struct hero
{
    char name[30];
    int health;
    int defense;
    int speed;
    int attack;
    int luck;
    Shield* shield;
    Sword* sword;
} Hero;

typedef enum print_option
{
    SHIELDS,
    SWORDS,
    ALL
} print_option;

typedef struct category
{
    char name[20];
    int numInCategory;
} Category;


void Shop(Hero*);
Hero* getHeroes(void);
void printHeroes(Hero*, print_option);
void shieldSelection(Shield**, Hero*, int*);
void swordSelection(Sword**, Hero*, int*);
void printShields(Shield*);
void printSwords(Sword*);
Shield* readShields(FILE*, int*);
Sword* readSwords(FILE*, int*);
Shield* extractShieldFromList(Shield**, int);
Sword* extractSwordFromList(Sword**, int);
void freeShields(Shield*);
void freeSwords(Sword*);
void freeHeroes(Hero*);

//DO NOT TOUCH THIS FUNCTION
int main(int argc, char** argv) {

    Hero* heroes = getHeroes();
    if(!heroes)
    {
    	return 1;
    }
    Shop(heroes);
    
    freeHeroes(heroes);
    return (EXIT_SUCCESS);
}

//DO NOT TOUCH THIS FUNCTION
void Shop(Hero* heroes)
{
    FILE* fp = fopen("shields.bin", "rb");
    
    if(!fp)
    {
        printf("shields failed to open\n");
        return;
    }

	FILE* fp2 = fopen("swords.bin", "rb");
    if(!fp2)
    {
        printf("swords failed to open\n");
        return;
    }

    int numShields = 0, numSwords = 0;
    
    Shield* shields = NULL;
    shields = readShields(fp, &numShields);
    if(fclose(fp) != 0)
    {
    	printf("Couldn't close the shields file...this is awkward.\nWill try to continue with the program.\n");
    }

    

    Sword* swords = NULL;
    swords = readSwords(fp2, &numSwords);
    if(fclose(fp2) != 0)
    {
    	printf("Couldn't close the swords file...this is awkward.\nWill try to continue with the program.\n");
    }

	if(!shields)
    {
    	printf("I got no list back from readShields! What happened?\n");
    	return;
    }

    //decent range to check for bad values.
    if(numShields > 40 || numShields < 5)
    {
    	printf("Your number of shields is invalid! What happened?\n");
    	return;
    }

    //This will seg fault if your list is bad!
    Shield* tmp = shields;
    while(tmp != NULL)
    {
    	tmp = tmp->nextShield;
    }

    if(!shields)
    {
    	printf("I got no list back from readSwords! What happened?\n");
    	return;
    }

	//decent range to check for bad values.
    if(numSwords > 40 || numSwords < 5)
    {
    	printf("Your number of swords is invalid! What happened?\n");
    	return;
    }

    //This will seg fault if your list is bad!
    Sword* tmp2 = swords;
    while(tmp2 != NULL)
    {
    	tmp2 = tmp2->nextSword;
    }

    while(1)
    {
		if(!shields)
	    {
	    	printf("I don't have a list of shields! What happened?\n");
	    	return;
	    }

	    //decent range to check for bad values.
	    if(numShields > 40 || numShields < 0)
	    {
	    	printf("Your number of shields is invalid! What happened?\n");
	    	return;
	    }

	    //This will seg fault if your list is bad!
	    Shield* tmp = shields;
	    while(tmp != NULL)
	    {
	    	tmp = tmp->nextShield;
	    }

	    if(!shields)
	    {
	    	printf("I don't have a list of swords! What happened?\n");
	    	return;
	    }

		//decent range to check for bad values.
	    if(numSwords > 40 || numSwords < 0)
	    {
	    	printf("Your number of swords is invalid! What happened?\n");
	    	return;
	    }

	    //This will seg fault if your list is bad!
	    tmp2 = swords;
	    while(tmp2 != NULL)
	    {
	    	tmp2 = tmp2->nextSword;
	    }

        printf("Welcome to the shop!\n\n1: Shields\n2: Swords\n3: View heroes\n4: quit\n");
        
        printf("\nSelect an option: ");
        int choice;
        scanf("%d", &choice);
        
        while(choice < 1 || choice > 4)
        {
            printf("I did not understand that command. Try again: ");
            scanf("%d", &choice);
        }
        
        switch(choice)
        {
            case 1:
                shieldSelection(&shields, heroes, &numShields);
                break;
            case 2:
                swordSelection(&swords, heroes, &numSwords);
                break;
            case 3:
                printHeroes(heroes, ALL);
                break;
            case 4:
                freeShields(shields);
                freeSwords(swords);
                return;
            default:
            	printf("I wasn't supposed to get here! Fatal error.\n");
            	freeShields(shields);
                freeSwords(swords);
                return;
        }
        
    }
}

//DO NOT TOUCH THIS FUNCTION
Hero* getHeroes(void)
{
    FILE* fp = fopen("chosenHeroes.bin", "rb");
    if(!fp)
    {
    	printf("Heroes file did not open!\n");
    	return NULL;
    }

    Hero* heroes = malloc(sizeof(Hero)*3);
    if(!heroes)
    {
    	printf("Heroes failed to malloc! That's really bad!\n");
    	printf("Try closing some programs to free up memory\n");
    	return NULL;
    }

    int i = 3;
    int j = 0;
    int timeout = 10;
    while((j = fread(heroes, sizeof(Hero), i, fp)) != i)
    {
    	if(timeout == 0)
    	{
    		printf("I couldn't read data from the file. Try a different computer?\n");
    		return NULL;
    	}
    	i = i-j;
    	timeout--;
    }

    for(i = 0; i < 3; i++)
    {
    	heroes[i].shield = NULL;
    	heroes[i].sword = NULL;
    }

    if(fclose(fp) != 0)
    {
    	printf("Couldn't close the hero file...this is awkward.\nWill try to continue with the program.\n");
    }
    return heroes;
}

//DO NOT TOUCH THIS FUNCTION
void printHeroes(Hero* heroes, print_option option)
{
    int i;
    switch(option)
    {
        case ALL:
            for(i = 0; i < 3; i++)
            {
                printf("\n%d: %s\n\tHealth: %dhp\n\tAttack: %d\n\tDefense: %d\n\tSpeed: %d\n\tLuck: %d\n", 
                    i, heroes[i].name, heroes[i].health, heroes[i].attack, 
                    heroes[i].defense, heroes[i].speed, heroes[i].luck);
                printf("Items for %s\n", heroes[i].name);
                if(heroes[i].shield != NULL)
                {
                    printf("\tShield: %s\n\t\tPrice: $%d\tDefense: %d\tWeight: %dkg\n",
                        heroes[i].shield->name, heroes[i].shield->price, 
                        heroes[i].shield->defense, heroes[i].shield->weight);
                }
                else
                {
                    printf("\tShield: None\n");
                }
                if(heroes[i].sword != NULL)
                {
                    printf("\tSword:\n\t%s\n\t\tPrice: $%d\tDamage: %d\n",
                        heroes[i].name, heroes[i].sword->name, heroes[i].sword->price, 
                        heroes[i].sword->damage);
                }
                else
                {
                    printf("\tSword: None\n");
                }
            }
            break;
        case SWORDS:
            for(i = 0; i < 3; i++)
            {
                if(heroes[i].sword == NULL)
                {
                    printf("\n%d: %s\n\tHealth: %dhp\n\tAttack: %d\n\tDefense: %d\n\tSpeed: %d\n\tLuck: %d\n", 
                        i, heroes[i].name, heroes[i].health, heroes[i].attack, 
                        heroes[i].defense, heroes[i].speed, heroes[i].luck);
                    printf("Items for %s\n", heroes[i].name);
                    if(heroes[i].shield != NULL)
                    {
                        printf("\tShield: %s\n\t\tPrice: $%d\tDefense: %d\tWeight: %dkg\n",
                            heroes[i].shield->name, heroes[i].shield->price, 
                            heroes[i].shield->defense, heroes[i].shield->weight);
                    }
                    else
                    {
                        printf("\tShield: None\n");
                    }   
                    printf("\tSword:None\n");
                }
                else
                {
                	printf("\n%s has a sword already.\n", heroes[i].name);
                }
            }
            break;
        case SHIELDS:
            for(i = 0; i < 3; i++)
            {
                if(heroes[i].shield == NULL)
                {
                    printf("\n%d: %s\n\tHealth: %dhp\n\tAttack: %d\n\tDefense: %d\n\tSpeed: %d\n\tLuck: %d\n", 
                        i, heroes[i].name, heroes[i].health, heroes[i].attack, 
                        heroes[i].defense, heroes[i].speed, heroes[i].luck);
                    printf("Items for %s\n\tShield: None\n", heroes[i].name);   
                    if(heroes[i].sword != NULL)
                    {
                        printf("\tSword: %s\n\t\tPrice: $%d\tDamage: %d\n",
                            heroes[i].name, heroes[i].sword->name, heroes[i].sword->price, 
                            heroes[i].sword->damage);
                    }
                    else
                    {
                        printf("\tSword: None\n");
                    }
                }
                else
                {
                	printf("\n%s has a shield already.\n", heroes[i].name);
                }
            }
            break;
    }
}

void freeHeroes(Hero* heroes)
{
    int i = 0;
    for(; i < 3; i++)
    {
        if(heroes[i].shield != NULL)
        {
            free(heroes[i].shield);
        }
        if(heroes[i].sword != NULL)
        {
            free(heroes[i].sword);
        }
        
    }
    free(heroes);
}

void shieldSelection(Shield** shields, Hero* heroes, int* numShields)
{
    int count = 0;
    while (count < 3){
        //gets the shield options to print out
        printShields(*shields);
        int selection;
        printf("Select a shield you would like to purchase: ");
        scanf("%d", &selection);
        while ( selection < 0 || selection > *numShields){
            printf("Try another option: ");
            scanf("%d", &selection);
        }
        //since we can't hardcode the number of shields, we use the pointer of numShields
        //quits the shields program once it equals number of shields
        if (selection == *numShields){
            return;
        }
        else{
           Shield*temp = extractShieldFromList(shields, selection);
           (*numShields)--;
           printHeroes(heroes, SHIELDS);
           int hoption=0;
           printf("Select a hero:");
           scanf("%d", &hoption);
           heroes[hoption].shield = temp;
        }
    }
}

//same as shieldSelection!!!!
void swordSelection(Sword** swords, Hero* heroes, int* numSwords)
{
    int count= 0;
    while (count < 3){
        //prints out the sword options
        printSwords(*swords);
        int selection;
        printf("Select a sword you would like to purchase: ");
        scanf("%d", &selection);
        while (selection < 0 || selection > *numSwords){
            printf("Try another option: ");
            scanf("%d", &selection);
        }
        if (selection == *numSwords){
            return;
        }
        else {
            Sword*temp = extractSwordFromList(swords, selection);
            (*numSwords)--;
            printHeroes(heroes, SWORDS);
            int hoption = 0;
            printf("Select a hero: ");
            scanf("%d", &hoption);
            heroes[hoption].sword = temp;
        }
    }
}

void printShields(Shield* shields)
{
    Shield* head = shields;
    Shield* tmp = head;
    int i = 0;
    while (tmp != NULL){
        printf("%d: %s\n\tPrice: $%d\tDefense: %d\tWeight: %dkg\n\n", i, tmp->name, tmp->price, tmp->defense, tmp->weight);
        i++;
        tmp = tmp->nextShield;
    }
    printf("%d: Quit\n", i);
}

// same as printShields
void printSwords(Sword* swords)
{
    Sword* head = swords;
    Sword* tmp = head;
    int i = 0;
    while (tmp != NULL){
        printf("%d: %s\n\tPrice: $%d\tDamage: %d\n\n", i, tmp->name, tmp->price, tmp->damage);
        i++;
        tmp = tmp->nextSword;
    }
    printf("%d: Quit\n", i);
}

Shield* readShields(FILE* fp, int* numShieldsPtr)
{
    Shield* shield= malloc(sizeof(Shield));
    Shield* head = shield;
    Shield* curr = shield;
    fread(curr,sizeof(Shield), 1, fp);
    while(1){
        Shield* newguy = malloc(sizeof(Shield));
        curr->nextShield = newguy;
        newguy->nextShield = NULL;
        (*numShieldsPtr)++;
        if (fread(newguy, sizeof(Shield), 1, fp) == 0){
            free(newguy);
            curr->nextShield = NULL;
            return head;
        }
        curr = newguy;
    }
}

//same as readSheilds
Sword* readSwords(FILE* fp, int* numSwordsPtr)
{
    Sword* sword= malloc(sizeof(Sword));
    Sword* head = sword;
    Sword* curr = sword;
    fread(curr,sizeof(Sword), 1, fp);
    while(1){
        Sword* newguy = malloc(sizeof(Sword));        
        (*numSwordsPtr)++;
        curr->nextSword = newguy;
        newguy->nextSword = NULL;
        if (fread(newguy, sizeof(Sword), 1, fp) == 0){
            free(newguy);
            curr->nextSword = NULL;
            return head;
        }
        curr = newguy;
    }
}

//This function takes out the selected shield from the list to delete it. 
Shield* extractShieldFromList(Shield** shields, int chosenShield)
{
    int i = 0;
    Shield* tmp = *shields;
    Shield* prev = *shields;
    Shield* head = *shields;
    if (chosenShield == 0){
        tmp = head;
        (*shields)=(*shields)->nextShield;
        return tmp;
    }
    else {
        tmp = head;
        while(tmp != NULL){
            if (i != chosenShield){
                i++;
                tmp = tmp->nextShield;
            }
            else {
                prev->nextShield = tmp->nextShield;
                return tmp;
            }
        }
    }
}

//same as extractShieldFromList
Sword* extractSwordFromList(Sword** swords, int chosenSword)
{
     int i = 0;
    Sword* tmp = *swords;
    Sword* prev = *swords;
    Sword* head = *swords;
    if (chosenSword == 0){
        tmp = head;
        (*swords)=(*swords)->nextSword;
        return tmp;
    }
    else {
        tmp = head;
        while(tmp != NULL){
            if (i != chosenSword){
                i++;
                tmp = tmp->nextSword;
            }
            else {
                prev->nextSword = tmp->nextSword;
                return tmp;
            }
        }
    }
}

//releases shields from memory
void freeShields(Shield* shields)
{
    Shield* prev = shields;
    Shield* curr = shields;
    while (curr != NULL){
        curr = curr->nextShield;
        shields = shields->nextShield;
        free(prev);
        prev = prev->nextShield;
    }
}

//releases swords from memory
void freeSwords(Sword* swords)
{
    Sword* prev = swords;
    Sword* curr = swords;
    while (curr != NULL){
        curr = curr->nextSword;
        swords = swords->nextSword;
        free(prev);
        prev = prev->nextSword;
    }
}

