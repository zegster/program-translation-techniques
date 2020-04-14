/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: scanner.h
# Date: 4/13/2020
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
#include <vector>        //Vectors are sequence containers representing arrays that can change in size.
#include "token.h"
using namespace std;

/* Scanner Class */
class Scanner: public Language
{
	private:
		//Scanner Tracker
		unsigned int current_scanner_pointer = -1;  //Keep track when the scanner is finish scanning the current input. Must init to 0.
		unsigned int current_line_number = 1;       //Keep track of the current line number.
		bool isCommenting = false;                  //Keep track when the scanner encounter a comment.
		string lastCommentPosition = "";            //Keep track the last known open comment tag.

		//All possible states in the FSA table
		enum {
			ERROR_UNK = -2,    //Error Unknown State
			ERROR_INT = -1,    //Error Integer State
			STATE_0 = 0,       //Initial
			STATE_1 = 1,       //Operator
			STATE_2 = 2,       //Identifier
			STATE_3 = 3,       //Integer
			STATE_F = 1000,    //Final State
			STATE_ID = 1001,   //Identifier Final State
			STATE_INT = 1003,  //Integer Final State
			STATE_OP = 1004,   //Operator Final State
			STATE_EOF = 1005   //EOF Final State
		};

		/* Visual representation of the FSA table: ROWS: 4 | COLUMNS: 6
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
		const int FSA_TABLE[4][6] = {
			{ STATE_2, STATE_3, STATE_0, STATE_EOF, STATE_1, ERROR_UNK },
			{ STATE_OP, STATE_OP, STATE_OP, STATE_OP, STATE_OP, ERROR_UNK },
			{ STATE_2, STATE_2, STATE_ID, STATE_ID, STATE_ID, ERROR_UNK },
			{ ERROR_INT, STATE_3, STATE_INT, STATE_INT, STATE_INT, ERROR_UNK }
		};

		//Scanner Delimiter
		const char SCANNER_DELIMITER = ' ';

		int getCategory(char ch);
		void getError(int state, char ch);
		char checkComment(char ch);

	public:
		Scanner();
		int scan(string &input, Token &tk);
		void isCommentMode();
		void invokeEOF(Token &tk);
};
#endif

