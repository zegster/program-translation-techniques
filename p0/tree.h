/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: tree.h
# Date: 2/10/20
==================================================================================================== */
#ifndef TREE_H
#define TREE_H
#include "node.h"
#include <string>
using namespace std;


NodeT *buildTree(string file_name);
NodeT *createNode(int level, string label, string word);
NodeT *insert(NodeT *root, int level, string label, string word);
int getLevel(NodeT *root);

#endif

