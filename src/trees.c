#include "..//include//trees.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPS 10E-6

TreeNode *newNode(TeamNode *data) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->score = data->score;
    node->teamName = data->teamName;
    node->left = node->right = NULL;
    return node;
}

TreeNode *insert(TreeNode *node, TeamNode *team) {
    if (node == NULL)
        return newNode(team);
    if (team->score < node->score)
        node->left = insert(node->left, team);
    else if (team->score >= node->score)
        node->right = insert(node->right, team);
    return node;
}

//copy contents of value node
void initBstTree(TreeNode **root, TeamNode *value) {
    *root = (TreeNode *)malloc(sizeof(TreeNode));

    (*root)->score = value->score;
    (*root)->teamName = value->teamName;

    (*root)->left = (*root)->right = NULL;
}

void buildBstTree(TreeNode *root, TeamNode *team) {
    while (team != NULL) {
        insert(root, team);
        team = team->nextTeam;
    }
}

// inorder
void printDescending(TreeNode *root, char *outputFilePath) {

    if (root->right != NULL)
        printDescending(root->right, outputFilePath);

    FILE *outputFile = fopen(outputFilePath, "at");
    fprintf(outputFile, "%-34s-  %.2f\n", root->teamName, root->score);
    fclose(outputFile);

    if (root->left != NULL)
        printDescending(root->left, outputFilePath);
}

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

int max(int a, int b) {
    return ((a > b) ? a : b);
}

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

TreeNode *insertAvl(TreeNode **node, TreeNode *value) {
    // 1. inserare nod
    if (*node == NULL) {
        *node = (TreeNode *)calloc(1, sizeof(TreeNode));
        (*node)->score = value->score;
        (*node)->teamName = (char*)malloc(sizeof(value->teamName));
        strcpy((*node)->teamName, value->teamName);
        (*node)->height = 0;
        // optional
        (*node)->left = (*node)->right = NULL;
        return (*node);
    }
    if (value->score <= (*node)->score)
        (*node)->left = insertAvl(&(*node)->left, value);
    else
        (*node)->right = insertAvl(&(*node)->right, value);
    // 2. updateaza inaltimea nodurilor stramos
    // de jos in sus la iesirea din apelul recurent
    (*node)->height = 1 + max(nodeHeight((*node)->left), nodeHeight((*node)->right));
    // 3. afla factorul de echilibru al nodului stramos
    // testul se face de jos in sus ,
    // pentru toate nodurile intre cel adaugat si radacina
    int balance = (nodeHeight((*node)->left) - nodeHeight((*node)->right));
    // 4. daca nodul nu este echilibrat -¿ echilibreaza
    // LL Case
    if (balance > 1 && value->score <= (*node)->left->score)
        return RightRotation(*node);
    // RR Case
    // k ¡-1 ¡=¿ y este in dreapta
    // key ¿ valoarea din nodul drept =¿ x in dreapta lui y
    else if (balance < -1 && value->score >= (*node)->right->score)
        return LeftRotation((*node));
    // LR Case
    // k ¿1 ¡=¿ y este in stanga
    // key ¿ valoarea din nodul stang =¿ x in dreapta lui y
    else if (balance > 1 && value->score >= (*node)->left->score)
        return LRRotation((*node));
    // RL Case
    else if (balance < -1 && value->score <= (*node)->right->score)
        return RLRotation((*node));
    return *node;
}

// postorder
void insertFromBstToAVL(TreeNode *rootBst, TreeNode **rootAvl) {
    if (rootBst == NULL)
        return;

    insertFromBstToAVL(rootBst->right, rootAvl);
    (*rootAvl) = insertAvl(rootAvl, rootBst);
    insertFromBstToAVL(rootBst->left, rootAvl);
}

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

void freeTree(TreeNode **root) {
    if (*root == NULL)
        return;

    freeTree(&(*root)->left);
    freeTree(&(*root)->right);
    free((*root)->teamName);
    free(*root);
}
