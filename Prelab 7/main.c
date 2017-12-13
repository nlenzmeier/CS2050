/* 
 * File:   main.c
 * Author: Nicolle
 *
 * Created on October 10, 2015, 2:48 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
typedef struct state
{
    int lengthOfState;
    char* name;
    long int population;
    long int populationOver18;
} State;

void readStates(State**, char*);
void printStateInfo(State*, int);
void findTotalPercentage(State*, float*);
void freeStates(State*);


int main(int argc, char** argv) {
    int option;
    State* usa = malloc(sizeof(State)*51);
    readStates(&usa, argv[1]);
//    printStateInfo(usa, option);
    do {
        printf("Put in state ID to get information or -1 to quit:");
        scanf("%d", &option);
        while (option > 51){
            printf("Please enter a number between 1-51:");
            scanf("%d", &option);
        }
        if (option == -1){
            float a;
            findTotalPercentage(usa, &a);
            printf("Percentage of US that is 18+: %.2f%%", a);
            break;
        }
        printStateInfo(usa, option);
    }
    while (option !=-1);
    
    freeStates(usa);
    return (EXIT_SUCCESS);
}

void readStates(State** y, char* fred){
    FILE*ptr = fopen(fred, "r");
    if (ptr == NULL){
        printf("Could not open file");
    }
    int i;
    for (i = 0; i< 51; i++){
        fscanf(ptr, "%d\n", &(*y)[i].lengthOfState);
        (*y)[i].name = malloc(sizeof(char) * ((*y)[i].lengthOfState));
        fscanf(ptr, "%s %ld %ld", (*y)[i].name, &(*y)[i].population, &(*y)[i].populationOver18);
    }
    return; 
}

void printStateInfo(State* z, int i){
    printf("----- State Info ----\n");
    printf("State Name: %s\n"
            "Length of the name: %d\n"
            "Total Population: %ld\n"
            "Total population over 18: %ld\n", z[i].name, z[i].lengthOfState-1, z[i].population, z[i].populationOver18);
    return;
}

void findTotalPercentage(State* t, float* b){
    int i;
    long int totalpop=0;
    for(i = 0; i < 51; i++){
        totalpop += t[i].population;
    }
    int j;
    long int totalunder=0;
    for (j = 0; j < 51; j++){
        totalunder+= t[j].populationOver18;
    }
    *b = ((float)totalunder/totalpop)*100;
   
    return;
}

void freeStates(State* h){
    int i=0;
    for(i=0; i<51; i++){
        free(h[i].name);
    }
    free(h);
}

