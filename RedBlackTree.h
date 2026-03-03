#pragma once
#include "Node.h"
#include<iostream>
using namespace std;
/*
RBT class is a balancing binary search tree. The class
has methods for both iterative and recursive insertions and deletions.
The balancing is done based on color properties and rotations.
*/
class RedBlackTree {
private:
	Node* Root;
	//-----------------------------------------helper functions------------------------------------
	void RotateLeft(Node* root); //performs the left rotation around the n Node
	void RotateRight(Node* root); //performs the right rotation around the n Node
	//fixInsert --- fixes RedBlack tree after insertion and ensures no two consecutive red Nodes exist and root remains black
	void fixInsert(Node* node);
	Node* insertRec(Node* node, int val, Node*& newNode); //rec inserts helper
	void fixDeletion(Node* node); //fixDeletion --- fixes violations after deletion////////////////////////////
	Node* removeRec(Node* node, int val, Node*& fixNode); //rec removes helper
	void replaceNode(Node* removed, Node* replacement);//deletion's helper function that replaces two nodes
	Node* Minimum(Node* node)const; //returns the Node that has the minimum value
	Node* search(Node* node, int value)const; //recursive search starting at Node
	Node* searchIterative(Node* node, int val) const; //iterative searchs helper
	//-------------------------------Helpers for memory managment----------------------------------
	void destroy(Node* node); //recursively delete all nodes
	Node* copy(Node* node, Node* parent); //recursively copy subtree
	//-----------------------------------------Traversals------------------------------------------
	void Preorder(ostream& out, Node* node)const;
	void Inorder(ostream& out, Node* node)const;
	void Postorder(ostream& out, Node* node)const;
	//-----------------------------------------Aunt helpers----------------------------------------
	Node* getAunt(Node* node)const; //returns aunt(parent's sibling)
	bool isAuntRed(Node* node)const; //checks if aunt is red
public:
	RedBlackTree();//default constructor that creates an empty tree
	RedBlackTree(const RedBlackTree& other); //copy constructor -- deep copy of another tree
	~RedBlackTree(); //destructor -- frees all memory
	RedBlackTree& operator=(const RedBlackTree& other); //assignment operator -- deep copy
	int minimum()const; //finding min element
	void insertIterative(int val); //iteratively inserts element
	void insertRecursive(int val); //recursively inserts element
	void removeIterative(int val); //Iteratively removes element
	void removeRecursive(int val); //recursively removes element
	bool searchrec(int val)const; //searches for a value in the tree and returns true if found
	bool searchIt(int val)const; //iteratively searchs
	//-------------------Traversal functions--------------------------------
	void preorder()const;
	void inorder()const;
	void postorder()const;
};
