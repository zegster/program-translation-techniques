/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: semantics.cpp
# Date: 5/10/2020
==================================================================================================== */
#include "semantics.h"

/* ====================================================================================================
* Function    :  Semantics()
* Definition  :  setup mapping and output file.
* Parameter   :  none.
* Return      :  none.
==================================================================================================== */
Semantics::Semantics(string file_name)
{
	//Init mapping
	initOperatorMap();
	initKeywordMap();	

	//Construct output file name [.asm]
	output_file_name.assign(file_name + ".asm");
	file.open(output_file_name.c_str());
}


/* ====================================================================================================
* Function    :  checkDeclare()
* Definition  :  check if the given token is already in the symbol table. Append if not. Error if so.
* Parameter   :  Token to check.
* Return      :  none.
==================================================================================================== */
void Semantics::checkDeclare(Token id, Token val)
{
	//Find the given variable in the symbol table. If exist, then it is already declare and should error
	int is_declared = -1;
	for(unsigned int i = 0; i < st.size(); i++) {
		if(st[i].identifier.value == id.value) {
			is_declared = i;
			break;
		}
	}

	//If positive, then the variable is already declared
	if(is_declared > -1) {
		cout << "[SEMANTICS ERROR] the variable [" << id.value << "] on line (" << id.line_number <<
		") -> has already been declared on line (" << st[is_declared].identifier.line_number << ")" << endl;
		exit(EXIT_FAILURE);  //Comment this out to continue semantic check
	} else {
		st_holder.identifier = id;
		st_holder.value = val;
		st.push_back(st_holder);
	}
}


/* ====================================================================================================
* Function    :  checkDefined()
* Definition  :  check if the given token is defined in the symbol table. Error if not.
* Parameter   :  Token to check.
* Return      :  none.
==================================================================================================== */
void Semantics::checkDefined(Token tk)
{
	//Find the given variable in the symbol table. If exist, then it is already declare and should error
	int is_declared = -1;
	for(unsigned int i = 0; i < st.size(); i++) {
		if(st[i].identifier.value == tk.value) {
			is_declared = i;
			break;
		}
	}

	//If positive, then the variable is declared. If not, then should error
	if(is_declared < 0) {
		cout << "[SEMANTICS ERROR] the variable [" << tk.value << "] on line (" << tk.line_number <<
		") -> is not on the stack and not yet been declared" << endl;
		exit(EXIT_FAILURE);  //Comment this out to continue semantic check
	}
}


/* ====================================================================================================
* Function    :  validate()
* Definition  :  check for any violations of the static semantics.
* Parameter   :  the root of the parse tree.
* Return      :  none.
==================================================================================================== */
void Semantics::validate(NodeT *node)
{
	if(node == NULL) {
		return;
	}

	//Check for <vars> label
	if(node->label == "<vars>") {
		for(unsigned int i = 0; i < node->tokens.size(); i++) {
			if(node->tokens[i].id == idTk && node->tokens[i].value != "EMPTY") {
				checkDeclare(node->tokens[i], node->tokens[i + 1]);
			}
		}
	}
	//Check for other label (whether identifier is defined or not)
	else {
		vector<string> labels = { "<R>", "<in>", "<assign>", "<label>", "<goTo>" };
		for(unsigned int i = 0; i < labels.size(); i++) {
			if(node->label == labels[i]) {
				for(unsigned int ii = 0; ii < node->tokens.size(); ii++) {
					if(node->tokens[ii].id == idTk) {
						checkDefined(node->tokens[ii]);
					}
				}
			}
		}
	}

	validate(node->c1);
	validate(node->c2);
	validate(node->c3);
	validate(node->c4);
}


void Semantics::generate(NodeT *node)
{
	if(node == NULL) {
		return;
	}

	//* <program> -> <vars> <block>
	if(node->label == "<program>") {
		generate(node->c1);
		generate(node->c2);
		
		//Program stopping point
		file << "STOP" << endl;

		//Initialize global variable and temporary variable
		for(unsigned int i = 0; i < st.size(); i++) {
			file << st[i].identifier.value << " " << st[i].value.value << endl;
		}
		for(unsigned int i = 0; i < current_temp_vars_num; i++) {
			file << "_T" << i << " 0" << endl; 
		}

		return;
	}

	//* <block> -> { <vars> <stats> }
	if(node->label == "<block>") {
		generate(node->c1);
		generate(node->c2);
		return;
	}

	//* <vars> -> empty | declare Identifier := Integer ; <vars>
	if(node->label == "<vars>") {
		generate(node->c1);
		return;
	}

	//* <expr> -> <N> - <expr> | <N>
	if(node->label == "<expr>") {
		if(node->tokens.empty()) {
			generate(node->c1);
		} else {
			int vars_num = current_temp_vars_num++;
			
			generate(node->c2);
			file << "STORE _T" << vars_num << endl;
			generate(node->c1);

			if(operator_map[node->tokens[0].value] == "minusTk") {
				file << "SUB _T" << vars_num << endl;
			}
		}
		return;
	}

	//* <N> -> <A> / <N> | <A> * <N> | <A> 
	if(node->label == "<N>") {
		if(node->tokens.empty()) {
			generate(node->c1);
		} else {
			int vars_num = current_temp_vars_num++;
			
			generate(node->c2);
			file << "STORE _T" << vars_num << endl;
			generate(node->c1);
			
			if(operator_map[node->tokens[0].value] == "divideTk") {
				file << "DIV _T" << vars_num << endl;
			}
			else if(operator_map[node->tokens[0].value] == "multiplyTk") {
				file << "MULT _T" << vars_num << endl;
			}
		}
		return;
	}

	//* <A> -> <M> + <A> | <M>
	if(node->label == "<A>") {
		if(node->tokens.empty()) {
			generate(node->c1);
		} else {
			int vars_num = current_temp_vars_num++;
			
			generate(node->c2);
			file << "STORE _T" << vars_num << endl;
			generate(node->c1);
			
			if(operator_map[node->tokens[0].value] == "plusTk") {
				file << "ADD _T" << vars_num << endl;
			}
		}
		return;
	}

	//* <M> -> * <M> | <R>
	if(node->label == "<M>") {
		generate(node->c1);
		if(!node->tokens.empty()) {
			file << "MULT -1" << endl;
		}
		return;
	}

	//* <R> -> ( <expr> ) | Identifier | Integer
	if(node->label == "<R>") {
		if(node->tokens.empty()) {
			generate(node->c1);
		} else {
			Token tk = node->tokens[0];
			file << "LOAD " << tk.value << endl;
		}
		return;
	}

	//* <stats> -> <stat> <mStat>
	if(node->label == "<stats>") {
		generate(node->c1);
		generate(node->c2);
		return;
	}

	//* <mStat> -> empty | <stat> <mStat>
	if(node->label == "<mStat>") {
		if(node->tokens.empty()) {
			generate(node->c1);
			generate(node->c2);
		}
		return;
	}

	//* <stat> -> <in> ; | <out> ; | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ; | <block>
	if(node->label == "<stat>") {
		generate(node->c1);
		return;
	}

	//* <in> -> in Identifier
	if(node->label == "<in>") {
		file << "READ " << node->tokens[0].value << endl;
		return;
	}

	//* <out> -> out <expr>
	if(node->label == "<out>") {
		int vars_num = current_temp_vars_num++;
		
		generate(node->c1);
		file << "STORE _T" << vars_num << endl;
		file << "WRITE _T" << vars_num << endl;
		
		return;
	}

	//* <iffy> -> iffy [ <expr> <RO> <expr> ] then <stat>
	if(node->label == "<iffy>") {
		int vars_num = current_temp_vars_num++;

		generate(node->c1);
		file << "STORE _T" << vars_num << endl;
		generate(node->c3);
		file << "SUB _T" << vars_num << endl;

		int exit_loop_num = current_labels_num;
		carry_labels_num = current_labels_num++;
		generate(node->c2);
		generate(node->c4);
		file << "_L" << exit_loop_num << ": NOOP" << endl;

		return;
	}

	//* <loop> -> loop [ <expr> <RO> <expr> ] <stat>
	if(node->label == "<loop>") {
		int loop_num = current_labels_num++;
		int vars_num = current_temp_vars_num++;

		file << "_L" << loop_num << ": NOOP" << endl;
		generate(node->c1);
		file << "STORE _T" << vars_num << endl;
		generate(node->c3);
		file << "SUB _T" << vars_num << endl;
		
		int exit_loop_num = current_labels_num;
		carry_labels_num = current_labels_num++;
		generate(node->c2);
		generate(node->c4);
		file << "BR _L" << loop_num << endl;
		file << "_L" << exit_loop_num << ": NOOP" << endl;

		return;
	}

	//* <assign> -> Identifier := <expr>
	if(node->label == "<assign>") {
		generate(node->c1);
		file << "STORE " << node->tokens[0].value << endl;
		return;
	}

	//* <label> -> label Identifier
	if(node->label == "<label>") {
		file << node->tokens[0].value << ": NOOP" << endl;
	}

	//* <goto> -> goto Identifier
	if(node->label == "<goto>") {
		file << "BR " << node->tokens[0].value << endl;
	}

	//* <RO> -> < | << (two tokens) | > | >> (two tokens) | == (one token ==) | <> (two tokens)
	if(node->label == "<RO>") {
		/* CHECK: < | < < | < > */
		if(operator_map[node->tokens[0].value] == "lessThanTk") {
			if(node->tokens.size() > 1 && operator_map[node->tokens[1].value] == "lessThanTk") {
				file << "BRNEG _L" << carry_labels_num << endl;
			}
			else if(node->tokens.size() > 1 && operator_map[node->tokens[1].value] == "greaterThanTk") {
				file << "BRZERO _L" << carry_labels_num << endl;
			} else {
				file << "BRZNEG _L" << carry_labels_num << endl;
			}
		}
		/* CHECK: > | > > */
		else if(operator_map[node->tokens[0].value] == "greaterThanTk") {
			if(node->tokens.size() > 1 && operator_map[node->tokens[1].value] == "greaterThanTk") {
				file << "BRPOS _L" << carry_labels_num << endl;
			} else {
				file << "BRZPOS _L" << carry_labels_num << endl;
			}
		}
		/* CHECK: == */
		else if(operator_map[node->tokens[0].value] == "equalEqualTk") {
			file << "BRNEG _L" << carry_labels_num << endl;
			file << "BRPOS _L" << carry_labels_num << endl;
		}
		
		return;
	}
}


void Semantics::codeGeneration(NodeT *node)
{
	validate(node);
	cout << "[INFO] semantic validate complete with no error... continue to the next step." << endl;
	generate(node);
	cout << "[INFO] code generation complete..." << endl;
	cout << "[INFO] file output => \"" << output_file_name << "\"" << endl;
	file.close();
}

