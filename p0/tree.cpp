/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: tree.cpp
# Date: 2/10/20
==================================================================================================== */
#include <iostream>      //For cout and cin; input and output.
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <cstring>       //Defines several functions to manipulate C strings and arrays.
#include <cctype>        //Classify and transform individual characters.
#include <fstream>       //Input and output stream class to operate on files.
#include "tree.h"
using namespace std;


/* ====================================================================================================
* Function    :  buildTree()
* Definition  :  read the data from an input file and build a binary search tree.
* Parameter   :  an input file name.
* Return      :  NodeT (the root of BST).
==================================================================================================== */
NodeT *buildTree(string file_name)
{
	NodeT *root = NULL;
	ifstream file(file_name.c_str());

	//Check if the file is open and associated with the stream object
	if(file.is_open())
	{
		//Read all line in the file
		string input;
		while(getline(file, input))
		{
			//Tokenize input into an array
			char *token = strtok(&input[0], " \t");

			//Loop through every word in the array
			while(token != NULL)
			{
				//Label the node (for comparison)
				string word = token;
				string label = word.substr(0, 2);

				//Add word to tree
				root = insert(root, 0, label, word);

				//Set the current token to null
				token = strtok(NULL, " \t");
			}
		}
	}
	else
	{
		cout << "[ERROR] Can't open file!" << endl;
		return NULL;
	}

	//Output a error message if root still null
	if(root == NULL)
	{
		cout << "[ERROR] Empty Input!" << endl;
	}
	file.close();
	return root;
}


/* ====================================================================================================
* Function    :  createNode()
* Definition  :  create an individual node based on given height, label, and word.
* Parameter   :  current node height, label (for comparasion), and word (tokens).
* Return      :  individual NodeT.
==================================================================================================== */
NodeT *createNode(int level, string label, string word)
{
	NodeT *temp_node = new NodeT;
	
	temp_node->level = level;
	temp_node->label = label;
	temp_node->words.insert(word);
	temp_node->left = NULL;
	temp_node->right = NULL;
	return temp_node;
}


/* ====================================================================================================
* Function    :  insert()
* Definition  :  insert a node into the BST.
* Parameter   :  the root of BST (first call), height of BST (should be zero at first call), label (for
                  comparsion), and word (tokens).
* Return      :  the node of BST).
==================================================================================================== */
NodeT *insert(NodeT *current_node, int level, string label, string word)
{
	if(current_node == NULL)
	{
		return createNode(level, label, word);
	}
	else if(label.compare(current_node->label) < 0)
	{
		current_node->left = insert(current_node->left, level + 1, label, word);
	}
	else if(label.compare(current_node->label) > 0)
	{
		current_node->right = insert(current_node->right, level + 1, label, word);
	}
	else if(label.compare(current_node->label) == 0)
	{
		current_node->words.insert(word);
	}

	return current_node;
}

