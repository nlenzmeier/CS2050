/* 
 * File:   main.c
 * Author: Nicolle
 *
 * Created on November 1, 2015, 1:32 PM
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct router
{
    int ID;
    struct router* leftRouter;
    struct router* rightRouter;
} Router;
/*
 * 
 */

/*
 * You are to read in some router IDs, and create a BST out of it. 
 * After you create the tree, the program will print out a nice little
 * tree so you can check and see if nodes were added correctly. Then free 
 * the tree.
 * 
 * THERE ARE IMPORTANT NOTES DOWN BY THE PRINT TREE FUNCTION.
 */



Router* readInRouterData(char* filename);
Router* addTreeLeaf(Router* root, Router* newLeaf);
void freeTree(Router* root);
void printTree(Router* root);
int _printTree(Router *tree, int is_left, int offset, int depth, char s[20][255]);

//Don't have to touch main. It gets the root of the tree you made,
//then prints out the tree and calls your free implementation.
int main(int argc, char** argv) {
    Router* root = readInRouterData(argv[1]);
    printTree(root);
    freeTree(root);
    return (EXIT_SUCCESS);
}

//Input: the name of the file that has the router IDs
//Return: the root of the BST
//Read in each router ID, put that ID into a new node, then add the node to the
//tree using the addTreeLeaf function.
Router* readInRouterData(char* filename)
{
    Router* root = NULL;
    Router* leaf = NULL;
    
    FILE* fp=fopen(filename, "r");
    while (feof(fp) == 0){
        leaf = malloc(sizeof(Router));
        fscanf(fp, "%d", &leaf->ID);
        leaf->leftRouter = NULL;
        leaf->rightRouter = NULL;
        root = addTreeLeaf(root, leaf);
    }
    fclose(fp);
    return root;
    //Need a loop so you can get every node value from the file.
    
    //Make a node for every ID, add it to the tree. Repeat. 
    //Remember to keep track of the root!
    //Remember to do something with the pointers in the new nodes!
    
    //Return the root. Remember to close your file. 
}

//Input: the root of a BST, and the new node to be added.
//Return: the root of the tree/subtree.
//Use techniques learned in class to recursively go through the tree
//and add the new node to the tree.
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
    //Am I at an open spot in the tree?
    
    //Do I go left? 
    
    //Do I go right?
    
    //What do I return?
}

//Input: the root of a BST
//Return: none
//Free the tree, using techniques learned in class.
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
    //Free EVERYTHING.
    
    //NOTE: many people have expressed concern that there's no real way to test 
    //for memory leaks. To confirm: Netbeans has no way of testing such things.
    //Look at your code, and convince yourself you got everything.
    
    //You would have to download a C/C++ profiler, then attach the profiler to
    //Netbeans. Feel free to search around for how to do this. Alternatively, you
    //can get valgrind (easy to do on Linux/OSX, harder on Windows without a bash
    //program), and that can test for memory leaks (that is the only one I have experience
    //in).
}

/*
 * ***********************NOTICE*************************
 * (Please read me. I say things that are good to know)
 * 
 * The below code will print out the tree in a manner that looks like the 
 * picture on blackboard.
 * 
 * BUT:
 * 
 * A couple of things to note:
 * 1. The tree only prints nicely on a big enough screen. If your screen
 *    isn't big enough, then the tree will appear squished. I think most screens
 *    should handle it though. The computers in your lab room should be big enough,
 *    so use this as a comparison to your laptop. 
 *      1a. The code has only been tested on a 22" monitor. It's more than enough
 *          for it. So if it looks really weird, it's either your code, or the monitor
 *          you're using to read this.
 * 2. The print code only works for a small enough sample set (maximum 10 levels deep, 
 *    5 nodes wide, I think. THIS HAS NOT BEEN CONFIRMED.), and the sample set you
 *    have been provided is small enough. If you decide to implement your own data
 *    set, results may vary. You are free to modify the code in the print function
 *    and play with the variable to see how the output changes, but no guarantees
 *    on what will happen (you probably won't do this...nobody has time for that)
 * 
 * AND FINALLY, THE NOTE YOU CARE ABOUT MOST LIKELY
 * 3. You WILL DEFINITELY NOT be printing your tree in the lab. You only have this
 *    prelab to get your tree building right. The data set we will be using in lab
 *    will be much bigger, and cannot be printed out nicely using this code, or most
 *    code implementations in general. Getting the tree correctly built is the most
 *    important part, so GET IT RIGHT! 
 *  
 * 
 * 
 * I take no credit for coming up with this code. I found it on the Internet
 * in a forum. It worked for the data set I put together, so I used it.
 * 
 * 
 * 
 * 
 */

//IGNORE THIS FUNCTION
int _printTree(Router *tree, int is_left, int offset, int depth, char s[20][255])
{
    int i;
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->ID);

    int left  = _printTree(tree->leftRouter,  1, offset,                depth + 1, s);
    int right = _printTree(tree->rightRouter, 0, offset + left + width, depth + 1, s);

    for (i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }

    return left + width + right;
}

//IGNORE THIS FUNCTION TOO
void printTree(Router *tree)
{
    int i;
    char s[20][255];
    for (i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _printTree(tree, 0, 0, 0, s);

    for (i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}

