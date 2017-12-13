#include "header.h"
#include <stdlib.h>
#include <stdio.h>

Student* searchForStudent(Student* root, int ID)
{
    if(!root)
    {
        return NULL;
    }
    
    if(root->ID == ID)
    {
        return root;
    }
    else if(root->ID > ID)
    {
        return searchForStudent(root->leftStudent, ID);
    }
    else
    {
        return searchForStudent(root->rightStudent, ID);
    }
}

Student* addLeaf(Student* root, Student* newNode)
{
    if(!root)
    {
        return newNode;
    }
    
    if(root->ID > newNode->ID)
    {
        root->leftStudent = addLeaf(root->leftStudent, newNode);
    }
    else
    {
        root->rightStudent = addLeaf(root->rightStudent, newNode);
    }
    
    return root;
}

Student* readTotalStudentsAndMakeTree(char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    #ifdef TEST
        //did the file open correctly?
    #endif

    Student* node = NULL;
    Student* root = NULL;
    int fxnCheck = 0;
    while(!feof(fp))
    {
        node = malloc(sizeof(Student));
        
        #ifdef TEST
            //did the node malloc correctly?
        #endif

        //reads a student from the file. Every student has an 8 digit student ID, a GPA, and a first and last name.
        fxnCheck = fscanf(fp, "%d %f %s %s",
                &(node->ID), &(node->GPA), node->fname, node->lname);
        
        #ifdef TEST
            //was all data read in?
            //is every piece of student data valid? 
            //is the student a duplicate? (This one requires a little creativity)
        #endif

        node->leftStudent = NULL;
        node->rightStudent = NULL;
        root = addLeaf(root, node);
        
        #ifdef TEST
            //is the root okay?
            //is the root's left what it should be?
            //is the root->left's left and right what it should be?
            //is the root's right what it should be?
            //is the root what it should be?
        #endif
    }
    return root;
}
