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


NodeT *buildTree(istream &in);
NodeT *create_node(string token);
NodeT *insert(NodeT *node, string token);
void getLevel(NodeT *root);
int findLevel(NodeT *root, int token_length);
int assignLevel(NodeT*, int token_length, int level);

#endif

