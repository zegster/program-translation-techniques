/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: parser.cpp
# Date: 5/10/2020
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
	string output_file_name = "filter-parser-temp.dat";
	scanner.filterScan(file_name, output_file_name);

	file.open(output_file_name.c_str());
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
		node->c2 = stats();

		//Check if token is [rightCurlyTk]
		if((tk.id == opTk) && (operator_map[tk.value] == "rightCurlyTk")) {
			nextScan();
			return node;
		} else {
			parserError("block() : }");
		}
	} else {
		parserError("block() : {");
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
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
						parserError("vars() : ;");
					}
				} else {
					parserError("vars() : Integer");
				}
			} else {
				parserError("vars() : :=");
			}
		} else {
			parserError("vars() : Identifier");
		}
	} else {
		node->tokens.push_back(EMPTY_TK);
		return node;
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  expr()
* Definition  :  <expr> -> <N> - <expr> | <N>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::expr()
{
	//Create the node <expr>
	NodeT *node = createNode("<expr>");

	node->c1 = N();
	
	//Check if token is [minusTk]
	if((tk.id == opTk) && (operator_map[tk.value] == "minusTk")) {
		node->tokens.push_back(tk);  //Store the [minus] in this node
		nextScan();

		node->c2 = expr();
	}

	return node;
}


/* ====================================================================================================
* Function    :  N()
* Definition  :  <N> -> <A> / <N> | <A> * <N> | <A> 
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::N()
{
	//Create the node <N>
	NodeT *node = createNode("<N>");

	node->c1 = A();

	//Check if token is [opTk]
	if(tk.id == opTk) {
		//Check if token is [divideTk]
		if(operator_map[tk.value] == "divideTk") {
			node->tokens.push_back(tk);  //Store the [divide] in this node
			nextScan();

			node->c2 = N();
		}
		//Check if token is [multiplyTk]
		else if(operator_map[tk.value] == "multiplyTk") {
			node->tokens.push_back(tk);  //Store the [multiply] in this node
			nextScan();

			node->c2 = N();
		}
	}

	return node;
}


/* ====================================================================================================
* Function    :  A()
* Definition  :  <A> -> <M> + <A> | <M>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::A()
{
	//Create the node <A>
	NodeT *node = createNode("<A>");

	node->c1 = M();
	
	//Check if token is [plusTk]
	if((tk.id == opTk) && (operator_map[tk.value] == "plusTk")) {
		node->tokens.push_back(tk);  //Store the [plus] in this node
		nextScan();
		
		node->c2 = A();
	}	

	return node;
}


/* ====================================================================================================
* Function    :  M()
* Definition  :  <M> -> * <M> | <R>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::M()
{
	//Create the node <M>
	NodeT *node = createNode("<M>");

	//Check if token is [multiplyTk]
	if((tk.id == opTk) && (operator_map[tk.value] == "multiplyTk")) {
		node->tokens.push_back(tk);
		nextScan();

		node->c1 = M();
		return node;
	}

	node->c1 = R();
	return node;
}


/* ====================================================================================================
* Function    :  R()
* Definition  :  <R> -> ( <expr> ) | Identifier | Integer
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::R()
{
	//Create the node <R>
	NodeT *node = createNode("<R>");

	//Check if token is [leftParenTk]
	if((tk.id == opTk) && (operator_map[tk.value] == "leftParenTk")) {
		nextScan();

		node->c1 = expr();

		//Check if token is [rightParenTk]
		if((tk.id == opTk) && (operator_map[tk.value] == "rightParenTk")) {
			nextScan();
			return node;
		} else {
			parserError("R() : )");
		}
	}
	//Check if token is [idTk]
	else if(tk.id == idTk) {
		node->tokens.push_back(tk);  //Store the [identifier] in this node
		nextScan();
		return node;
	}
	//Check if token is [intTk]
	else if(tk.id == intTk) {
		node->tokens.push_back(tk);  //Store the [integer] in this node
		nextScan();
		return node;
	}
	else {
		parserError("R() : ( or Identifier or Integer");
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  stats()
* Definition  :  <stats> -> <stat> <mStat>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::stats()
{
	//Create the node <stats>
	NodeT *node = createNode("<stats>");

	node->c1 = stat();
	node->c2 = mStat();

	return node;
}


/* ====================================================================================================
* Function    :  mStat()
* Definition  :  <mStat> -> empty | <stat> <mStat>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::mStat()
{
	//Create the node <mStat>
	NodeT *node = createNode("<mStat>");

	//Check if token is [inTk], [outTk], [iffyTk], [loopTk], [labelTk], [gotoTk], [idTk] 
	if( 
		((tk.id == keywordTk) && ( 
			(keyword_map[tk.value] == "inTk") || (keyword_map[tk.value] == "outTk") ||
			(keyword_map[tk.value] == "iffyTk") || (keyword_map[tk.value] == "loopTk") ||
			(keyword_map[tk.value] == "labelTk") || (keyword_map[tk.value] == "gotoTk")
		)) || 
		((tk.id == opTk) && (operator_map[tk.value] == "leftCurlyTk")) ||
		(tk.id == idTk)
	) {
		node->c1 = stat();
		node->c2 = mStat();
		return node;
	} else {
		node->tokens.push_back(EMPTY_TK);
		return node;
	}
}


/* ====================================================================================================
* Function    :  stat()
* Definition  :  <stat> -> <in> ; | <out> ; | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ; | <block>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::stat()
{
	//Create the node <stat>
	NodeT *node = createNode("<stat>");

	//Check if token is [keywordTk]
	if(tk.id == keywordTk) {
		//Check if token is [inTk]
		if(keyword_map[tk.value] == "inTk") {
			nextScan();

			node->c1 = in();

			//Check if token is [semiColonTk]
			if((tk.id == opTk) && (operator_map[tk.value] == "semiColonTk")) {
				nextScan();
				return node;
			} else {
				parserError("stat() : ;");
			}
		}
		//Check if token is [outTk]
		else if(keyword_map[tk.value] == "outTk") {
			nextScan();

			node->c1 = out();

			//Check if token is [semiColonTk]
			if((tk.id == opTk) && (operator_map[tk.value] == "semiColonTk")) {
				nextScan();
				return node;
			} else {
				parserError("stat() : ;");
			}
		}
		//Check if token is [iffyTk]
		else if(keyword_map[tk.value] == "iffyTk") {
			nextScan();

			node->c1 = iffy();

			//Check if token is [semiColonTk]
			if((tk.id == opTk) && (operator_map[tk.value] == "semiColonTk")) {
				nextScan();
				return node;
			} else {
				parserError("stat() : ;");
			}
			return node;
		}
		//Check if token is [loopTk]
		else if(keyword_map[tk.value] == "loopTk") {
			nextScan();

			node->c1 = loop();

			//Check if token is [semiColonTk]
			if((tk.id == opTk) && (operator_map[tk.value] == "semiColonTk")) {
				nextScan();
				return node;
			} else {
				parserError("stat() : ;");
			}
			return node;
		}
		//Check if token is [labelTk]
		else if(keyword_map[tk.value] == "labelTk") {
			nextScan();

			node->c1 = label();

			//Check if token is [semiColonTk]
			if((tk.id == opTk) && (operator_map[tk.value] == "semiColonTk")) {
				nextScan();
				return node;
			} else {
				parserError("stat() : ;");
			}
			return node;
		}
		//Check if token is [gotoTk]
		else if(keyword_map[tk.value] == "gotoTk") {
			nextScan();

			node->c1 = goTo();

			//Check if token is [semiColonTk]
			if((tk.id == opTk) && (operator_map[tk.value] == "semiColonTk")) {
				nextScan();
				return node;
			} else {
				parserError("stat() : ;");
			}
			return node;
		} else {
			parserError("stat() : in or out or iffy or loop or label or goto or Identifier");
		}
	}
	//Check if token is [idTk]
	else if(tk.id == idTk) {
		/*NOTE: the scanner retrieves the next token before assign is called. 
		The identifer token will be lost if it not temporarily stored. */
		Token temp_tk = tk;
		nextScan();

		node->c1 = assign();
		node->c1->tokens.push_back(temp_tk);
		
		//Check if token is [semiColonTk]
		if((tk.id == opTk) && (operator_map[tk.value] == "semiColonTk")) {
			nextScan();
			return node;
		} else {
			parserError("stat() : semicolon");
		}
	} else {
		node->c1 = block();
		return node;
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  in()
* Definition  :  <in> -> in Identifier
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::in()
{
	//Create the node <in>
	NodeT *node = createNode("<in>");

	//Check if token is [idTk]
	if(tk.id == idTk) {
		node->tokens.push_back(tk);
		nextScan();
		return node;
	} else {
		parserError("in() : Identifier");
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  out()
* Definition  :  <out> -> out <expr>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::out()
{
	//Create the node <out>
	NodeT *node = createNode("<out>");

	node->c1 = expr();
	return node;
}


/* ====================================================================================================
* Function    :  iffy()
* Definition  :  <iffy> -> iffy [ <expr> <RO> <expr> ] then <stat>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::iffy()
{
	//Create the node <iffy>
	NodeT *node = createNode("<iffy>");

	//Check if token is [leftBracketTk]
	if((tk.id == opTk) && (operator_map[tk.value] == "leftBracketTk")) {
		nextScan();
		
		node->c1 = expr();
		node->c2 = RO();
		node->c3 = expr();
		
		//Check if token is [rightBracketTk]
		if((tk.id == opTk) && (operator_map[tk.value] == "rightBracketTk")) {
			nextScan();

			//Check if token is [thenTk]
			if((tk.id == keywordTk) && (keyword_map[tk.value] == "thenTk")) {
				nextScan();

				node->c4 = stat();
				return node;
			} else {
				parserError("iffy() : then");
			}
		} else {
			parserError("iffy() : ]");
		}
	} else {
		parserError("iffy() : [");
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  loop()
* Definition  :  <loop> -> loop [ <expr> <RO> <expr> ] <stat>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::loop()
{
	//Create the node <loop>
	NodeT *node = createNode("<loop>");

	//Check if token is [leftBracketTk]
	if((tk.id == opTk) && (operator_map[tk.value] == "leftBracketTk")) {
		nextScan();
		
		node->c1 = expr();
		node->c2 = RO();
		node->c3 = expr();
		
		//Check if token is [rightBracketTk]
		if((tk.id == opTk) && (operator_map[tk.value] == "rightBracketTk")) {
			nextScan();

			node->c4 = stat();
			return node;
		} else {
			parserError("loop() : ]");
		}
	} else {
		parserError("loop() : [");
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  assign()
* Definition  :  <assign> -> Identifier := <expr>
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::assign()
{
	//Create the node <assign>
	NodeT *node = createNode("<assign>");

	//Check if token is [colonEqualTk]
	if((tk.id == opTk) && (operator_map[tk.value] == "colonEqualTk")) {
		nextScan();

		node->c1 = expr();
		return node;
	} else {
		parserError("assign() : :=");
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  label()
* Definition  :  <label> -> label Identifier
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::label()
{
	//Create the node <label>
	NodeT *node = createNode("<label>");

	//Check if token is [idTk]
	if(tk.id == idTk) {
		node->tokens.push_back(tk);
		nextScan();
		return node;
	} else {
		parserError("label() : Identifier");
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  goTo()
* Definition  :  <goto> -> goto Identifier
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::goTo()
{
	//Create the node <goTo>
	NodeT *node = createNode("<goTo>");

	//Check if token is [idTk]
	if(tk.id == idTk) {
		node->tokens.push_back(tk);
		nextScan();
		return node;
	} else {
		parserError("goTo() : Identifier");
	}

	//An error has occur if code reach here
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  RO()
* Definition  :  <RO> -> < | << (two tokens) | > | >> (two tokens) | == (one token ==) | <> (two tokens) 
* Parameter   :  none. 
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *Parser::RO()
{
	//Create the node <RO>
	NodeT *node = createNode("<RO>");

	//Check if token is [opTk]
	if(tk.id == opTk) {
		/* CHECK: < | < < | < > */
		//Check if token is [lessThanTk]
		if((tk.id == opTk) && (operator_map[tk.value] == "lessThanTk")) {
			node->tokens.push_back(tk);
			nextScan();		

			if((tk.id == opTk) && (operator_map[tk.value] == "lessThanTk")) {
				node->tokens.push_back(tk);
				nextScan();
				return node;
			}
			else if((tk.id == opTk) && (operator_map[tk.value] == "greaterThanTk")) {
				node->tokens.push_back(tk);
				nextScan();
				return node;
			}
			else if((tk.id == opTk) && ((operator_map[tk.value] != "lessThanTk") || (operator_map[tk.value] != "greaterThanTk"))) {
				parserError("RO() : < or << or <>");
			} 
			else {
				return node;
			}
		}
		/* CHECK: > | > > */
		//Check if token is [greaterThanTk]
		else if((tk.id == opTk) && (operator_map[tk.value] == "greaterThanTk")) {
			node->tokens.push_back(tk);
			nextScan();		

			if((tk.id == opTk) && (operator_map[tk.value] == "greaterThanTk")) {
				node->tokens.push_back(tk);
				nextScan();
				return node;
			}
			else if((tk.id == opTk) && (operator_map[tk.value] != "greaterThanTk")) {
				parserError("RO() : > or >>");
			}
			else {
				return node;
			}
		}
		/* CHECK: == */
		//Check if token is [equalEqualTk]
		else if((tk.id == opTk) && (operator_map[tk.value] == "equalEqualTk")) {
			node->tokens.push_back(tk);
			nextScan();	
			return node;
		}
		//Anything that is not valid... 
		else {
			parserError("RO() : < or << or > or >> or == or <>");
		}
	} else {
		parserError("RO() : < or << or > or >> or == or <>");
	}
	
	//An error has occur if code reach here
	exit(EXIT_FAILURE);
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

		/* DEBUG ONLY
		if(scanner_status_code != -1) {
			scanner.tokenToString(tk);
		} */
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
void Parser::parserError(string expected_token)
{
	cout << "[PARSER ERROR] parsing error at " << scanner.getScannerPosition() << " -> expected " 
		<< expected_token << " -> but received " << tk.value << "" << endl;
	file.close();
	exit(EXIT_FAILURE);
}


/* ====================================================================================================
* Function    :  parse()
* Definition  :  constructing the parse tree from the start symbol.
* Parameter   :  none.
* Return      :  root node.
==================================================================================================== */
NodeT *Parser::parse()
{
	NodeT *root = NULL;
	nextScan();
	root = program();

	//Check the last token of the program return by the scanner is eofTk
	//If not eofTk, an error occur, display error message and exit with no recovery
	if(tk.id != eofTk) {
		parserError("parse() : EOF");
		exit(EXIT_FAILURE);
	} else {
		cout << "[INFO] parsing complete with no error... continue to the next step." << endl;
		file.close();
		return root; 
	}
}

