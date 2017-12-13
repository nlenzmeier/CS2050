/* 
 * File:   main.c
 * Author: Nicolle
 * NALYV2
 * Lab F
 * Lab 4
 * Created on September 23, 2015, 11:53 AM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct cellphone
{
    char brand[20];
    char model[20];
    int priceNoContract;
    float screenDiameterInches;
    float customerRating;
    int numInStock;
} Phone;

//Prototypes
void driver(char* filename);
Phone* readPhones(char* filename);
void printPhones(Phone* phones);
Phone* sortPhones(Phone* phones, int sortChoice);

//Calls driver functions to implement the entire program
int main(int argc, char** argv) {
    driver(argv[1]);
    return (EXIT_SUCCESS);
}

//Displays menu while also calling the readPhone function and read in the file from binary
void driver(char* filename){
    Phone* cell = readPhones(filename);
    while (1) {
        printPhones(cell);
        int option;
        printf("How would you like to sort these phones?"
                "\n1: Price"
                "\n2: Screen Diameter"
                "\n3: Rating"
                "\n4: Quit\n");
        scanf("%d", &option);

        while (option < 1 || option > 4){
            printf("Invalid option. Please choose another:");
            scanf("%d", &option);
        }

        if (option == 4){
            break;
        }
        else{
            sortPhones(cell, option);
        }
    }
}

//reads the binary file and transfers it to our program for the user to read
Phone* readPhones(char* filename){
    Phone*phoneList = malloc(sizeof(Phone)*20); 
    FILE*ptr=fopen("phones.txt", "rb");
    if (ptr == NULL){
        printf("Could not open file.");
    }
    else {
        fread (phoneList, sizeof(struct cellphone), 20, ptr);
    }
    fclose(ptr);
    fclose(phoneList);
    return phoneList;
}

//insertion sort of phones, which the user gets to choose how we sort the file
//this is why I have three for loops... for each option the user might choose
Phone* sortPhones(Phone* phones, int sortChoice){
    int c, move, i;
    if(sortChoice == 1){
        for (c = 0; c < 20; c++){
            move = c;
            Phone insert = phones[c];
            
            while (move > 0 && phones[move - 1].priceNoContract > insert.priceNoContract){
                phones[move] = phones[move -1];
                --move;
            }
            phones[move]= insert;
        }
    }
    if(sortChoice == 2){
        for (c = 0; c < 20; c++){
            move = c;
            Phone insert = phones[c];
            
            while (move > 0 && phones[move - 1].screenDiameterInches > insert.screenDiameterInches){
                phones[move] = phones[move -1];
                --move;
            }
            phones[move]= insert;
        }
    }
    if(sortChoice == 3){
        for (c = 0; c < 20; c++){
            move = c;
            Phone insert = phones[c];
            
            while (move > 0 && phones[move - 1].customerRating > insert.customerRating){
                phones[move] = phones[move -1];
                --move;
            }
            phones[move]= insert;
        }
    }
    printPhones(phones);
}

//Prints the phones unsorted and sorted
void printPhones(Phone* phones){
    int i = 0;
    printf("List of phones:\n\n");
    for (i = 0; i < 20; i++){
        printf("%s %s:"
                "\nPrice: $%d"
                "\nScreen Size: %fin"
                "\nRating: %f"
                "\nIn Stock: %d\n\n", phones[i].brand, phones[i].model, phones[i].priceNoContract, phones[i].screenDiameterInches, phones[i].customerRating, phones[i].numInStock);
    }
    return;
}