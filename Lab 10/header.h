/* 
 * File:   header.h
 * Author: Nicolle
 *
 * Created on November 11, 2015, 12:42 PM
 */

#ifndef HEADER_H
#define	HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct studentNode
{
    int ID;
    float GPA;
    char fname[20];
    char lname[20];
    struct studentNode* leftStudent;
    struct studentNode* rightStudent;
} Student;

//Tree functions below
Student* addLeaf(Student*, Student*);
Student* readTotalStudentsAndMakeTree(char*);
Student* searchForStudent(Student*, int);
//Queue functions below
Student* readStudentsForClassAndMakeQ(char*);
Student* addStudentToQ(Student*, Student*);
Student* removeStudentFromQ(Student**);


#ifdef	__cplusplus
}
#endif

#endif	/* HEADER_H */

