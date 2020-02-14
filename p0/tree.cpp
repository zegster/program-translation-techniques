/* ====================================================================================================
# Author: Duc Ngo
# Course: CS4280-002 - Program Translation Techniques
# File Name: tree.cpp
# Date: 2/10/20
==================================================================================================== */
#include <iostream>      //For cout and cin; input and output
#include <string>        //Introduces string types, character traits and a set of converting functions.
#include <cstring>       //Defines several functions to manipulate C strings and arrays.
#include <cctype>        //Classify and transform individual characters.
#include <fstream>       //Input/output stream class to operate on files.
#include "tree.h"
using namespace std;


static const int BUFFER_SIZE = 256;
static int tree_size = 0;
static int max_token_length = 0;


NodeT *buildTree(string file_name)
{
	NodeT *root = NULL;
	ifstream file(file_name.c_str());

	//Check if the file is open and assoicated with the stream object
	if(file.is_open())
	{
		//Read all line in the file
		string input;
		while(getline(file, input))
		{
			//Tokenize input into an array
			char *token = strtok(&input[0], " ");

			//Loop through every word in the array
			while(token != NULL)
			{
				//Loop through every character in the word
				string word = token;
				for(unsigned int i = 0; i < word.size(); i++)
				{
					//Check if each character is alphanumeric 
					if(!isalnum(word.at(i)))
					{
						cout << "[ERROR] Invalid character!" << endl;
						return NULL;
					}
				}

				//Set the current token to null
				token = strtok(NULL, " ");

				//Label the node (for comparison)
				string label = word.substr(0, 2);

				//Add word to tree
				root = insert(root, 0, label, word);
			}
		}
	}
	else
	{
		return NULL;
	}

	file.close();
	return root;
}


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

