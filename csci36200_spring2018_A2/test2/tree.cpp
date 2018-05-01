// Binary Search Tree - Implemenation in C++
// Simple program to create a BST of integers and search an element in it 
#include<ctype.h>
#include<string.h>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;
//Definition of Node for Binary search tree
struct Node {
	string data;
	int pos[100];
	int index = 0;
	Node* left;
	Node* right;
};

// Function to create a new Node
Node* GetNewNode(string data,int cpos) {
	Node* newNode = new Node();
	newNode->pos[newNode->index] = cpos; //populate new node with data
	newNode->index++;
	newNode->data = data;
	newNode->left = newNode->right = NULL;
	return newNode;
}

// To insert data in BST, returns address of root node 
Node* Insert(Node* root,string data,int cpos) {
	//cout << "inserting" << data << "\n";
	if(root == NULL) { // empty tree
		root = GetNewNode(data,cpos);
	}
	// if data to be inserted is less, insert in left subtree. 
	if(root->data.compare(data) > 0) {
		root->left = Insert(root->left,data,cpos);
	}
	// if greater insert in right subtree. 
	if(root->data.compare(data) < 0){
		root->right = Insert(root->right,data,cpos);
	}
	//if the item is already in the tree set the position
	if(root->data.compare(data) == 0){
		root->pos[root->index] = cpos;
		root->index++;
		//cout<< root->data << " " << data << "\n";
		//cout<<"Word already in tree\n";
	}
	return root;
}

void PrintTree(Node* root){ //prints tree using inorder notation
	if(root->left != NULL){ //first path down the left part of the subtree
		PrintTree(root->left);
	}
	cout<< root->data << " "; //prints data
	for(int y = 1;y < root->index;y++){ //prints the positions the word is found
		cout<< root->pos[y] << " ";
	}
	cout<<"\n";
	if(root->right != NULL){ //recurse down right part of the subtree
		PrintTree(root->right);
	}
}

void destroyTree(Node* root){ //destructor for the tree
        if(root == NULL) return;
        if(root->left != NULL) destroyTree(root->left);
        if(root->right != NULL) destroyTree(root->right);
        delete root;
        return;
}

int main(int ac , char *av[]) {
	Node* root = NULL;  // creates tree
	//FILE *fp;
	char test;
	int len;
	int x = 1; //keeps track of line number
	if(ac < 2){
		cout<< "Syntax: tree [filename]\n";//tests to see if a file location was passed
		return 0;
	}
	ifstream file (av[1]); //opens file passed as arg
	if(file.is_open()){ //checks to see if file can be opened
		string line; //creates strings and vector to store tokenized input line
		vector <string> tokens;
		string temp;
		while(getline(file,line)){ //fetches new line
			//cout<<line;
			//cout<<"\n";
			stringstream check1(line); //tokenizes the line
			while(getline(check1, temp, ' ')){
				tokens.push_back(temp);
			}
			for(int i = 0;i<tokens.size();i++){
				//cout<<tokens.size();
				//cout<<tokens[i]<<"\n";
				if(tokens[i].length() > 10) //if the string is larget than 10 cut it down to 10
					tokens[i] = tokens[i].substr(0,9);
				test = tokens[i].at(0); //check first element in string to see if it is a number
				if(!isdigit(test) && !ispunct(test)){ //checks for numbers
					//cout<<"inserting"<<tokens[i];
					test=tokens[i].at(tokens[i].length()-1); //set test to be the last element in the string
					if(ispunct(test)){ //check for punctuation at the end
						tokens[i] = tokens[i].substr(0,tokens[i].length()-1); //if there is punctuation delete it
					}
					root = Insert(root,tokens[i],x); //inserts into tree
				}
				else
					continue;
			}
			tokens.clear(); //clear all dynamic variables for next line
			line.clear();
			temp.clear();
			check1.clear();
			x++;
		}
	}
	else{
		cout<<"File not found\n"; //error message if file cannot be found
		return 0;
	}
	PrintTree(root); //prints tree
	destroyTree(root); //frees and deletes tree
	file.close();	//closes filestream
}
