/* 
 * File:   main.c
 * Author: Nicolle
 *
 * Created on September 30, 2015, 12:04 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct student {
    char FName[20];
    char LName[20];
    float GPA;
    int ID;
} Student;



/*
 * Takes in a filename, reads students from that file, 
 * and returns the address of the malloced array. In order 
 * to also know the number of students, the address of an int 
 * is sent to this function so that the number can be stored for later use. 
 */
Student* readStudents(char* filename, int* numStudentsRef);

/*
 * Takes an address to an array and the number in that array, and prints out all the students. 
 */
void printStudents(Student* students, int numStudents);

/*
 *This function does a binary search recursively. 
 *It will take the address to the array, the number 
 *of students in that array, and the ID that we are 
 *looking for. Returns the address of the student with 
 *the target ID, or NULL if not found. 
 */
Student* searchStudentID(Student* students, int low, int high, int targetID);

//this prototype was not included, but it sorts it by their last name
Student* sortStudentsByLastName(Student* students, int numStudents);


// Sorts the students by there id's
Student* sortStudentsByID(Student* students, int numStudents);

/* 
 * Finds the student with the highest GPA. Returns the address to that student. 
 */
Student* findHighestGPA(Student* students, int numStudents); 

/*
 * Takes the address to the array, the number of elements, and the filename, 
  *and writes the array to a sequential file so that it can be readable to users. 
 */
void writeToReadableFile(Student* students, int numStudents, char* filename);

/*
 * Central HQ for the program. Takes in what it needs, and runs the rest. 
 */
void driver(char* filename, char* filename2);

int main(int argc, char** argv) {
    
    driver(argv[0], argv[1]); 
    
    return (EXIT_SUCCESS);
}

void driver(char* filename, char* filename2)
{
    int numStudents;
    Student* students = readStudents(filename, &numStudents);
    printf("Students: \n");
    printStudents(students, numStudents);
//    printf("this is working..");
    
    
//    printf("The highest GPA is %.2f.\n", findHighestGPA(students, numStudents).GPA);
    //should not have used the ".", but the arrow
    printf("The highest GPA is %.2f.\n", findHighestGPA(students, numStudents)->GPA);
    
    printf("------------\nStudents sorted by last name:\n");
    students=sortStudentsByLastName(students, numStudents);
    printStudents(students, numStudents);
    
    students = sortStudentsByID(students, numStudents);
    int ID;
    int control;
    int low = 0;
    //need an int that will be the lowest value
    while(1)
    {
        printf("------------\nGive me a student ID to search for: ");
//        scanf("%d", ID); 
        scanf("%d", &ID); 
        
//        Student* result = searchStudentID(students, numStudents-1, ID);
        Student* result = searchStudentID(students, low, numStudents-1, ID);
        
//        if(result = NULL) 
        if(result == NULL) 
        {
            printf("Student not found.\n");
        }
        else
        {
            printf("Found student: \n");
            printStudents(result, 1);
        }
        printf("\n\nEnter 0 to quit or 1 to search for another ID: ");
        scanf("%d", &control);
        while(control != 1 || control != 0)
        {
            printf("Sorry, I don't understand that command. Try again.\n");
            printf("\n\nEnter 0 to quit or 1 to search for another ID: ");
            scanf("%d", &control);
        }
        if(control == 0)
        {
            break;
        }
    }
    
    writeToReadableFile(students, numStudents, filename2);
    
}

Student* readStudents(char* filename, int* numStudentsRef)
{
//    FILE* fp = fopen(filename, "r");
    FILE* fp = fopen(filename, "rb");
    
    if (fp == NULL){
        printf("Did not open file\n");
    }
    
    fseek(fp, 0, SEEK_END);
    
    //numStudentsRef = (int)ftell(fp) / sizeof(Student);
    //needs to be dereferenced
    *numStudentsRef = (int)ftell(fp) / sizeof(Student);
    rewind(fp);
    
    Student* students;
    
//    fread(&students, sizeof(Student), *numStudentsRef, fp);
    fread(students, sizeof(Student), *numStudentsRef, fp);
    
//    free(students)
    fclose(fp);
    
    return students;
    
    
}

void printStudents(Student* students, int numStudents)
{
//    printf("This is working");
    int i = 0; 
//    for(; i < numStudents; i++)
     for(i=0; i < numStudents; i++)
    {
        printf("-----%s %s\n\tGPA: %f\n\tStudent ID: %d\n------\n", 
//                students.FName, students.LName, students.GPA, students.ID);
                //should be arrows
                students[i].FName, students[i].LName, students[i].GPA, students[i].ID);
    }
    
    //return 0;
    // should not return anything since it is a void function
    return;
}

Student* searchStudentID(Student* students, int low, int high, int targetID)
{
    if(low<=high)
    {
        return NULL;
    }
    
    int mid = (low+high)/2;
    
//    if(targetID == students[mid])
    //needs to assign the int to a struct int, not the struct as a whole
    if(targetID == students[mid].ID)
    {
        return &students[mid];
    }
    else if(targetID > students[mid].ID)
    {
        return searchStudentID(students, low, mid, targetID);
    }
    else
    {
        return searchStudentID(students, mid+1, high, targetID);
    }
}

Student* findHighestGPA(Student* students, int numStudents)
{
    Student* max = &students[0];
    int i = 1;
    for(i; i < numStudents; i++)
    {
        if(students[i].GPA > max->GPA)
        {
            max = &students[i];
        }
    }
    
    return max;
}

Student* sortStudentsByLastName(Student* students, int numStudents)
{
    int i, j, min;
    
    for(j = 0; j < numStudents-1; j++)
    {
        for(i = j+1; i < numStudents; i++)
        {
            if(strcmp(students[i].LName, students[min].LName) > 0) 
            {
                min = i;
            }
        }
        
        if(min != j)
        {
//            int tmp = students[j];
            //tmp shouldn't be an int, but a struct
            Student tmp = students[j];
            students[j] = students[min];
            students[min] = tmp;
        }
    }
    
    return students;
}

Student* sortStudentsByID(Student* students, int numStudents)
{
    int i, j, min;
    for(j = 0; j < numStudents-1; j++)
    {
        min = j;
        for(i = j+1; i < numStudents; i++)
        {
            if(students[i].ID < students[min].ID)
            {
                min = i;
            }
        }
        
        if(min != j)
        {
//            int tmp = students[j];
             //tmp shouldn't be an int, but a struct
            Student tmp = students[j];
            students[j] = students[min];
            students[min] = tmp;
        }
    }
    
    return students;
}

void writeToReadableFile(Student* students, int numStudents, char* filename)
{
    FILE* fp = fopen(filename, "w");
    int i = 0;
    for(;i < numStudents; i++)
    {
        fprintf(fp, "%s %s\n", students[i].FName, students[i].LName);
        fprintf(fp, "%d %d\n", &students[i].GPA, &students[i].ID);
    }
    fclose(fp);
    free(students);
}


