#include "header.h"
#include <stdio.h>
#include <stdlib.h>

Student* readStudentsForClassAndMakeQ(char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    #ifdef TEST
        //did the file open?
    #endif

    int requiredGPA;
    int ID;
    int fxnCheck = 0;
    Student* node = NULL;
    Student* head = NULL;
    Student* tail;
    
    //This is the GPA every student must have to enroll into the class.
    fscanf(fp, "%f", &requiredGPA);
    
    #ifdef TEST
        //did the GPA read in okay?
    #endif

    while(!feof(fp))
    {
        node = malloc(sizeof(Student));
        
        #ifdef TEST
            //did node malloc okay?
        #endif

        //reads a student from the file. Every student has an 8 digit student ID, a GPA, and a first and last name.
        //later on, this student will be cross referenced with the set of students to make sure he/she is a valid student.
        fxnCheck = fscanf(fp, "%d %f %s %s",
                &(node->ID), &(node->GPA), node->fname, node->lname);
        
        #ifdef TEST
            //was everything read in correctly?
            //is every piece of student data valid? (Be creative, think about what is valid in this circumstance)
            //is the student qualified for the class? (Take a look at the rest of this fxn for hints)
        #endif
        
        //Only the rightStudent ptr will be used...all leftStudent ptrs will be NULL. This will
        //ensure a one-way list. 
        node->rightStudent = NULL;
        node->leftStudent = NULL;
        head = addStudentToQ(head, node);
        
        #ifdef TEST
            //was the node added correctly? (This take a little bit of code. Try using the tail ptr to verify)
            //is the head okay?
            //is the end of the list correct? (What's true about the last node in the list?)
            //is the head what it should be?
            //is the tail what it should be?
            //is the second thing in the list what it should be?
        #endif

        node = NULL;
    }
    return head;
}

Student* addStudentToQ(Student* head, Student* newNode)
{
    if(!head)
    {
        return newNode;
    }
    
    Student* tmp = head;
    while(tmp->rightStudent != NULL)
    {
        tmp = tmp->rightStudent;
    }
    tmp->rightStudent = newNode;
    return head;
}

Student* removeStudentFromQ(Student** head)
{
    if((*head)->rightStudent == NULL)
    {
        Student* tmp = *head;
        *head = NULL;
        return tmp;
    }
    
    Student* tmp = (*head);
    *head = (*head)->rightStudent;
    tmp->rightStudent = NULL;
    return tmp;
    
}
