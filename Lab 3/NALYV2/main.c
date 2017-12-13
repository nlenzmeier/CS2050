/* 
 * File:   main.c
 * Author: Nicolle
 * NALYV2
 * LAB F
 * LAB 3
 * Created on September 16, 2015, 11:58 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void collatzDriver();
int collatz(int);
void hexConverterDriver();
int hexConverter(int);

//calls our Driver functions
int main(int argc, char** argv) {
    collatzDriver();
    hexConverterDriver();
   
    
    return (EXIT_SUCCESS);
}

//Displays the menu to perform the collatz function
void collatzDriver(){
    int linenum;
    printf("Enter a positive number for the Collatz sequence or -1 to quit:");
    scanf("%d", &linenum);
    
    //excludes -1 from not working, and checks all other numbers
    while (linenum != -1){
        if (linenum == 0){
            printf("Invalid input. Try again:");
            scanf("%d", linenum);
        }
        if (linenum < -1){
           printf("Invalid input, Try again:");
            scanf("%d", linenum);
        }
        else {
            //printf("%d->", linenum);
            collatz(linenum);
        }
        printf("\nEnter a positive number for the Collatz sequence or -1 to quit:");
        scanf("%d", &linenum);
    }
    return;
}

//creates the numbers for the number chain
int collatz(int numentered){
    if (numentered == 1){
        printf("%d", numentered);
        return 1;
    }
    if (numentered%2==0){
        printf("%d->", numentered);
        numentered = numentered/2;
        return collatz(numentered);
    }
    else{
        printf("%d->",numentered);
        numentered = (numentered*3)+1;
        return collatz(numentered);
        }
}

//Displays the menu for the hex conversion function
void hexConverterDriver(){
    int num;
    printf("Enter a number in hex to be converted to decimal or -1 to quit:");
    scanf("%d", &num);  
    
    //excludes -1 from not working and throwing an error, and checking all other numbers
    while (num != -1){
        if (num == 0){
            printf("Invalid input. Try again:");
            scanf("%d", num);
        }
        if (num < -1){
           printf("Invalid input, Try again:");
            scanf("%d", num);
        }
        else {
            printf("Your number in decimal is %d", hexConverter(num));
        }
        printf("\nEnter a number in hex to be converted to decimal or -1 to quit:");
        scanf("%d", &num);
    }
    return;
}

//Converts hex to decimal numbers
int hexConverter(int hex){
    if (hex < 10){
        return hex;
    }
    int n = hex;
    int count=0;
    while (n != 0){
        n/=10;
        ++count;
    }
    // Checks to see if count is working properly.
    //printf("Number of digits: %d", count);
        int denominator= pow(10, count-1);
        int msig = hex/denominator;
        int rest = hex%denominator;
        return (msig * pow(16, count -1) + hexConverter(rest));
}
