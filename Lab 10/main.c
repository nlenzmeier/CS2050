/* 
 * File:   main.c
 * Author: Nicolle Lenzmeier
 * Lab F
 * Lab 10
 * Pawprint: NALYV2
 * Created on November 11, 2015, 11:59 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#define TEST



#define assert(condition){                  \
    if(!(condition))                        \
    {                                       \
        printf("Assertion failed:\n");      \
        printf("Line: %d\nFile: %s\n",      \
                __LINE__, __FILE__);        \
        exit(0);                            \
    }                                       \
}                                           \

/*
 * 
 */
int main(int argc, char** argv) {
    //Should fire if you did your Makefile correctly.
    #ifdef TEST
        printf("**************You have successfully triggered the preprocessor definition******************\n");
    #endif
    //Uncomment this and rerun if you can't get it to work. Comment it back out once it works.
    //assert(1 > 2);
    Student* root = readTotalStudentsAndMakeTree(argv[1]);
    Student* head = readStudentsForClassAndMakeQ(argv[2]);
    #ifdef TEST
        //is the root valid?
        //is the head valid?
    #endif

    Student* nextStudent;
    Student* checkStudent;
    while(head)
    {
        nextStudent = removeStudentFromQ(&head);
        #ifdef TEST
            //is nextStudent valid?
        #endif
        
        checkStudent = searchForStudent(root, nextStudent->ID);
        
        #ifdef TEST
            //was the student found to be a valid student?
        #endif

        printf("%s %s has been enrolled into the class.\n",
                nextStudent->fname, nextStudent->lname);
        free(nextStudent);
    }
    
    return (EXIT_SUCCESS);
}





