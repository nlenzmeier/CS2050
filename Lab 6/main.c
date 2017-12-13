/* 
 * File:   main.c
 * Author: Nicolle
 * NALYV2
 * Lab F
 * Lab 6
 * Created on October 7, 2015, 11:58 AM
 */

//You are free to use this definition if you wish.
#define SIZE 8

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct square
{
    int surroundingMines;
    int isCovered;
    int isAMine;
} Square;
/*
 * 
 */

//given prototypes
Square** randomizeBoard(void);
void printBoard(Square** board);
int updateBoard(Square** board, int row, int column);
void printUncoveredBoard(Square** board);
int countMines(Square** board, int i, int j);
void uncoverNeighbors(Square** board, int i, int j);
int checkGameState(Square** board);

int main(int argc, char** argv) {

    srand(time(NULL));
    Square** board = randomizeBoard();
    int gameOver, gameWon;
    while(1)
    {
        printBoard(board);
        //printUncoveredBoard(board);
        
        int gameWon = checkGameState(board);
        if(gameWon == 1)
        {
            printf("\nYou won! Congratulations!\n");
            return 0;
        }
        printf("\n\nEnter the row of the space you want to hit: ");
        int row;
        scanf("%d", &row);
        while (row >= SIZE){
            printf("Incorrect option. Enter again:");
            scanf("%d", &row);
        }

        printf("\nEnter the column of the space you want to hit: ");
        int column;
        scanf("%d", &column);
        while (column >= SIZE){
            printf("Incorrect option. Enter again:");
            scanf("%d", &column);
        }
            
        gameOver = updateBoard(board, row, column);
        if(gameOver == 1)
        {
            printf("\nYou hit a mine! Game Over");
            printUncoveredBoard(board);
            return 0;
        }
        
    }
    
    return (EXIT_SUCCESS);
}


//Given funciton. Prints out our matrix
void printBoard(Square** squares)
{
    int i, j;
    printf("\x1B[0m\n\n");
    printf("\x1B[0m\t   Columms:\n");
    printf("         0 1 2 3 4 5 6 7");
    for(i = 0; i < SIZE; i++)
    {
        printf("\x1B[0m\nRow %d -> ", i);
        for(j = 0; j < SIZE; j++)
        {
            if(squares[i][j].isCovered == 1)
            {
                printf("\x1B[0mx ");
            }
            else if (squares[i][j].surroundingMines == 0) 
            {
                printf("\x1B[32m%d ", squares[i][j].surroundingMines);
            } else {
                printf("\x1B[33m%d ", squares[i][j].surroundingMines);
            }
        }
    }
}

//mallocs space for our matrix. Creates random spots where our mines are
Square** randomizeBoard(void){
    int ROW = SIZE;
    int COL = SIZE;

    Square** matrix = malloc(sizeof(Square*)*ROW);
    
    int i;
    for (i = 0; i < ROW; i++){
        matrix[i] = calloc(sizeof(Square),COL);
    }
    
    int x;
    for(x =0; x<15; x++){
        int row = rand()%SIZE;
        int col = rand()%SIZE;
        matrix[row][col].isAMine = 1;
    }
    
    int y, z;
    for(y= 0; y < SIZE; y++){
        for(z = 0; z < SIZE; z++){
            matrix[y][z].surroundingMines = countMines(matrix, y, z);
            matrix[y][z].isCovered=1;
        }
    }
    return matrix;
}


//Counts the amount of "M" around the desired position. Returns it to randomizeBoard to print the board properly.
int countMines(Square** board, int i, int j){
    int count = 0;
    int x, y;
    if (i -1 >= 0){
        if (j-1 >= 0){
            if (board[i-1][j-1].isAMine){
                count ++;
            }  
        }
        
        if (board[i-i][j].isAMine){
            count++;
        }
        
        if (board[i-1][j+1].isAMine){
            count++;
        }
    }
    
    if (j - 1 >= 0){
        if (board[i][j-1].isAMine){
            count++;
        } 
    }
    
    if (j + 1 < SIZE){
        if (board[i][j+1].isAMine){
            count++;
        }
    }
    
    if (i + 1 < SIZE){
        if (j-1 >= 0){
            if (board[i+1][j-1].isAMine){
                count++;
            }
        }
        
        if (board[i+1][j].isAMine){
            count++;
        }
        
        if (board[i+1][j+1].isAMine){
            count++;
        }
    }
    return count;
}

//Updates the board when an option is selected
int updateBoard(Square** board, int row, int column){
    board[row][column].isCovered=0;
    if (board[row][column].isAMine==1){
        return 1;
    }
    return 0;   
}

//Uncovers neighbors to an option that is returned zero
void uncoverNeighbors(Square** board, int i, int j){
    if (i -1 >= 0){
        if (j-1 >= 0){
           board[i-1][j-i].isCovered=0; 
        }
        
        if (board[i-i][j].isAMine){
            board[i-1][j].isCovered=0;
        }
        
        if (board[i-1][j+1].isAMine){
            board[i-1][j+1].isCovered=0;
        }
    }
    
    if (j - 1 >= 0){
        if (board[i][j-1].isAMine){
            board[i][j-1].isCovered=0;
        } 
    }
    
    if (j + 1 < SIZE){
        if (board[i][j+1].isAMine){
            board[i][j+1].isCovered=0;
        }
    }
    
    if (i + 1 < SIZE){
        if (j-1 >= 0){
            if (board[i+1][j-1].isAMine){
                board[i+1][j-1].isCovered=0;
            }
        }
        
        if (board[i+1][j].isAMine){
            board[i+1][j].isCovered=0;
        }
        
        if (board[i+1][j+1].isAMine){
            board[i+1][j+1].isCovered=0;
        }
    }
    return;
}

//prints the board when the player loses the game and a mine is hit
void printUncoveredBoard(Square** squares)
{
    int i, j;
    printf("\x1B[0m\n\n");
    printf("\x1B[0m\t   Columms:\n");
    printf("         0 1 2 3 4 5 6 7");
    for(i = 0; i < SIZE; i++)
    {
        printf("\x1B[0m\nRow %d -> ", i);
        for(j = 0; j < SIZE; j++)
        {
            if(squares[i][j].isAMine)
            {
                printf("\x1B[31mM ");
            }
            else if (squares[i][j].surroundingMines == 0) 
            {
                printf("\x1B[32m%d ", squares[i][j].surroundingMines);
            } else {
                printf("\x1B[33m%d ", squares[i][j].surroundingMines);
            }
        }
    }
}

int checkGameState(Square** board){
   
    int i=0, j=0;
    for(i=0; j<SIZE; i++){
        for(j=0; j<SIZE; j++){
            if(board[i][j].isCovered == 1){
                if (board[i][j].isAMine == 0){
                    return 0;
                }
            }
        }
    }
    
    free(board);
    return 1;
}
