/* 
 * File:   main.c
 * Author: Nicolle
 * LAB F
 * Lab 7
 * NALYV2
 * Created on October 14, 2015, 11:59 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
typedef struct state{
    int lengthOfState;
    char* name;
    long int population;
    long int populationOver18;
}State;

typedef struct division {
    char* name;
    State** states;
    int numStates;
    int lengthOfName;
}Division;

State* readStates(char*);
Division* readDivision(State*, char*, int*);
int printAndSelectDivision(Division*, int);
void printStatesInDivision(Division*, int);
void freeMemory(Division*, State*, int);


int main(int x, char** argv) {
    int option;
    State* usa = malloc(sizeof(State)*51);
    usa = readStates(argv[1]);
    Division* section;
    int length;
    section = readDivision(usa, argv[2], &length);
    
    do{
        printf("Make a selection:\n");
        printAndSelectDivision(section, length);
       
        
    }
    while (option != 9);
    
    freeMemory(usa, section, length);
    return (EXIT_SUCCESS);
}

State* readStates(char* b){
    FILE*ptr = fopen(b, "r");
    if (ptr == NULL){
        printf("Could not open file");
        return NULL;
    }
    int i;
    State* y = malloc(sizeof(State)*51);
    for (i = 0; i< 51; i++){
        fscanf(ptr, "%d\n", &(y[i].lengthOfState));
        y[i].name = malloc(sizeof(char) * (y[i].lengthOfState));
        fscanf(ptr, "%s %ld %ld", y[i].name, &(y[i].population), &(y[i].populationOver18));
    }
    return y; 
}

Division* readDivision(State* liberty, char* filename, int* lengthptr){
    FILE*fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file");
        return NULL;
    }
    fscanf(fp, "%d", lengthptr);
    int i;
    Division* d = malloc(sizeof(Division)*(*lengthptr));
    for (i = 0; i < *lengthptr; i++){ 
        fscanf(fp, "%d %d", &(d[i].lengthOfName), &(d[i].numStates));
        d[i].name = malloc(sizeof(char) * (d[i].lengthOfName));
                      
        int j=0;
        d[i].states = malloc(sizeof(State*)*d[i].numStates);
        for (j =0 ; j < d[i].numStates; j++){
            int states=0;
            fscanf(fp,"%d", &states);
            d[i].states[j] = &liberty[states];
        }
    }
    return d;
}

int printAndSelectDivision(Division* array, int length){
    int option;
    int i;
    for (i = 0; i < length; i++){
        printf("%d: %s\n", i, array[i].name);
    }
    printf("9: Quit");
    scanf("%d", &option);
    
    return option;
}

void freeMemory(Division* d, State* s, int x){
    int i, j;
    for (i = 0; i< 51; i++){
        free(s[i].name);
        for (j = 0; j < x; j++){
            free(d[i].name);
        }
    }
    free(s);
    free(d);
}

