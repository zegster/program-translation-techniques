/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: node.h
# Date: 2/10/20
==================================================================================================== */
#ifndef NODE_H
#define NODE_H
#include <string>
#include <set>
using namespace std;


typedef struct node_t
{
	int level;                   //The level of this node
	int token_length;            //The length of tokens, or strings, of this node
	set<string> tokens;          //The set of tokens of this node
	struct node_t *left, *right;  //The left and right subtrees of this node
}NodeT;

#endif
