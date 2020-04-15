/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: testTree.h
# Date: 4/13/2020
==================================================================================================== */
#ifndef TESTTREE_H
#define TESTTREE_H
#include <cstring>       //Defines several functions to manipulate C strings and arrays.
#include <fstream>       //Input and output stream class to operate on files.
#include <iostream>      //For cout and cin; input and output.
#include <string>        //Introduces string types, character traits and a set of converting functions.
using namespace std;

void printToken(int level, set<string> token);
void traversePreorder(NodeT *root);

#endif

