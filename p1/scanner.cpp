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
	else if(isOperator(ch) != -1) { //isOperator() is from token.h
		return 4;  //Operator is in column 4
	}
	else {
		return 5;  //No match for accepted categories, will error out
	}
}


void getError(int current_line, int state, char ch)
{
	cout << "[ERROR] at (" << current_line << ":" << current_scanner_pointer << ") -> {" << ch << "]: ";
	if(state == ERROR_INT) {
		cout << "all integer token must contain only digits." << endl;
		cout << "[ERROR] code: " << ERROR_INT << endl;
	}
	else if(state == ERROR_UNK) {
		cout << "unknown token is not allow." << endl;
		cout << "[ERROR] code: " << ERROR_UNK << endl;
	}
}


bool isCommenting = false;
string lastCommentPosition = "merp";
char checkComment(int current_line, char ch)
{
	if(ch == COMMENT_DELIMITER) {
		isCommenting = (isCommenting == true) ? false : true;
		
		if(isCommenting) {
			ostringstream temp;
			temp << current_line << ":" << current_scanner_pointer;
			lastCommentPosition = temp.str();
		}
		return SCANNER_DELIMITER;
	}

	if(isCommenting) {
		return SCANNER_DELIMITER;
	}
	else {
		return ch;
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
	string read_value;               //The current reading value of the token
	char next_char;                  //Keep track of the current token of the input

	//Continue looping until scanner pointer is less than or equal to the string it compare
	while(current_scanner_pointer <= input.length()) {
		if(current_scanner_pointer < input.length()) {
			next_char = checkComment(current_line, input.at(current_scanner_pointer));
		} 
		else {
			next_char = SCANNER_DELIMITER;
		}

		//Look at FSA Table and obtain the next state (row)
		next_category = getCategory(next_char);
		next_state = FSA_TABLE[current_state][next_category];

		//Check to see if this were an error state. Return -1 if it is.
		if(next_state < 0) {
			getError(current_line, next_state, next_char);
			//exit(EXIT_FAILURE);  //Uncomment this if you want the scanner to stop scanning when encounting error
		}
		//Check to see if this were the final state. Return 0 if it is.
		else if(next_state > STATE_F) {
			//Set the token	holder with the current token read value	
			tk.value = read_value;

			//Look for a specific final state and assign the token holder with appropriate id and value
			switch(next_state) {
				case STATE_ID: //Identfier
					if(getKeyword(tk) != -1) { //Keyword?
						tk.id = keywordTk;
						tk.value.append(" " + read_value);
					}
					else {
						tk.id = idTk;
						tk.value.assign("idTk " + read_value);
					}
					break;

				case STATE_INT: //Integer
					tk.id = intTk;
					tk.value.assign("intTk " + read_value);
					break;

				case STATE_OP: //Operator
					tk.id = opTk;
					
					//Check to see if it non-single operator
					if(current_scanner_pointer < input.length()) {
						string ns_operator = read_value + input.at(current_scanner_pointer);
						if(isNonSingleOperator(ns_operator) != -1) {
							read_value = ns_operator;
							current_scanner_pointer++;
						}
					}

					tk.value.assign(read_value);
					getOperator(tk);
					tk.value.append(" " + read_value);
					break;
			}

			if(isCommenting) {
				current_scanner_pointer++;
			}
			return 0;
		}

		//Update state and scanner pointer
		current_state = next_state;
		current_scanner_pointer++;

		//If not white space flager, update reading value of the token
		if(!isspace(next_char)) {
			read_value.push_back(next_char);
		}
	}

	//When scanner pointer is looking at the end of the input, end scanner.
	return -1;
}


void resetScannerPointer()
{
	current_scanner_pointer = 0;
}


void isCommentMode()
{
	if(isCommenting) {
		cout << "[WARNING] at (" << lastCommentPosition << ") -> comment tag never close, was this on purpose?" << endl;
	}
}

