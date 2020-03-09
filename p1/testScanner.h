/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: testScanner.h
# Date: 3/8/2020
==================================================================================================== */
#ifndef TESTSCANNER_H
#define TESTSCANNER_H
#include <iostream>      //For cout and cin; input and output.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <cstring>       //Defines several functions to manipulate C strings and arrays.
#include <fstream>       //Input and output stream class to operate on files.
using namespace std;

/* TestScanner Function Prototype */
int testScanner(string file_name);
int filter(string &);
int isValidChar(char);

#endif

