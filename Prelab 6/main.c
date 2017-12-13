/* 
 * File:   main.c
 * Author: Nicolle
 *
 * Created on October 1, 2015, 8:10 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 8
#define COLUMNS 8

/*
 * 
 */
typedef struct square{
    int i;
    char c;
} Square;

//prototypes. See below for more details
Square** initializeMatrix(void);
void printMatrixNumbers(Square**);
void printMatrixLetters(Square**);
void shuffleMatrix(Square**);

Square* initialize1DMatrix(void);
void print1DMatrixLetters(Square*);
void print1DMatrixNumbers(Square*);
void shuffle1DMatrix(Square*);


//Don't touch this code!
int main(void)
{
    srand(time(NULL));

    Square** matrix = initializeMatrix();
    
    while(1)
    {
        printf("Print which set?: ");
        printf("\n1. letters\n2. numbers\n3. shuffle matrix\n4. move to 1D matrix");
        printf("\n>");
        int choice;
        scanf("%d", &choice);

        if(choice == 1)
        {
            printMatrixLetters(matrix);
        }
        else if(choice == 2)
        {
            printMatrixNumbers(matrix);
        }
        else if(choice == 3)
        {
            shuffleMatrix(matrix);
        }
        else if(choice == 4)
        {
            break;
        }
        else
        {
            printf("Didn't understand that input. Try again\n\n");
        }
    }

    Square* matrix2 = initialize1DMatrix();
    printf("\n\nNow for the 1D array:\n\n");
    
    while(1)
    {
        int choice;
        printf("Print which set?: ");
        printf("\n1. letters\n2. numbers\n3. shuffle matrix\n4. quit");
        printf("\n>");
        scanf("%d", &choice);
        
        if(choice == 1)
        {
            print1DMatrixLetters(matrix2);
        }
        else if(choice == 2)
        {
            print1DMatrixNumbers(matrix2);
        }
        else if(choice == 3)
        {
            shuffle1DMatrix(matrix2);
        }
        else if(choice == 4)
        {
            break;
        }
        else
        {
            printf("Didn't understand that input. Try again\n\n");
        }
    }
    
    return 0;
}
//End of main code


//Alright, let's start doing things! This function will initialize the DOUBLE POINTER for the 2D Matrix, and 
//return the address back to main.
Square** initializeMatrix()
{
    //this will be used to randomize the matrix. See below for more info.
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 
    
    //I've got rows and columns in the matrix, as defined at the top of the program. 
    int row, column;
    
    /*********************************************************************************/
    //Here's the double pointer! You should probably have it point to something first! But what? CAREFUL!
    Square** matrix = malloc(sizeof(Square*)*ROWS);
    
    //Here's where that initial array of pointers all get their own array of elements, signifying columns.
    //How does each pointer get its own array to point to?
    for(row = 0; row < ROWS; row++)
    {
        /*********************************************************************************/
        //You should be doing something here! What is the for loop doing again?
        *(matrix+row)=malloc(sizeof(Square)*COLUMNS);
    }

    //Now it's time for all elements to get values!
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //Each element needs a number and a character assigned to it.
                //For the number, you should do a random number from 0-9. You should know how to do this.
                //For the character, use the array at the beginning of this function. Get a random number from
                //0-25, and use that as the index to get the character from the above array. 
                
                //Give that number and character to the matrix element here.
                Square temp;
                temp.i = rand()%9;
                temp.c = letters[rand()%25];
                *(*(matrix+row)+column)=temp;
            }
    }

    return matrix;
}

//Prints out each matrix element's number nicely. See the output for a pretty box.
void printMatrixNumbers(Square** matrix)
{
    int row, column;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //How should I print out that element again? Which part of the element am I printing here?
                printf("%d   ", (*(*(matrix+row)+column)).i);
            }
            printf("\n");
    }
}

//Prints out each matrix element's letter nicely. See the output for a pretty box.
void printMatrixLetters(Square** matrix)
{
    int row, column;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //How should I print out that element again? Which part of the element am I printing here?
                printf("%c   ", (*(*(matrix+row)+column)).c);  
            }
            printf("\n");
    }
}

//This function will take the randomly generated matrix, and shuffle around elements doing a very basic swap.
//Doesn't shuffle the matrix very well (in a random enough way), but that's fine...we'll just do it about 50000 times. 
void shuffleMatrix(Square** matrix)
{
    int randRow, randColumn, randRow2, randColumn2, passNumber = 0;
    Square tmp;
    
    for(passNumber; passNumber < 50000; passNumber++)
    {
        /*********************************************************************************/
        //Here you will get random numbers for each row/column pair. Each row/column pair will
        //get you one of the elements that will be swapped.
        
        //Once you know which 2 elements you will be swapping, swap them! You should know how 
        //to do this from sorting. 
        
    }
}

//Here begins the 2D Matrix code to represent it using a single pointer! 
Square* initialize1DMatrix(void)
{
    //Same stuff as before. 
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; 
    
    /*********************************************************************************/
    //Now we have a single pointer. This probably should be pointing to something...but what?
    Square* matrix;
    
    //Woah, what is this thing?! We've got the above pointer keeping track of where the beginning is,
    //but we need this other pointer to go down the line and assign values to each element. This is so that
    //all the elements will be changed, but we can still keep track of the beginning with the above variable!
    Square* ticker = matrix;

    int row, column;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //USE THE TICKER! The ticker should always point to the current element that needs new
                //random values. Calculate the random values just like before, and assign the values
                //to the element that ticker is pointing to.
                
                //then after that, how does the ticker get to the next element? POINTER MATH
                
            }
    }

    return matrix;
}

//Prints out each matrix element's letter nicely. See the output for a pretty box.
void print1DMatrixLetters(Square* matrix)
{
    //IT'S THE TICKER AGAIN!
    Square* ticker = matrix; 
    
    int column, row;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //How should I print out that element again? Which part of the element am I printing here?
                //BUT WAIT! I CAN ONLY USE THE TICKER! DON'T MOVE THE POINTER 'MATRIX'!
                    
            }
            printf("\n");
    }
}

//Prints out each matrix element's number nicely. See the output for a pretty box.
void print1DMatrixNumbers(Square* matrix)
{
    //SO MANY TICKERS!
    Square* ticker = matrix; 
    
    int column, row;
    for(row = 0; row < ROWS; row++)
    {
            for(column = 0; column < COLUMNS; column++)
            {
                /*********************************************************************************/
                //How should I print out that element again? Which part of the element am I printing here?
                //BUT WAIT! I CAN ONLY USE THE TICKER! DON'T MOVE THE POINTER 'MATRIX'!
                   
            }
            printf("\n");
    }
}

//This function will take the randomly generated matrix, and shuffle around elements doing a very basic swap.
//Doesn't shuffle the matrix very well (in a random enough way), but that's fine...we'll just do it about 50000 times. 
void shuffle1DMatrix(Square* matrix)
{
    //literally the same stuff as before.
    int randRow, randColumn, randRow2, randColumn2,passNumber = 0;
    Square tmp;
    
    for(passNumber; passNumber < 50000; passNumber++)
    {
        /*********************************************************************************/
        //Same thing as before. Get the row/column pairs for the 2 elements to be swapped
        
        //But....but it's a SINGLE POINTER! This is the hardest part of the whole prelab!
        //I can't treat the single pointer like the double pointer, so how do I use 
        //the row and column values to get to the element I need? Once you figure it out,
        //swap the two elements as before.
        
    }
}
