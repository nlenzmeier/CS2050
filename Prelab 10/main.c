/* 
 * File:   main.c
 * Author: Nicolle Lenzmeier
 * NALYV2
 * Prelab 10
 * Lab F
 * Created on November 22, 2015, 6:23 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Is the input string a date? If it is, return true. Otherwise, return false.
bool isADate(char* token);
/*
 * 
 */

//Don't touch me.
//Or do touch it. I suggest you know what you're doing first though.
//If you want to try other dates, find the dates in the strcpy calls and change them. 
//Also make sure that the output is correct if you do change the dates (as it stands, 2 3 and 4 are invalid, 1 is valid.)
//No sample output needed. Prints if it's a date or if it's not a date, and if there was an error.
int main(int argc, char** argv) {
    char* token = malloc(sizeof(char)*20);
    //load date #1. Need the null terminator? Not sure actually. 
    strcpy(token, "10/20/1999\0");
    if(isADate(token))
    {
        printf("%s is a date.\n", token);
    }
    else
    {
        printf("%s is not a date, but should be.\n", token);
    }
    //clear out the token. Not necessary, I think, since all dates are the same length, but w/e
    memset(token, 0, strlen(token)+1);
    //date #2
    strcpy(token, "15/20/1929\0");
    if(!isADate(token))
    {
        printf("%s is not a date.\n", token);
    }
    else
    {
        printf("%s is a date, but shouldn't be.\n", token);
    }
    memset(token, 0, strlen(token)+1);
    //date #3
    strcpy(token, "06/31/2014\0");
    if(!isADate(token))
    {
        printf("%s is not a date.\n", token);
        
    }
    else
    {
        printf("%s is a date, but shouldn't be.\n", token);
    }
    //aha! Not all dates are in fact the same length.
    memset(token, 0, strlen(token)+1);
    strcpy(token, "06/2/201\0");
    if(!isADate(token))
    {
        printf("%s is not a date.\n", token);
        
    }
    else
    {
        printf("%s is a date, but shouldn't be.\n", token);
    }
    //whoops, still need to free.
    free(token);
    return (EXIT_SUCCESS);
}

bool isADate(char* token)
{
    //Index of the array below -> number of days in (that month+1).
    //So daysPerMonth[1] = 28 (28 days in February)
    //(Just learned how to spell February, and that there's no actual pattern to number of days. Who designed the calendar anyway?)
    int daysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    //We'll say that the earliest readable date is 01/01/1970 (computer epoch).
    //Computers shouldn't be reading stuff from earlier than computers anyway.
    int earliestValidYear = 1970;
    int earliestValidDay = 1;
    int earliestValidMonth = 1;
    
    //RULES:
    //  1. Dates cannot be earlier than the computer epoch. The day-of is okay. 
    //  2. The month number must be valid. The day in that month must also be valid, based on the above array. 
    //  3. Dates must be in the form MM/DD/YYYY. You must find this to be true!
    //      3a. This means, no extra '/'s, 2 digits in month and day and 4 digits in year. 
    //  4. You cannot use the string library! isdigit() might be useful though!
    //      4a. If this is too difficult, you can use the string library. But you absolutely cannot use strtok().
    //          I am using strtok in lab, and the way strtok works, that means you can't use it. You also can't use its associated functions.
    //      4b. In lab, you will be allowed to use string library functions, but you will be docked points for doing so.
    
    //Function gets hairy very quickly. So if it gets messy, you are probably doing it right.
    
    return true;
}

