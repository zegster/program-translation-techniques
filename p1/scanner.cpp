/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: scanner.cpp
# Date: 3/8/2020
==================================================================================================== */
#include "scanner.h"

int getCategory(char ch)
{
	//Refer to FSA_TABLE in scanner.h
	//Check if alphabetic character
	if(isalpha(ch)) {
		return 0;  //Letter is in column 0
	}
	else if(isdigit(ch)) {
		return 1;  //Digit is in column 1	
	}
	else if(isspace(ch)) {
		return 2;  //White Space (WS) is in column 2
	}
	else if(isOperator(ch)) { //isOperator() is from token.h
		return 4;  //Operator is in column 4
	}
	else {
		return 5; //No match for accepted categories, will error out
	}
}


int scanner(int current_line, string &input, Token &tk)
{
	//Set current line number for the current token
	tk.line_number = current_line;

	//Init variable for tracking
	int current_state = 0;
	int next_fsa_tbl_row = 0;
	int next_fsa_tbl_col = 0;
	char next_char;

	unsigned int current_index = 0;
	while(current_index <= input.length()) {
		if(current_index < input.length()) {
			next_char = input.at(current_index);
		} 
		else {
			next_char = ' ';
		}

		next_fsa_tbl_col = getCategory(next_char);
		next_fsa_tbl_row = FSA_TABLE[current_state][next_fsa_tbl_col];
	}

	return -1;
}

