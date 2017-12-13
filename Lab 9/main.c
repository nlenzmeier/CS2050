/* 
 * File:   main.c
 * Author: Nicolle Lenzmeier
 * Lab F
 * Lab 9
 * NALYV2
 * Created on November 4, 2015, 11:58 AM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct router
{
    int ID;
    int travelTimeToLeft;
    int travelTimeToRight;
    struct router* leftRouter;
    struct router* rightRouter;
} Router;

typedef struct packet
{
    int packetID;
    int destinationRouter;
} Packet;

Router* readInRouterData(char* filename);
Router* addTreeLeaf(Router* root, Router* newLeaf);
void handlePacketData(char* filename, Router* root);
Router* findRouter(int* timeElapsed, Router* root, Packet* packet);
void freeTree(Router* root);
Router* bonusRead(char* filename);
void mirrorTree(Router* root);
void printTree(Router* root);
int _printTree(Router *tree, int is_left, int offset, int depth, char s[20][255]);
/*
 * 
 */
int main(int argc, char** argv) {
    
    Router* root = readInRouterData(argv[1]);
    handlePacketData(argv[2], root);
//    Uncomment this if you are going to do the bonus.
//    Router* bonusRoot = bonusRead(argv[1]);
//    printTree(bonusRoot);
//    mirrorTree(bonusRoot);
//    printTree(bonusRoot);
    freeTree(root);
    return (EXIT_SUCCESS);
}

Router* readInRouterData(char* filename)
{
    Router* root = NULL;
    Router* leaf = NULL;
    
    FILE* fp=fopen(filename, "r");
    while (feof(fp) == 0){
        leaf = malloc(sizeof(Router));
        fscanf(fp, "%d %d %d", &leaf->ID, &leaf->travelTimeToLeft, &leaf->travelTimeToRight);
        leaf->leftRouter = NULL;
        leaf->rightRouter = NULL;
        root = addTreeLeaf(root, leaf);
    }
    fclose(fp);
    return root;
}

Router* addTreeLeaf(Router* root, Router* newLeaf)
{
    if (root == NULL){
        root = newLeaf;
        return root;
    }
    if (root->ID == newLeaf->ID){
        return root;
    }
    if( newLeaf->ID < root->ID){
        root->leftRouter = addTreeLeaf(root->leftRouter, newLeaf);
    }
    if (newLeaf->ID > root->ID){
        root->rightRouter = addTreeLeaf(root->rightRouter, newLeaf);
    }
   
    return root;
}

void handlePacketData(char* filename, Router* root)
{
    FILE* fp = fopen(filename, "r");
    Packet* packetPtr = malloc(sizeof(Packet));
    int time = 0;
    printf("\nBegin transmissions:\n");
    while(fscanf(fp, "%d %d", &(packetPtr->packetID), 
            &(packetPtr->destinationRouter)) == 2)
    {
        printf("Packet %d: searching for router %d...", packetPtr->packetID, 
                packetPtr->destinationRouter);
        Router* dest = findRouter(&time, root, packetPtr);
        if(!dest)
        {
            printf("Router not found for packet %d.\n", packetPtr->packetID);
        }
        else
        {
            printf("Router found. Travel time for packet: %d ms\n", time);
        }
        time = 0;
    }
    free(packetPtr);
    fclose(fp);
}

Router* findRouter(int* timeElapsed, Router* root, Packet* packet)
{
    if (root == NULL){
        return NULL;
    }
    if (root->ID == packet->destinationRouter){
        return root;
    }
    if (root->ID < packet->destinationRouter){
        *timeElapsed += root->travelTimeToRight;
        return findRouter(timeElapsed, root->rightRouter, packet);
    }
    if (root->ID > packet->destinationRouter){
        *timeElapsed += root->travelTimeToLeft;
       return findRouter(timeElapsed, root->leftRouter, packet);
    }
}

void freeTree(Router* root)
{
    if (root == NULL){
        return;
    }
    else {
        freeTree(root->leftRouter);
        freeTree(root->rightRouter);
        free(root);
    }
}

