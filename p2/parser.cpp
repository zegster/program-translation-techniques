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
	
	EMPTY_TK.value = "EMPTY";
	scanner_status_code = 0;
	getline(file, file_input);
}


/* ====================================================================================================
* Function    :  program()
* Definition  :  <program> -> <vars> <block>
* Parameter   :  none.
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::program()
{
	//Create the node <program>
	NodeT *node = createNode("<program>");

	node->c1 = vars();
	node->c2 = block();
	
	cout << "done program" << endl;
	return node;
}


/* ====================================================================================================
* Function    :  block()
* Definition  :  <block> -> { <vars> <stats> }
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::block()
{
	//Create the node <block>
	NodeT *node = createNode("<block>");
	
	//Check if token is [leftCurlyTk]
	if((tk.id == opTk) && (operator_map[tk.value] == "leftCurlyTk")) {
		nextScan();

		node->c1 = vars();
		//node->c2 = stats();

		//Check if token is [rightCurlyTk]
		if((tk.id == opTk) && (operator_map[tk.value] == "rightCurlyTk")) {
			nextScan();
			return node;
		} else {
			expected_token.assign("rightCurlyTk");
			parserError();
			exit(EXIT_FAILURE);
		}
	} else {
		expected_token.assign("leftCurlyTk");
		parserError();
		exit(EXIT_FAILURE);
	}
}


/* ====================================================================================================
* Function    :  vars()
* Definition  :  <vars> -> empty | declare Identifier := Integer ; <vars>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::vars()
{
	//Create the node <vars>
	NodeT *node = createNode("<vars>");

	//Check if token is [declareTk]
	if((tk.id == keywordTk) && (keyword_map[tk.value] == "declareTk")) {
		nextScan();

		//Check if the token is [idTk]
		if(tk.id == idTk) {
			node->tokens.push_back(tk);  //Store the [identifier] in this node
			nextScan();

			//Check if the token is [colonEqualTk]
			if((tk.id == opTk) && (operator_map[tk.value] == "colonEqualTk")) {
				nextScan();
				
				//Check if the token is [intTk]
				if(tk.id == intTk) {
					node->tokens.push_back(tk);  //Store the [integer] in this node
					nextScan();
					
					//Check if the token is [semiColonTk]
					if((tk.id == opTk) && (operator_map[tk.value] == "semiColonTk")) {
						nextScan();
						
						node->c1 = vars();

						return node;
					} else {
						expected_token.assign("semiColonTk");
						parserError();
						exit(EXIT_FAILURE);
					}
				} else {
					expected_token.assign("intTk");
					parserError();
					exit(EXIT_FAILURE);
				}
			} else {
				expected_token.assign("colonEqualTk");
				parserError();
				exit(EXIT_FAILURE);
			}
		} else {
			expected_token.assign("idTk");
			parserError();
			exit(EXIT_FAILURE);
		}
	} else {
		node->tokens.push_back(EMPTY_TK);
		return node;
	}
}










/* ====================================================================================================
* Function    :  nextScan()
* Definition  :  determine whether renew the current input line or use the current input line. Also
                  determine if end of file has reach.
* Parameter   :  none.
* Return      :  none.
==================================================================================================== */
void Parser::nextScan()
{
	do {
		if(scanner_status_code == -1) {
			if(!getline(file, file_input)) {
				if(file.eof()) {
					scanner.isCommentMode();
					scanner.invokeEOF(tk);
					return;
				}
			}
		}
	
		scanner_status_code = scanner.scan(file_input, tk);
		scanner.tokenToString(tk);  //DEBUG only
	} while(scanner_status_code == -1);
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
	nextScan();
	root = program();

	//Check the last token of the program return by the scanner is eofTk
	//If not eofTk, an error occur, display error message and exit with no recovery
	if(tk.id != eofTk) {
		expected_token.assign("eofTk");
		parserError();
		exit(EXIT_FAILURE);
	} else {
		cout << "[INFO] parsing complete with no error... continue to the next step." << endl;
		return root; 
	}
}

