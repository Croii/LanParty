#include "structures//trees_structure.h"

TreeNode *newNode(TeamNode *data);
void initTree(TreeNode **root, TeamNode *d);
TreeNode *insert(TreeNode *node, TeamNode *team);
void buildTree(TreeNode *root, TeamNode *team);
void printDescending(TreeNode *root, char *outputFilePath);
void sortNodesByName(TeamNode *team);