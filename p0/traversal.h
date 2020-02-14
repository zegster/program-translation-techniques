/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: traversal.h
# Date: 2/10/20
==================================================================================================== */
#ifndef TRAVERSAL_H
#define TRAVERSAL_H
#include "node.h"

void printToken(string output_file_name, int level, set<string> token);
void traverseInorder(string output_file_name, NodeT *root);
void traversePreorder(string output_file_name, NodeT *root);
void traversePostorder(string output_file_name, NodeT *root);
#endif
