#include "..//include//trees.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void initTree(TreeNode **root, TeamNode *d) {
    *root = (TreeNode *)malloc(sizeof(TreeNode));
    (*root)->left = (*root)->right = NULL;
    (*root)->score = d->score;
    (*root)->teamName = d->teamName;
}

void buildTree(TreeNode *root, TeamNode *team) {
    while (team != NULL) {
        insert(root, team);
        team = team->nextTeam;
    }

}

void printDescending(TreeNode *root, char *outputFilePath) {
    
    if(root->right != NULL)
        printDescending(root->right, outputFilePath);
    
    FILE *outputFile = fopen(outputFilePath, "at");
    fprintf(outputFile, "%-34s-  %.2f\n", root->teamName, root->score);
    fclose(outputFile);
    
    if(root->left != NULL)
        printDescending(root->left, outputFilePath);
    
}

void sortNodesByName(TeamNode *team) {
    TeamNode *i = team;
    TeamNode *j = NULL;
    while (i->nextTeam) {
        j = i->nextTeam;
        while (j) {
            if (strcmp(i->teamName, j->teamName) > 0) {
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
