/*
This file contains an implementation of Red-Black tree.it is written with emphasis
on clarity and correctness, with both iterative and recursive code for insertion and deletion
so you can compare both methods.
*/
#include<iostream>
#include"RedBlackTree.h"
using namespace std;
//--------------------------------------constructors,destructor, operator---------------------------------------

//default constructor
RedBlackTree::RedBlackTree() { Root = nullptr; }


//copy constructor
RedBlackTree::RedBlackTree(const RedBlackTree& other) {
	Root = copy(other.Root, nullptr);
}


//destructor
RedBlackTree::~RedBlackTree() {
	destroy(Root);
}


//aassignment operatorr implementation
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other) {
	if (this != &other) {
		destroy(Root);
		Root = copy(other.Root, nullptr);
	}
	return *this;
}


//-----------------------------------------Rotations:)---------------------------------------------


//left rotation function
void RedBlackTree::RotateLeft(Node* RT) {
	Node* tmp = RT->right;
	RT->right = tmp->left;
	if (tmp->left != nullptr) {
		tmp->left->parent = RT;
		tmp->left->isLeftChild = false;
	}
	tmp->parent = RT->parent;
	if (RT->parent == nullptr) {
		Root = tmp;
		tmp->isLeftChild = false;
	}
	else if (RT->isLeftChild) {
		RT->parent->left = tmp;
		tmp->isLeftChild = true;
	}
	else {
		RT->parent->right = tmp;
		tmp->isLeftChild = false;
	}
	tmp->left = RT;
	RT->parent = tmp;
	RT->isLeftChild = true;
}

//right rotation function
void RedBlackTree::RotateRight(Node* RT) {
	Node* tmp = RT->left;
	RT->left = tmp->right;
	if (tmp->right != nullptr) {
		tmp->right->parent = RT;
		tmp->right->isLeftChild = true;
	}
	tmp->parent = RT->parent;
	if (RT->parent == nullptr)
		Root = tmp;
	else if (RT->isLeftChild) {
		RT->parent->left = tmp;
		tmp->isLeftChild = true;
	}
	else {
		RT->parent->right = tmp;
		tmp->isLeftChild = false;
	}
	tmp->right = RT;
	RT->parent = tmp;
	RT->isLeftChild = false;
}

//--------------------------------------------Aunt helper functions-------------------------------------------


//function that returns Aunt Node
Node* RedBlackTree::getAunt(Node* node)const {
	if (node == nullptr || node->parent == nullptr || node->parent->parent == nullptr)return nullptr;
	if (node->parent->isLeftChild)return node->parent->parent->right;
	return node->parent->parent->left;
}


//function that returns true if the Aunt is Red
bool RedBlackTree::isAuntRed(Node* node) const {
	Node* aunt = getAunt(node);
	return aunt && !aunt->isBlack;
}
//-------------------------------------------Traversals--------------------------------------------------------


/*
Prints out the tree preorderly .
1)the current node is visited first
2)then the left and right subtrees
*/
void RedBlackTree::Preorder(ostream& ost, Node* RT) const {
	if (!RT) return;
	ost << RT->value << " ";
	Preorder(ost, RT->left);
	Preorder(ost, RT->right);
}


/*
Prints the tree with inorderly.
1)it goes to the left subtree
2)processes the node
3)and goes to the right subtree.
So it prints nodes containing values that are sorted in an ascending manner.
*/
void RedBlackTree::Inorder(ostream& ost, Node* RT) const {
	if (!RT) return;
	Inorder(ost, RT->left);
	ost << RT->value << " ";
	Inorder(ost, RT->right);
}

/*it prints the tree using postorderly.
1)Process the left and right subtrees
2)process current node.*/
void RedBlackTree::Postorder(ostream& ost, Node* RT) const {
	if (!RT) return;
	Postorder(ost, RT->left);
	Postorder(ost, RT->right);
	ost << RT->value << " ";
}


void RedBlackTree::preorder()const { Preorder(cout, Root); cout << endl; }
void RedBlackTree::inorder()const { Inorder(cout, Root); cout << endl; }
void RedBlackTree::postorder()const { Postorder(cout, Root); cout << endl; }


//----------------------------------------------Memory Helpers----------------------------------------------------

//destroy recursive function that deletes all the elements
void RedBlackTree::destroy(Node* node) {
	if (node == nullptr)return;
	destroy(node->left);
	destroy(node->right);
	delete node;
}


//copy recursive function that copies all the nodes from another rbt
Node* RedBlackTree::copy(Node* node, Node* parent) {
	if (!node) return nullptr;
	Node* New = new Node(node->value);
	New->isBlack = node->isBlack;
	New->isLeftChild = node->isLeftChild;
	New->parent = parent;
	New->left = copy(node->left, New);
	New->right = copy(node->right, New);
	return New;
}


//-----------------------------------------insertion------------------------------------------------------------------
//Iterative insertion
void RedBlackTree::insertIterative(int val) {
	Node* New = new Node(val);
	Node* par = nullptr;
	Node* walker = Root;
	while (walker) {
		par = walker;
		if (val < walker->value) {
			walker = walker->left;
			New->isLeftChild = true;
		}
		else {
			walker = walker->right;
			New->isLeftChild = false;
		}
	}
	New->parent = par;
	if (par == nullptr)Root = New;
	else if (New->isLeftChild) par->left = New;
	else par->right = New;
	fixInsert(New);
}

/*
fixInsert function: triggered after a new node has been successfully
inserted into the tree.it checks if any of the Red-Black tree properties are violated
such as having two consecutive Red nodes. it is useful for its function of avoiding
too many problems after insertation
*/
void RedBlackTree::fixInsert(Node* node) {
	Node* par = nullptr;
	Node* grand = nullptr;
	while (node != Root && !node->parent->isBlack) {//working until node becomes Root and node's parent is red
		par = node->parent;
		grand = par->parent;
		Node* Aunt = getAunt(node);
		//case 1 if Aunt is Red
		if (isAuntRed(node)) {
			par->isBlack = true;
			Aunt->isBlack = true;
			grand->isBlack = false;
			node = grand;
		}
		//case 2 if Aunt is Black or nullptr
		else {
			if (par->isLeftChild) { //if node's parent is leftchild
				if (!node->isLeftChild) {
					node = par;
					RotateLeft(node);
					par = node->parent;
				}
				par->isBlack = true;
				grand->isBlack = false;
				RotateRight(grand);
			}
			else { //if node's parent is rightchild
				if (node->isLeftChild) {
					node = par;
					RotateRight(node);
					par = node->parent;
				}
				par->isBlack = true;
				grand->isBlack = false;
				RotateLeft(grand);
			}
		}
	}
	Root->isBlack = true;
}

//recursive insertion
Node* RedBlackTree::insertRec(Node* nd, int elem, Node*& newNode) {
	if (!nd) {
		newNode = new Node(elem);
		return newNode;
	}
	if (elem < nd->value) {
		nd->left = insertRec(nd->left, elem, newNode);
		nd->left->parent = nd;
		nd->left->isLeftChild = true;
	}
	else {
		nd->right = insertRec(nd->right, elem, newNode);
		nd->right->parent = nd;
		nd->right->isLeftChild = false;
	}
	return nd;
}


// public wrapper of insertRecursive function
void RedBlackTree::insertRecursive(int val) {
	Node* newNode = nullptr;
	Root = insertRec(Root, val, newNode);
	fixInsert(newNode);//to fix Red-Black properties
}


//--------------------------------------------search functions------------------------------------------------
//recursive search
Node* RedBlackTree::search(Node* node, int val)const {
	if (!node)return nullptr;
	if (val == node->value)return node;
	else if (val < node->value)return search(node->left, val);
	else return search(node->right, val);
}
//Iterative search
Node* RedBlackTree::searchIterative(Node* node, int val)const {
	while (node) {
		if (val == node->value) return node;
		else if (val < node->value) node = node->left;
		else node = node->right;
	}
	return nullptr;
}
//public wrapper for recursive search
bool RedBlackTree::searchrec(int val)const {
	return search(Root, val) != nullptr;
}
//public wrapper for Iterative search
bool RedBlackTree::searchIt(int val)const {
	return searchIterative(Root, val) != nullptr;
}

//----------------------------------------Minimum functions---------------------------------------------------
Node* RedBlackTree::Minimum(Node* node) const {
	while (node && node->left) node = node->left;
	return node;
}
int RedBlackTree::minimum()const {
	Node* min = Minimum(Root);
	if (min)return min->value;
	else throw std::runtime_error("Tree is empty");
}

//------------------------------------------------Deletion-----------------------------------------------------
//to make some replacements.it will be necessary in the remove function and maybe in the fixdeletion function
//it's helper not to write too much:))
void RedBlackTree::replaceNode(Node* removed, Node* replacement) {
	if (!removed->parent) Root = replacement;
	else if (removed->isLeftChild)
		removed->parent->left = replacement;
	else
		removed->parent->right = replacement;
	if (replacement) {
		replacement->parent = removed->parent;
		replacement->isLeftChild = removed->isLeftChild;
	}
}

//remove functions that removes the node from the red-black Tree
void RedBlackTree::removeIterative(int val) {
	Node* found = search(Root, val);
	if (!found) {
		cout << "Element " << val << " not found!" << endl;
		return;
	}
	Node* f1 = found; // y=z
	Node* f2 = nullptr; //x=null
	bool originalBlack = f1->isBlack;
	//case 1: if found element doesnt have left child
	if (!found->left) {
		f2 = found->right;
		replaceNode(found, f2);
	}
	//case 2: if found element doesnt have right child
	else if (!found->right) {
		f2 = found->left;
		replaceNode(found, f2);
	}
	//case 3: if found element doesnt have both children
	else {
		f1 = Minimum(found->right);
		originalBlack = f1->isBlack;
		f2 = f1->right;
		if (f1->parent == found) {
			if (f2) {
				f2->parent = f1;
				f2->isLeftChild = false;
			}
		}
		else {
			replaceNode(f1, f1->right);
			f1->right = found->right;
			f1->right->parent = f1;
			f1->right->isLeftChild = false;
		}
		replaceNode(found, f1);
		f1->left = found->left;
		f1->left->parent = f1;
		f1->left->isLeftChild = true;
		f1->isBlack = found->isBlack;
	}
	delete found;
	if (originalBlack) {
		fixDeletion(f2);
	}
}

/*
fixDeletion func deals with violations that occur when a deletion takes place in a node,
it takes care of its own double-black nodes by examining its sibling nodes in order to recolor
or rotate them to satisfy the Red-Black Tree properties again.
*/
void RedBlackTree::fixDeletion(Node* nd) {
	//loop until nd is root or there is a double black problem
	while (nd != Root && (!nd || nd->isBlack)) {
		Node* par = nd ? nd->parent : nullptr; //parent of the current Node
		Node* parSib = nullptr; //sibling of the current Node
		//find sibling --- if Node is left child
		if (nd && nd->isLeftChild) parSib = par->right;
		//if Node is right child
		else if (nd) parSib = par->left;
		//if Node is nullptr
		if (!nd) {
			if (par && par->left == nullptr) parSib = par->right;
			else if (par) parSib = par->left;
		}
		//case 1: sibling is red
		if (parSib && !parSib->isBlack) {
			parSib->isBlack = true;
			par->isBlack = false;
			//rotating parent towards nd
			if (nd && nd->isLeftChild) RotateLeft(par);
			else RotateRight(par);
			continue;
		}
		//case 2: sibling is Black and both children are Black or null
		if (parSib && (!parSib->left || parSib->left->isBlack) && (!parSib->right || parSib->right->isBlack)) {
			parSib->isBlack = false;
			nd = par;
			continue;
		}
		//case 3: sibling is Black and at least one child is red
		if (nd && nd->isLeftChild) {
			//right child is Black and left child is red
			if (parSib->right && parSib->right->isBlack) {
				if (parSib->left) parSib->left->isBlack = true;
				parSib->isBlack = false;
				RotateRight(parSib);
				parSib = par->right; //update sibling
			}
			//right child is red and left child is Black
			parSib->isBlack = par->isBlack;
			par->isBlack = true;
			if (parSib->right) parSib->right->isBlack = true;
			RotateLeft(par);
			nd = Root;
		}
		//nd is right child
		else {
			//left child is black and right is red
			if (parSib->left && parSib->left->isBlack) {
				if (parSib->right) parSib->right->isBlack = true;
				parSib->isBlack = false;
				RotateLeft(parSib);
				parSib = par->left; //update sibling
			}
			//left child is red and right is black
			parSib->isBlack = par->isBlack;
			par->isBlack = true;
			if (parSib->left) parSib->left->isBlack = true;
			RotateRight(par);
			nd = Root;
		}

	}
	//finally ensure the nd is black
	if (nd) nd->isBlack = true;
}


//recursive remove function
Node* RedBlackTree::removeRec(Node* node, int val, Node*& fix) {
	if (!node) return nullptr;//if value not found
	if (val < node->value)
		node->left = removeRec(node->left, val, fix);
	else if (val > node->value)
		node->right = removeRec(node->right, val, fix);
	else { //if found
		if (!node->left) {
			fix = node->right;//double Black possibility
			if (fix) fix->parent = node->parent;
			delete node;
			return fix;
		}
		else if (!node->right) {
			fix = node->left;
			if (fix) fix->parent = node->parent;
			delete node;
			return fix;
		}
		else {
			Node* min = Minimum(node->right);
			node->value = min->value;//copy value
			node->right = removeRec(node->right, min->value, fix);
		}
	}
	return node;
}

//public wrapper for this function
void RedBlackTree::removeRecursive(int val) {
	Node* fixNode = nullptr;
	Root = removeRec(Root, val, fixNode);
	if (fixNode && fixNode->isBlack) fixDeletion(fixNode);
	if (Root) Root->isBlack = true;
}

