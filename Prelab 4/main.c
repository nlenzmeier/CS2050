/* 
 * File:   main.c
 * Author: Nicolle
 *
 * Created on September 18, 2015, 2:08 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct computer
{
	char serialNumber[8];
	int price;
	int GBofRAM;
	int GBofHardDrive;
} Computer;

Computer* readComputers(char* filename);
void printComputers(Computer* comps);
Computer* insertionSortByRAM(Computer* comps);
Computer* selectionSortByPrice(Computer* comps);

int main(int argc, char** argv) {
    if (argc != 2){
        printf("Invalid arguments!\n");
        return 1;
    }

    Computer *compute;
    compute = readComputers(argv[1]);
    printComputers(compute);
    Computer *C = insertionSortByRAM(compute);
    printComputers(C);
    Computer *com = selectionSortByPrice(C);
    printComputers(com);
   
    
    free(compute);
//    free(C);
//    free(CS);
    return (EXIT_SUCCESS);
}

Computer* readComputers(char* filename){
    FILE*fp = fopen("comp.txt", "r");
    if (fp == NULL){
        printf("Failed to open the file\n");
    }
    
    int x = 0;
    
    Computer *keyboard;
    keyboard=malloc(sizeof(Computer)*3);
    for (x= 0; x < 3; x++){
        fscanf(fp, "%s %d\n%d %d", keyboard[x].serialNumber, &keyboard[x].price, &keyboard[x].GBofRAM, &keyboard[x].GBofHardDrive);
        keyboard[x].serialNumber[7]='\0';
    }
    fclose(fp);
    return keyboard;
}

void printComputers(Computer* comps){
    int i=0;
    printf("List of Computers:\n\n");
    for (i = 0; i < 3; i++){
        printf("Serial Number: %s Price: $%d\n GB0fRAM: %d GBofHardDrive: %d\n\n", comps[i].serialNumber, comps[i].price, comps[i].GBofRAM, comps[i].GBofHardDrive);
    }
    return;
}

Computer* insertionSortByRAM(Computer* complist){
    int c, move, i;
    for (c=0; c<3; c++){
        move = c;
        Computer insert = complist[c];
                
        while(move > 0 && complist[move - 1].GBofRAM > insert.GBofRAM){
            complist[move] = complist[move-1];
            --move;
        }
        complist[move] = insert;
    }
    
    printf("\nSorted List by Insertion(RAM):\n");
    return complist;
}

Computer* selectionSortByPrice(Computer* comps){
    int smallest;
    int i, j;
    
    for(i=0; i < 3-1; i++){
        smallest = i;
        
        for(j = i + 1; j < 3; j++){
            if(comps[j].price < comps[smallest].price){
               smallest = j; 
            }
        }
                Computer temp = comps[i];
                comps[i] = comps[smallest];
                comps[smallest] = temp;
            }
    printf("\nSorted List by Selection (Price):\n");
    return comps;
}
