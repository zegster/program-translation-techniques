/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: scanner.h
# Date: 3/8/2020
==================================================================================================== */
#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>      //For cout and cin; input and output.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <cstring>       //Defines several functions to manipulate C strings and arrays.
#include <cctype>        //Classify and transform individual characters.
#include <cstdlib>       //Defines several general purpose functions.
#include <sstream>       //Header providing string stream classes.
#include <cstdio>        //Composes a string with the same text that would be printed.
#include "token.h"
using namespace std;

/* The FSA table with rows (states) and columns (categories) */
const int ROWS = 4;
const int COLUMNS = 6;

/* All possible states in the FSA table */
const int ERROR_UNK = -3;    //Error Unknown State
const int ERROR_INV = -2;
const int ERROR_INT = -1;    //Error Integer State
const int STATE_0 = 0;
const int STATE_1 = 1;
const int STATE_2 = 2;
const int STATE_3 = 3;
const int STATE_F = 1000;    //Final State
const int STATE_ID = 1001;   //Identifier Final State
const int STATE_INT = 1003;  //Integer Final State
const int STATE_OP = 1004;   //Operator Final State
const int STATE_EOF = 1005;  //EOF Final State

/* Visual representation of the FSA table:
-------------------------------------------------------------------------
| letter    | digit     | ws        | EOF       | operator  | other     |
-------------------------------------------------------------------------
| STATE_2   | STATE_3   | STATE_0   | STATE_EOF | STATE_1   | ERROR_UNK | s0 (initial)
-------------------------------------------------------------------------
| STATE_OP  | STATE_OP  | STATE_OP  | STATE_OP  | STATE_OP  | ERROR_UNK | s1 (operator)
-------------------------------------------------------------------------
| STATE_2   | STATE_2   | STATE_ID  | STATE_ID  | STATE_ID  | ERROR_UNK | s2 (identifier)
-------------------------------------------------------------------------
| ERROR_INT | STATE_3   | STATE_INT | STATE_INT | STATE_INT | ERROR_UNK | s3 (integer)
-------------------------------------------------------------------------
*/
const int FSA_TABLE[ROWS][COLUMNS] = {
	{ STATE_2, STATE_3, STATE_0, STATE_EOF, STATE_1, ERROR_UNK },
	{ STATE_OP, STATE_OP, STATE_OP, STATE_OP, STATE_OP, ERROR_UNK },
	{ STATE_2, STATE_2, STATE_ID, STATE_ID, STATE_ID, ERROR_UNK },
	{ ERROR_INT, STATE_3, STATE_INT, STATE_INT, STATE_INT, ERROR_UNK }
};


/* Scanner Tracker */
extern unsigned int current_scanner_pointer; //Keep track when the scanner is finish scanning the current input. Must init to 0.
extern bool isCommenting;                    //Keep track when the scanner encounter a comment.
extern string lastCommentPosition;

/* Scanner Delimiter */
const char SCANNER_DELIMITER = ' ';

/* Scanner Function Prototype */
int getCategory(char ch);
void getError(int current_line, int state, char ch);
char checkComment(int current_line, char ch);
int scanner(int current_line, string &input, Token &tk);
void resetScannerPointer();
void isCommentMode();

#endif

