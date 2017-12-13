/* 
 * File:   main.c
 * Author: Nicolle Lenzmeier
 * Lab F
 * Lab 8
 * NALYV2
 * Created on October 28, 2015, 11:56 AM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
typedef struct word_
{
    char word[10];
    struct word_* nextWord;
} Word;

#include <stdio.h>
#include <stdlib.h>

//Prototypes 
Word* addWordToSentence(Word*, Word*);
Word* deleteWordFromSentence(Word**);
Word* addWordToUndoList(Word*, Word*);
Word* deleteWordFromUndoList(Word**);
void printSentence(Word*);
void freeMemory(Word*, Word*);
/*
 * 
 */

//DO NOT TOUCH!!!!
int main(int argc, char** argv) {

    int choice;
    Word* justReadIn = NULL;
    Word* undoStack = NULL;
    Word* undoneWord = NULL;
    Word* redoneWord = NULL;
    Word* sentenceQ = NULL;
    while(1)
    {
        printf("1: add word\n2: undo\n3: redo\n4: quit\n");
        printf("Option:\n>");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1: 
                justReadIn = malloc(sizeof(Word));
                printf("Insert your word: ");
                scanf("%s", justReadIn->word);
                sentenceQ = addWordToSentence(sentenceQ, justReadIn);
                break;
            case 2:
                undoneWord = deleteWordFromSentence(&sentenceQ);
                undoStack = addWordToUndoList(undoStack, undoneWord);
                break;
            case 3:
                redoneWord = deleteWordFromUndoList(&undoStack);
                sentenceQ = addWordToSentence(sentenceQ, redoneWord);
                break;
            case 4:
                freeMemory(sentenceQ, undoStack);
                return 0;
                break;
            default:
                printf("Did not understand command. Try again.\n");
                break;
        }
        printf("\n");
        printSentence(sentenceQ);
        printf("\n");
    }
    return (EXIT_SUCCESS);
}

Word* addWordToSentence(Word* firstWord, Word* newWord)
{
    if (newWord == NULL){
        printf("No sentence here.\n");
        return firstWord;
    }
    if (firstWord == NULL){
        newWord->nextWord = NULL;
        return newWord;
    }
    else {
        newWord->nextWord = firstWord;
        return newWord;
    }
}
Word* deleteWordFromSentence(Word** firstWord)
{
    if (*firstWord == NULL){
        printf("No sentence here.\n");
        return NULL;
    }
    Word* temp = (*firstWord);
    (*firstWord) = temp->nextWord;
    temp->nextWord = NULL;
    return temp;
}
Word* addWordToUndoList(Word* lastUndone, Word* newestUndoneWord)
{
    if (newestUndoneWord == NULL){
        printf("Nothing to undo.\nNothing to print.\n");
        return lastUndone;
    }
    if (lastUndone == NULL){
        newestUndoneWord->nextWord = NULL;
        return newestUndoneWord;
    }
    else {
        newestUndoneWord->nextWord = lastUndone;
        return newestUndoneWord;
    }
}
Word* deleteWordFromUndoList(Word** lastUndone)
{
    if (*lastUndone == NULL){
        printf("Nothing to redo.\nNothing to print.\n");
        return NULL;
    }
    Word* temp = (*lastUndone);
    (*lastUndone) = temp->nextWord;
    temp->nextWord = NULL;
    return temp;
}

void printSentence(Word* firstWord)
{
    Word* last = NULL;
    last = firstWord;
    if (firstWord == NULL){
//        printf("Nothing to print.\n");
        return;
    }
    else {
            printSentence(firstWord->nextWord);
            printf("%s ", firstWord->word);        
    }
}

void freeMemory(Word* firstWord, Word* undoStack)
{
    Word* temp1 = firstWord;
    while (firstWord != NULL){
        temp1 = firstWord;
        firstWord = firstWord->nextWord;
        free(temp1);
    }
    
    Word* temp2 = undoStack;
    while (undoStack != NULL){
        temp2 = undoStack;
        undoStack = undoStack->nextWord;
        free(temp2);
    }
}


