/* 
 * File:   main.c
 * Author: Nicolle
 * Lab F
 * NALYV2
 *
 * Created on September 11, 2015, 1:03 PM
 */

#include <stdio.h>
#include <stdlib.h>

//Prototypes:
int factorial(int num);
int costFunction(int num);
void collatz(int);

int main(int argc, char** argv) {
    //Part 1
    int num, product;
    printf("Enter a positive number:");
    scanf("%d", &num);
    product = factorial(num);
    printf("Factorial = %d\n", product);

    //Part 2
    
    
    //Part 3
    int linenum;
    //int result;
    printf("Enter another positive number:");
    scanf("%d", &linenum);
    printf("%d->", linenum);
    collatz(linenum);
    return (EXIT_SUCCESS);
}

int factorial(int num){
    if (num ==1){
        return num;
    }
    else{
        return (num*factorial(num-1));
    }
//    int total=0;
//    int count;
//    int i;
//    if (num == 0){
//        return 1;
//    }
//    else{
//        return num * factorial(num-1);
//    }
//    return total;
}

int costFunction(int num){
    
}

void collatz(int numentered){
    int newnums;
        if(numentered == 1){
            return;
        }
        if(numentered%2==0){
            newnums= numentered/2;
            printf("%d->", newnums);
            collatz(newnums);
            return;
        }
        else{
            newnums= (numentered*3)+1;
            printf("%d->",newnums);
            collatz(newnums);
            return;
        }
}