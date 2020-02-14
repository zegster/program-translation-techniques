/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: traversal.h
# Date: 2/10/20
==================================================================================================== */
#ifndef TRAVERSAL_H
#define TRAVERSAL_H
#include "node.h"

void printToken(ofstream &file, int level, set<string> token);
void traverseInorder(ofstream &file, NodeT *root);
void traversePreorder(ofstream &file, NodeT *root);
void traversePostorder(ofstream &file, NodeT *root);
#endif

