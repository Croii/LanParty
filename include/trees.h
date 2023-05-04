#include "structures//trees_structure.h"

TreeNode *newNode(TeamNode *data);
void initTree(TreeNode **root, TeamNode *d);
TreeNode *insert(TreeNode *node, TeamNode *team);
void buildTree(TreeNode *root, TeamNode *team);
void printDescending(TreeNode *root, char *outputFilePath);
void sortNodesByName(TeamNode *team);
TreeNode* LRRotation(TreeNode *Z);
TreeNode* RLRotation( TreeNode *Z);
TreeNode *RightRotation(TreeNode *z);
TreeNode* LeftRotation(TreeNode *z);
int nodeHeight(TreeNode *root);
int max(int a,int b);
TreeNode *insertAvl(TreeNode **node, TreeNode *value);

void printPostOrder(TreeNode * root, char * outputFilePath);
void printLevel(TreeNode* root, int level, char *outputFilePath);
void insertFromBstToAVL(TreeNode *rootBst, TreeNode **rootAvl);
void extractFromBstToList(TreeNode *root, TeamNode **listForAvl);
void insertInList(TeamNode **root, TreeNode **value);
void insertFromListToAvl(TreeNode **rootAvl, TeamNode **listAvl);
void sortNodesByValue(TeamNode *team);