/* 
 * File:   main.c
 * Author: Nicolle
 *Lab F
 * Created on September 2, 2015, 12:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _car {
    char model[20];
    char brand[20];
    int year;
    long worth;
} Car;

typedef struct _house{
    int sqFootage;
    long worth;
} House;

typedef struct _person {
    char firstname[20];
    char lastname[20];
    int numCars;
    Car ownedCars[2];
    House ownedHouse;
} Person;

Person readPeople(FILE* fp);
int calculateTotal(Person people);
Car findMostExpensiveCar(Person* people);

/*
 * 
 */
int main(int argc, char** argv) {
    if (argv != 2){
        printf("Invalid arguments");
    }
   
    
//github practice for my functions created below.
/*Person bobSmith = {
        "Bob",
        "Smith",
        1,
        {{
            "Ford",
             "Mustang",
             1964,
             20000
         }},
        {
            50000,
            1000000
        }
    };
    
    Person joeSmith = {
        "Joe",
        "Smith",
        2,
        {{
            "Honda",
            "Civic",
            2009,
            7000,    
        },{
            "Jeep",
            "Grand Cheroke",
            2011,
            10000
        }},
        {
            1000,
            300000
        }
    };
    
    Person people[2] = {bobSmith, joeSmith};
    
    //Generate a sample input
    FILE* fp = fopen("sampleInput.txt", "w");
    if (fp == NULL) {
        return (EXIT_FAILURE);
    }
    
    fprintf(fp, "%s %s\n%d\n%d %s %s %ld\n%d %ld",
            bobSmith.firstname,
            bobSmith.lastname,
            bobSmith.numCars,
            bobSmith.ownedCars[0].year,
            bobSmith.ownedCars[0].brand,
            bobSmith.ownedCars[0].model,
            bobSmith.ownedCars[0].worth,
            bobSmith.ownedHouse.sqFootage,
            bobSmith.ownedHouse.worth
        );
    
    fprintf(fp, "%s %s\n%d\n%d %s %s %ld\n%d %s %s %ld\n%d %ld",
            joeSmith.firstname,
            joeSmith.lastname,
            joeSmith.numCars,
            joeSmith.ownedCars[0].year,
            joeSmith.ownedCars[0].brand,
            joeSmith.ownedCars[0].model,
            joeSmith.ownedCars[0].worth,
            joeSmith.ownedCars[1].year,
            joeSmith.ownedCars[1].brand,
            joeSmith.ownedCars[1].model,
            joeSmith.ownedCars[1].worth,
            joeSmith.ownedHouse.sqFootage,
            joeSmith.ownedHouse.worth
        );
    
    fclose(fp);
    fp = fopen("sampleInput.txt", "r");
    const Person person2 = readPeople(fp);
        printf("%s %s\n%d\n%d %s %s %ld\n%d %s %s %ld\n%d %ld",
            person2.firstname,
            person2.lastname,
            person2.numCars,
            person2.ownedCars[0].year,
            person2.ownedCars[0].brand,
            person2.ownedCars[0].model,
            person2.ownedCars[0].worth,
            person2.ownedCars[1].year,
            person2.ownedCars[1].brand,
            person2.ownedCars[1].model,
            person2.ownedCars[1].worth,
            person2.ownedHouse.sqFootage,
            person2.ownedHouse.worth
        );
    
    fclose(fp);
    remove("sampleInput.txt");
    printf("Passed all readPeople tests");
    
    
    printf("Beginning calculateTotal tests");
    const int bobNetWorth = calculateTotal(bobSmith);
    assert(bobNetWorth == 1020000);
    
    const int joeNetWorth = calculateTotal(joeSmith);
    assert(joeNetWorth == 317000);
    
    printf("Passed all calculateTotal tests");
    
    printf("Beginning findMostExpensiveCar tests");
    
    const Car bobsMostExpensiveCar = findMostExpensiveCar(people);
    assert(
            strcmp(bobsMostExpensiveCar.brand, bobSmith.ownedCars[0].brand) == 0
    );
    
    const Car mostExpensiveCar = findMostExpensiveCar(people);
    assert(
            strcmp(mostExpensiveCar.brand, joeSmith.ownedCars[0].brand) == 0
    );
    printf("Passed all findMostExpensiveCar tests");
    
    printf("Congratulations, delete this code and implement main");*/
    return (EXIT_SUCCESS);
}

Person readPeople(FILE* fp){
    
    Person guy;
    fscanf(fp, "%s %s", guy.firstname, guy.lastname);
    fscanf(fp, "%d", &guy.numCars);
    int i=0;
    for (i = 0; i < guy.numCars; i++){
        fscanf(fp, "%d %s %s %ld", &guy.ownedCars[i].year, guy.ownedCars[i].brand, guy.ownedCars[i].model, &guy.ownedCars[i].worth);
    }
    fscanf(fp, "%d %ld", &guy.ownedHouse.sqFootage, &guy.ownedHouse.worth);
    return guy;
}

int calculateTotal(Person people){
    int total=0;
    int i=0;
    for (i=0; i < people.numCars; i++){
       total +=(int)people.ownedCars[i].worth;
    }
    total += people.ownedHouse.worth;
    return total;
}

Car findMostExpensiveCar(Person* people){
    Car max;
    max.worth= -1;
    int x;
    int j;
    for (x=0; x < 4; x++){
        for (j=0; j < people[x].numCars; j++){
            if (people[x].ownedCars[j].worth > max.worth){
                max = people[x].ownedCars[j];
            }
        }
    }
    return max;
}
   