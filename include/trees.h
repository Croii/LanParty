#include "structures//trees_structure.h"

TreeNode *newNode(TeamNode *data);
void initBstTree(TreeNode **root, TeamNode *value);
TreeNode *insert(TreeNode *node, TeamNode *team);
void buildBSTTree(TreeNode *root, TeamNode *team);
void printDescending(TreeNode *root, char *outputFilePath);
void sortNodesByName(TeamNode *team);
TreeNode* LRRotation(TreeNode *Z);
TreeNode* RLRotation( TreeNode *Z);
TreeNode *RightRotation(TreeNode *z);
TreeNode* LeftRotation(TreeNode *z);
int nodeHeight(TreeNode *root);
int max(int a,int b);
TreeNode *insertAvl(TreeNode **node, TreeNode *value);

void printPostOrder(TreeNode *root, char *outputFilePath);
void printLevel(TreeNode* root, int level, char *outputFilePath);
void insertFromBstToAVL(TreeNode *rootBst, TreeNode **rootAvl);
void insertInList(TeamNode **root, TreeNode **value);
void freeTree(TreeNode **root);