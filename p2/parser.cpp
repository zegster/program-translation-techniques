/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: parser.cpp
# Date: 4/13/2020
==================================================================================================== */
#include "parser.h"

/* ====================================================================================================
* Function    :  Parser()
* Definition  :  setup file, check if file exist, and init scanner_status_code when this object is create.
* Parameter   :  none.
* Return      :  none.
==================================================================================================== */
Parser::Parser(string file_name)
{
	//Check if the file is open and associated with the stream object
	file.open(file_name.c_str());
	if(!file.is_open()) {
		cout << "[ERROR] Can't open file!" << endl;
		exit(EXIT_FAILURE);	
	}
	scanner_status_code = -1;
}


/* ====================================================================================================
* Function    :  program()
* Definition  :  <program> -> <vars><block>
* Parameter   :  none.
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::program()
{
	NodeT *node = createNode("<program>");
	return node;
}


/* ====================================================================================================
* Function    :  ()
* Definition  :  .
* Parameter   :  none.
* Return      :  none.
==================================================================================================== */
void Parser::nextParse()
{
	if(file.eof()) {
		scanner.isCommentMode();
		scanner.invokeEOF(tk);
		scanner.tokenToString(tk);
	} else {
		if(scanner_status_code == -1) {
			getline(file, file_input);
			scanner_status_code = scanner.scan(file_input, tk);
			scanner.tokenToString(tk);
		} else {
			scanner_status_code = scanner.scan(file_input, tk);
			scanner.tokenToString(tk);
		}
	}
}


/* ====================================================================================================
* Function    :  createNode()
* Definition  :  create an individual node based on given production name label.
* Parameter   :  production name label.
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::createNode(string production_name)
{
	NodeT *node = new NodeT;
	node->label = production_name;
	node->c1 = NULL;
	node->c2 = NULL;
	node->c3 = NULL;
	node->c4 = NULL;
	return node;
}


/* ====================================================================================================
* Function    :  parserError()
* Definition  :  print error message of the line number cursor position
* Parameter   :  none.
* Return      :  none.
==================================================================================================== */
void Parser::parserError()
{
	cout << "[ERROR] parsing error at " << scanner.getScannerPosition() << " -> expected [" 
		<< expected_token << "] but received [" << tk.value << "]" << endl;
}


/* ====================================================================================================
* Function    :  parse()
* Definition  :  .
* Parameter   :  .
* Return      :  .
==================================================================================================== */
NodeT *Parser::parse()
{
	NodeT *root = NULL;
	nextParse();
	//root = program();

	//Check the last token of the program return by the scanner is eofTk
	//If not eofTk, an error occur, display error message and exit with no recovery
	if(tk.id != eofTk) {
		expected_token.assign("EOF");
		parserError();
		exit(EXIT_FAILURE);
	} else {
		cout << "[INFO] parsing complete with no error... continue to the next step." << endl;
		return root; 
	}
}

