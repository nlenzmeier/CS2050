/* 
 * File:   main.c
 * Author: Nicolle
 *
 * Created on August 27, 2015, 2:23 PM
 */

#include <stdio.h>
#include <stdlib.h>


/* for (i=0; i < 2; i++) {
 printf ("%s %s %d\n", people[i].firstname, people[i].lastname, &people[i].height);
 }*/

//structures
typedef struct _car
{
    char color[20];
    char model[20];
    char brand[20];
    int year;
} Car;

typedef struct _person
{
    char firstName[20];
    char lastName[20];
    int heightInInches;
} Person;

//Prototypes
Car* readCar(char*);
Person* readPeople(char*);
void printData(Car*, Person*);

int main(int argc, char** argv) {
    if (argc != 3){
        printf("Invalid arguments!\n Correct Usage: ./a.out <Car file> <Person file>\n");
        return 1;
    }
    
    Car *drive;
    drive = readCar(argv[1]);
    
    Person* guy;
    guy = readPeople(argv[2]);
    printData(drive, guy);
    free(drive);
    free(guy);
    return 0;
}

Car* readCar(char* filename){
    FILE*fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Failed to open the file %s\n", filename);
    }
    int x = 0;
    
    Car *motor;
    motor=malloc(sizeof(Car)*3);
    while(1){
        fscanf(fp, "%d %s %s %s", &motor[x].year, motor[x].color, motor[x].brand, motor[x].model);
        x++;
        if (feof(fp)){
            break;
        }
    }
    fclose(fp);
    return motor;
}

Person* readPeople(char* filename){
    FILE*fp= fopen(filename, "r");
    if (fp==NULL){
        printf("Failed to open the file %s\n", filename);
    }
    Person *dude;
    int i=0; 
    dude=malloc(sizeof(Person)*3);
    while (1){
        fscanf(fp, "%s %s %d", dude[i].firstName, dude[i].lastName, &dude[i].heightInInches);
        i++;
        if (feof(fp)){
            break;
        }
    }
    fclose(fp);
    return dude;
}

void printData(Car *drive, Person *dude){
    int i = 0;
    int j = 0;
    printf("List of Cars:\n");
    for (i=0; i < 3; i++){
        printf("%d %s %s %s\n", drive[i].year, drive[i].color, drive[i].brand, drive[i].model);
    }
    printf("\nList of People\n");
    for(j=0; j<3; j++){
        printf("%s %s %d\n", dude[j].firstName, dude[j].lastName, dude[j].heightInInches);
    }
    printf("\nPlease edit referenced text documents to change listing.");
    return;
}
  /*  JUNK! JUST HERE FOR EXTRA THOUGHTS
   * 
   * Person* people = malloc(sizeof(Person)*2);
    int i;
    
    FILE* file=fopen(peoplelist.txt, "r");
    if (file == NULL){
        return 0;
    }
    
    for (i=0, i < 2, i++){
        fscanf(file, "%s %s %d", people[i].firstName, people[i].lastName, &people[i].heightInInches);
    }
    
    Car* cars = malloc(sizeof(Car)*4);
    int j;
    
    FILE* fp=fopen(carlist.txt, "r");
    if (file == NULL){
        return 1;
    }
    
    for (j=0, j<4, j++){
        fscanf(fp, "%d %s %s %s", &cars[j].year, cars[j].color, cars[j].brand, cars[j].model);
    }
    
    printf("%d %s %s %s", &cars[j].year, cars[j].color, cars[j].brand, cars[j].model);
    
    printf ("%s %s %d\n", people[i].firstName, people[i].lastName, &people[i].heightInInches);
    
    
    
    
    fclose(file);  
    fclose(fp);
    return (EXIT_SUCCESS);
}

printData(Car[] cars, Person[] people){
    printf("%d %s %s %s", cars[j].year, cars[j].color, cars[j].brand, cars[j].model);
    
    printf ("%s %s %d\n", people[i].firstname, people[i].lastname, &people[i].height);
}*/