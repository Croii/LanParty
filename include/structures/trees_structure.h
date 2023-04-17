#ifndef TREES_STRUCTURE_H
#define TREES_STRUCTURE_H

#include "team_structure.h"

typedef struct treeNode {
    char *teamName;
    float score;
    struct treeNode *left ,*right;
}TreeNode;


#endif
