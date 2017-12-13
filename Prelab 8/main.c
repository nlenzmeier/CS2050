/* 
 * File:   main.c
 * Author: Nicolle
 *
 * Created on October 22, 2015, 12:46 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Integer_
{
    int num;
    struct Integer_* nextInt;
    struct Integer_* prevInt;
} Integer;

Integer* addInt(Integer*, Integer*);
void printNumbers(Integer*);
void freeNumbers(Integer*);
Integer* deleteInt(Integer*);
/*
 * 
 */
int main(int argc, char** argv) {
    Integer* top = NULL;
    Integer* new = NULL;
    while (1){
        int option;
        int num;
        printf("Select an option:\n1: Add a number\n2: Take a number off\n3: Print numbers\n4: Quit\n");
        printf("Option: ");
        scanf("%d", &option);
        while (option < 1 || option > 4){
            printf("Incorrect option. Please try again\n");
            scanf("%d", &option);
        }
        if (option == 1){
            new = malloc(sizeof(Integer));
            printf("Insert your number:");
            scanf("%d", &num);
            new->num = num;
            top = addInt(top, new);
        }
        if (option == 2){
            top = deleteInt(top);
        }
        if (option == 3){
            printNumbers(top);
        }
        if (option == 4){
            free(top);
            return 1;
        }
    }
    return (EXIT_SUCCESS);
}

Integer* addInt(Integer* top, Integer* new){
    if (new == NULL){
        return top;
    }
    if (top == NULL){
        new->nextInt=NULL;
        new->prevInt=NULL;
        return new;
    }
    else {
        top->nextInt=new;
        new->prevInt = top;
        new->nextInt = NULL;
        return new;
    }
}

void printNumbers(Integer* top){
    Integer* bottom = NULL;
    bottom = top;
    if (top == NULL){
        printf("Hey idiot, this list is EMPTY... too bad for you. Boo.");
        return;
    }
    else {
        while( bottom->prevInt != NULL){
            bottom = bottom->prevInt;
        }
        while (bottom->nextInt!= NULL){
            printf("%d -> ", bottom->num);
            bottom = bottom->nextInt;
        }
        printf("%d\n", bottom->num);
    }
}

void freeNumbers(Integer* top){
    Integer* tmp = top->prevInt;
    while (top->prevInt != NULL){
        tmp = top;
        top = top->prevInt;
        free(tmp);
    }
    free(top);
}

Integer* deleteInt(Integer* top){
    Integer* tmp = top;
    if (top == NULL){
        printf("Aaaaaah! Tis list is empty!");
        return NULL;
    }
    if (top->prevInt==NULL && top->nextInt==NULL){
        free (top);
        return NULL;
    }
    else {
        top = top->prevInt;
        free(tmp);
        top->nextInt = NULL;
        return top;
    }
}