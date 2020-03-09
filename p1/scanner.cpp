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
		return 5;  //No match for accepted categories, will error out
	}
}


void getError(int current_line, int state, char ch)
{
	cout << "ERROR on line #" << current_line << " [" << ch << "]: ";
	if(state == ERROR_INT) {
		cout << "all integer token must contain only digits." << endl;
	}
	else if(state == ERROR_UNK) {
		cout << "unknown token is not allow." << endl;
	}
}



unsigned int current_scanner_pointer = 0;
int scanner(int current_line, string &input, Token &tk)
{
	//Set current line number for the current token
	tk.line_number = current_line;

	//Init variable for tracking
	int current_state = 0;           //Keep track of the current FSA state
	int next_state = 0;              //Refer to the row of FSA Table
	int next_category = 0;           //Refer to the column of FSA Table
	string token_value;              //The value of the token
	char next_char;                  //Keep track of the current token of the input

	while(current_scanner_pointer <= input.length()) {
		if(current_scanner_pointer < input.length()) {
			next_char = input.at(current_scanner_pointer);
		} 
		else {
			next_char = ' ';
		}

		//Look at FSA Table and obtain the next state (row)
		next_category = getCategory(next_char);
		next_state = FSA_TABLE[current_state][next_category];
		
		//Check to see if this were an error state
		if(next_state < 0) {
			getError(current_line, next_state, next_char);
			return -1;
		}
		else if(next_state > STATE_F) {
			switch(next_state)
			{
				case STATE_ID:
					if(isKeyword(tk) != -1) {
						tk.id = keywordTk;
					}
					else {
						tk.id = idTk;
						tk.value.assign("idTk " + token_value);
					}
					break;

				case STATE_INT:
					cout << "derp" << endl;
			}

			return 0;
		}

		current_state = next_state;
		current_scanner_pointer++;

		if(!isspace(next_char)) {
			token_value.push_back(next_char);
		}
	}

	return -1;
}


void resetScannerPointer()
{
	current_scanner_pointer = 0;
}
