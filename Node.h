#pragma once
class RedBlackTree;
/*
this class corresponds to one element within the Red and Black Tree. it contains values
as well as pointers for its parent and children and also there are additional flags that makes more simple
the rotations and other modifications.
*/
class Node {
	friend class RedBlackTree;//friend classs:)
private:
	int value; //stores the value of the Node
	bool isBlack; //true if the Node si black, false if its red
	bool isLeftChild; //true if this Node is leftt
	//--------------------pointers---------------------------------------
	Node* parent;
	Node* left;
	Node* right;
public:
	/*constructor--- initializes and by default,
	the new Node is Red and has no parent or children*/
	Node(int item = 0) :value(item), isBlack(false), isLeftChild(false),
		parent(nullptr), left(nullptr), right(nullptr) {
	}
};