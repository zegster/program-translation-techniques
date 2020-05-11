/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: testTree.cpp
# Date: 5/10/2020
==================================================================================================== */
#include "testTree.h"

/* ====================================================================================================
* Function    :  traversePreorder()
* Definition  :  Preorder traversal of the BST.
* Parameter   :  Root node of BST, node depth, prefix indentation, and whether this node is the last.
* Return      :  none.
==================================================================================================== */
void traversePreorder(NodeT *node, int depth, string indent, bool last)
{
	if(node == NULL) {
		return;
	}

	//Indentation Symbol
	string indent_symbol = "";
	if(depth > 0) {
		indent_symbol = (last) ? "└─ " : "├─ ";
	} else {
		indent_symbol = ">> ";
	}
	cout << indent << indent_symbol << node->label << " ";

	//Label Production
	for(unsigned int i = 0; i < node->tokens.size(); i++) {
		cout << node->tokens[i].value;

		//Separate multiple tokens on a node by a comma
		if(((i + 1) != node->tokens.size()) && (node->tokens[i].id != opTk)) {
			cout << ",";
		}
		cout << " ";
	}
	cout << endl;


	//Setting up appropriate indent level
	indent += (last) ? "   " : "│  ";
	vector<NodeT *> nodes;
	if(node->c1 != NULL) {
		nodes.push_back(node->c1);
	}
	if(node->c2 != NULL) { 
		nodes.push_back(node->c2);
	}
	if(node->c3 != NULL) {
		nodes.push_back(node->c3);
	}
	if(node->c4 != NULL) {
		nodes.push_back(node->c4);
	}

	//Continue printing the rest of the node
	for(unsigned int i = 0; i < nodes.size(); i++) {
		traversePreorder(nodes[i], depth + 1, indent, i == nodes.size() - 1);
	}
}

