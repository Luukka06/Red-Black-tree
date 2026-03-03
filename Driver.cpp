#include <iostream>
#include "RedBlackTree.h"
using namespace std;

int main() {
    cout << "---------------------------- ::RED BLACK TREE:: ----------------------------\n" << endl;
    //creating RedBlackTree obkject called RBtree;)
    RedBlackTree RBtree;
    //--------------- testing Iterative insertion ----------------
    cout << "Tree after iterative insertion:" << endl;
    RBtree.insertIterative(67);
    RBtree.insertIterative(30);
    RBtree.insertIterative(115);
    RBtree.insertIterative(19);
    RBtree.insertIterative(40);
    //checking traversals after iterative insertion
    cout << "\nTraversals after iterative insertion:" << endl;
    cout << "Preorder: "; RBtree.preorder();
    cout << "Inorder: "; RBtree.inorder();
    cout << "Postorder: "; RBtree.postorder();
    //--------------- testing Recursive insertion ----------------
    cout << "\nTree after recursive insertion:" << endl;
    RBtree.insertRecursive(5);
    RBtree.insertRecursive(1);
    RBtree.insertRecursive(8);
    RBtree.insertRecursive(10);
    //checking traversals after recursive insertion
    cout << "\nTraversals after recursive insertion:" << endl;
    cout << "Preorder: "; RBtree.preorder();
    cout << "Inorder: "; RBtree.inorder();
    cout << "Postorder: "; RBtree.postorder();
    //--------------- Searching elements -------------------
    cout << "\nSearching elements:" << endl;
    int mass[] = { 67, 112, 30, 15 };
    for (int val : mass) {
        cout << "Recursive search for " << val << " :answer: " << (RBtree.searchrec(val) ? "Found" : "Not Found") << endl;
        cout << "Iterative search for " << val << " :answer: " << (RBtree.searchIt(val) ? "Found" : "Not Found") << endl;
    }
    //--------------- Minimum value -------------------
    cout << "\nMinimum value in the RBtree: " << RBtree.minimum() << endl;
    //--------------- Iterative deletion ----------------
    cout << "\nRemoving elements iteratively: 5, 19" << endl;
    RBtree.removeIterative(5);
    RBtree.removeIterative(19);
    //traversals after iterative deletion
    cout << "\nTree traversals after iterative deletion:" << endl;
    cout << "Preorder: "; RBtree.preorder();
    cout << "Inorder: "; RBtree.inorder();
    cout << "Postorder: "; RBtree.postorder();
    //--------------- Recursive deletion ----------------
    cout << "\nRemoving elements recursively: 10, 1" << endl;
    RBtree.removeRecursive(10);
    RBtree.removeRecursive(1);
    //traversals after recursive deletion
    cout << "\nTree traversals after recursive deletion:" << endl;
    cout << "Preorder: "; RBtree.preorder();
    cout << "Inorder: "; RBtree.inorder();
    cout << "Postorder: "; RBtree.postorder();
    //--------------- Testing copy constructor ----------------
    cout << "\nTesting copy constructor:" << endl;
    RedBlackTree copytree(RBtree);
    cout << "Copied tree inorder traversal: "; copytree.inorder();
    //--------------- Testing assignment operator ----------------
    cout << "\nTesting assignment operator:" << endl;
    RedBlackTree assignTree;
    assignTree = RBtree;
    cout << "Assigned tree inorder traversal: "; assignTree.inorder();

    cout << "\n---------------------------- ::END OF MAIN:: ----------------------------" << endl;

}
