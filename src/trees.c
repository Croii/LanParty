#include "..//include//trees.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 10E-6

//function used to create a new node for the tree
TreeNode *newNode(TeamNode *value) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->score = value->score;
    node->teamName = value->teamName;
    node->left = node->right = NULL;
    return node;
}


//function used to insert a new node in the tree using a given team node
TreeNode *insert(TreeNode *node, TeamNode *team) {
    if (node == NULL)
        return newNode(team);

    if (team->score < node->score)
        node->left = insert(node->left, team);

    else if (team->score >= node->score)
        node->right = insert(node->right, team);
        
    return node;
}

//function used to intialize a bst tree given a team node
void initBstTree(TreeNode **root, TeamNode *value) {
    *root = (TreeNode *)malloc(sizeof(TreeNode));
    (*root)->score = value->score;
    (*root)->teamName = value->teamName;
    (*root)->left = (*root)->right = NULL;
}

//function used to build a bst tree given a team node list
void buildBstTree(TreeNode *root, TeamNode *team) {
    while (team != NULL) {
        insert(root, team);
        team = team->nextTeam;
    }
}

//function used to print the tree in descending order
void printDescending(TreeNode *root, char *outputFilePath) {

    if (root->right != NULL)
        printDescending(root->right, outputFilePath);

    FILE *outputFile = fopen(outputFilePath, "at");
    fprintf(outputFile, "%-34s-  %.2f\n", root->teamName, root->score);
    fclose(outputFile);

    if (root->left != NULL)
        printDescending(root->left, outputFilePath);
}

//function used to sort a team node list by name in ascending order
void sortNodesByName(TeamNode *team) {
    TeamNode *i = team;
    TeamNode *j = NULL;
    while (i->nextTeam) {
        j = i->nextTeam;
        while (j) {
            if (strcasecmp(i->teamName, j->teamName) > 0) {
                char *auxCh = i->teamName;
                i->teamName = j->teamName;
                j->teamName = auxCh;

                float auxIn = i->score;
                i->score = j->score;
                j->score = auxIn;
            }

            j = j->nextTeam;
        }
        i = i->nextTeam;
    }
}

//function used to return the maximum of two integers
int max(int a, int b) {
    return ((a > b) ? a : b);
}

//function used to calculate the height of a node
int nodeHeight(TreeNode *root) {
    if (root == NULL)
        return -1;
    else
        return root->height;
}


TreeNode *LeftRotation(TreeNode *z) {
    TreeNode *y = z->right;
    TreeNode *T2 = y->left;
    y->left = z;
    z->right = T2;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;

    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}


TreeNode *LRRotation(TreeNode *Z) {
    Z->left = LeftRotation(Z->left);
    return RightRotation(Z);
}

TreeNode *RLRotation(TreeNode *Z) {
    Z->right = RightRotation(Z->right);
    return LeftRotation(Z);
}

TreeNode *RightRotation(TreeNode *z) {
    TreeNode *y = z->left;
    TreeNode *T3 = y->right;
    y->right = z;
    z->left = T3;
    z->height = max(nodeHeight(z->left), nodeHeight(z->right)) + 1;
    y->height = max(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    return y;
}

//function used to insert a node in an avl tree
TreeNode *insertToAvl(TreeNode **node, TreeNode *value) {
    // 1. inserare nod
    if (*node == NULL) {
        *node = (TreeNode *)calloc(1, sizeof(TreeNode));
        (*node)->score = value->score;
        (*node)->teamName = (char*)malloc(strlen(value->teamName) + 1);
        strcpy((*node)->teamName, value->teamName);
        (*node)->height = 0;
        // optional
        (*node)->left = (*node)->right = NULL;
        return (*node);
    }
    if (value->score <= (*node)->score)
        (*node)->left = insertToAvl(&(*node)->left, value);
    else
        (*node)->right = insertToAvl(&(*node)->right, value);
    
    //update height
    (*node)->height = 1 + max(nodeHeight((*node)->left), nodeHeight((*node)->right));
    
    //compute balance factor of this node to check whether this node became unbalanced
    int balance = (nodeHeight((*node)->left) - nodeHeight((*node)->right));

    //LL Case
    if (balance > 1 && value->score <= (*node)->left->score)
        return RightRotation(*node);
    //RR Case
    else if (balance < -1 && value->score >= (*node)->right->score)
        return LeftRotation((*node));
    // LR Case
    else if (balance > 1 && value->score >= (*node)->left->score)
        return LRRotation((*node));
    // RL Case
    else if (balance < -1 && value->score <= (*node)->right->score)
        return RLRotation((*node));

    return *node;
}

//function used to insert nodes from a bst tree to an avl tree in inorder traversal
void insertFromBstToAVL(TreeNode *rootBst, TreeNode **rootAvl) {
    if (rootBst == NULL)
        return;

    insertFromBstToAVL(rootBst->right, rootAvl);
    (*rootAvl) = insertToAvl(rootAvl, rootBst);
    insertFromBstToAVL(rootBst->left, rootAvl);
}

//function used to print the tree in postorder traversal
void printPostOrder(TreeNode *root, char *outputFilePath) {
    if (root->left) {
        printPostOrder(root->left, outputFilePath);
    }
    if (root->right) {
        printPostOrder(root->right, outputFilePath);
    }
    FILE *outputFile = fopen(outputFilePath, "at");
    fprintf(outputFile, "%f ", root->score);
    fclose(outputFile);
}

//function used to print the tree level by level
void printLevel(TreeNode *root, int level, char *outputFilePath) {
    if (root == NULL)
        return;
    if (level == 1) {
        FILE *outputFile = fopen(outputFilePath, "at");
        fprintf(outputFile, "%s\n", root->teamName);
        fclose(outputFile);
    } else if (level > 1) {
        printLevel(root->right, level - 1, outputFilePath);
        printLevel(root->left, level - 1, outputFilePath);
    }
}


//function used to deallocate the memory used by a tree
void freeTree(TreeNode **root) {
    if (*root == NULL)
        return;

    //postorder traversal
    freeTree(&(*root)->left);
    freeTree(&(*root)->right);
    
    //free the team name and the node
    free((*root)->teamName);
    free(*root);
}

