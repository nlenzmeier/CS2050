#include "game.h" 

bossDecision* addDecisionNodeToList(bossDecision* top, bossDecision* newTop)
{
    if(!top){
        return newTop;
    }
    
    if (!newTop){
        printf("NO NEW TOP.\n");
        return NULL;
    }
    
    newTop->next = top;
    return newTop;
}

bossDecisionNode* addNodeToDecisionTree(bossDecisionNode* root, bossDecisionNode* newNode)
{
    if(!root){
        newNode->leftNode = NULL;
        newNode->rightNode = NULL;
        return newNode;
    }
    
    else if (newNode->healthMax < root->healthMin){
        root->leftNode = addNodeToDecisionTree(root->leftNode, newNode);
        return root;
    } else {
        root->rightNode = addNodeToDecisionTree(root->rightNode, newNode);
        return root;
    }
}

bossDecision* getNewListInTree(bossDecisionNode* root, int currentBossHealth)
{
    if (root==NULL){
        return NULL;
    }
    if(currentBossHealth < root->healthMax && currentBossHealth >= root->healthMin){
        return root->topOfStack;
    }
    else if (currentBossHealth < root->healthMin){
        return getNewListInTree(root->rightNode, currentBossHealth);
    }

    else{
        return getNewListInTree(root->leftNode, currentBossHealth);
    }
}