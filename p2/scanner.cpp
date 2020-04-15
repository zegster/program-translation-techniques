/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: scanner.cpp
# Date: 4/13/2020
==================================================================================================== */
#include "scanner.h"

/* ====================================================================================================
* Function    :  Scanner()
* Definition  :  invoke initOperatorMap() and initKeywordMap() when this object is create.
* Parameter   :  none.
* Return      :  none.
==================================================================================================== */
Scanner::Scanner()
{
	initOperatorMap();
	initKeywordMap();
}


/* ====================================================================================================
* Function    :  getCategory()
* Definition  :  return the category column number when a match is found.
* Parameter   :  char.
* Return      :  none.
==================================================================================================== */
int Scanner::getCategory(char ch)
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


/* ====================================================================================================
* Function    :  getError()
* Definition  :  print the appropriate error message base on the error stage.
* Parameter   :  the error state (int) and input character (char).
* Return      :  none.
==================================================================================================== */
void Scanner::getError(int state, char ch)
{
	cout << "[ERROR] at " << getScannerPosition() << " -> {" << ch << "]: ";
	if(state == ERROR_INT) {
		cout << "all integer token must contain only digits." << endl;
		cout << "[ERROR] code: " << ERROR_INT << endl;
	}
	else if(state == ERROR_UNK) {
		cout << "unknown token is not allow." << endl;
		cout << "[ERROR] code: " << ERROR_UNK << endl;
	}
}


/* ====================================================================================================
* Function    :  checkComment()
* Definition  :  check for comment delimiter and ignore all the input if found one. Once an ending tag
                  is found, restore scanner back to normal operation.
* Parameter   :  input character (char).
* Return      :  none.
==================================================================================================== */
char Scanner::checkComment(char ch)
{
	if(ch == COMMENT_DELIMITER) {
		is_commenting = !is_commenting;
		
		if(is_commenting) {
			ostringstream temp;
			temp << current_line_number << ":" << current_scanner_pointer;
			last_comment_position = temp.str();
		}
		return SCANNER_DELIMITER;
	}

	if(is_commenting) {
		return SCANNER_DELIMITER;
	}
	else {
		return ch;
	}
}


/* ====================================================================================================
* Function    :  getScannerPosition()
* Definition  :  get the scanner current line and cursor position.
* Parameter   :  none.
* Return      :  the scanner current position message.
==================================================================================================== */
string Scanner::getScannerPosition()
{
	ostringstream temp;
	temp << "(" << current_line_number << ":" << current_scanner_pointer << ")";
	return temp.str();
}


/* ====================================================================================================
* Function    :  isCommentMode()
* Definition  :  check if comment tag still open, if it, then display a warning message.
* Parameter   :  none.
* Return      :  none.
==================================================================================================== */
void Scanner::isCommentMode()
{
	if(is_commenting) {
		cout << "[WARNING] at (" << last_comment_position << ") -> comment tag never close" << endl;
	}
}


/* ====================================================================================================
* Function    :  invokeEOF()
* Definition  :  invoke end of file procedure (only call this if it end of file).
* Parameter   :  none.
* Return      :  none.
==================================================================================================== */
void Scanner::invokeEOF(Token &tk)
{
	//Check if the current line is the initial line. If not, reduce by 1
	tk.line_number = (current_line_number > 1) ? current_line_number - 1 : current_line_number;
	tk.id = eofTk;
	tk.value = "EOF";
}


/* ====================================================================================================
* Function    :  scan()
* Definition  :  main function that identify the token using the state transition table, and if the 
                  table does not return an error state.
* Parameter   :  input (string), and token holder (struct Token). 
* Return      :  return negative number if error.
==================================================================================================== */
int Scanner::scan(string &input, Token &tk)
{
	//Set current line number for the current token
	tk.line_number = current_line_number;

	//Init variable for tracking
	int current_state = 0;           //Keep track of the current FSA state
	int next_state = 0;              //Refer to the row of FSA Table
	int next_category = 0;           //Refer to the column of FSA Table
	string read_value;               //The current reading value of the token
	char next_char;                  //Keep track of the current token of the input

	//Continue looping until scanner pointer is less than or equal to the string it compare
	while(current_scanner_pointer <= input.length()) {
		if(current_scanner_pointer < input.length()) {
			next_char = checkComment(input.at(current_scanner_pointer));
		} 
		else {
			next_char = SCANNER_DELIMITER;
		}

		//Look at FSA Table and obtain the next state (row)
		next_category = getCategory(next_char);
		next_state = FSA_TABLE[current_state][next_category];

		//Check to see if this were an error state. Return -1 if it is.
		if(next_state < 0) {
			getError(next_state, next_char);
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
						tk.value.assign(read_value);
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
					tk.value.assign(read_value);
					break;
			}

			//Increment scanner pointer when open comment tag is found
			if(is_commenting) {
				current_scanner_pointer++;
			}
			return 0;
		}

		//Update state and scanner pointer
		current_state = next_state;
		current_scanner_pointer++;

		//If not white space, update reading value of the token
		if(!isspace(next_char)) {
			read_value.push_back(next_char);
		}
	}

	//When scanner pointer is looking at the end of the input, end scanner.
	current_scanner_pointer = 0;
	current_line_number++;
	return -1;
}

