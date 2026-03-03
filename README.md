# Red-Black-tree implementation in C++

# Overview
This project implements a fully functional Red-Black tree(RBT) - a self-balancing Binary search Tree that guarantees O(logn) time complexity for insertion, deletion and search operations. The implementation includes both iterative and recursive approaches for core operations to demonstrate algorithmic differences.

# Project Structure 
Red-Black-Tree/
- Node.h           # Node class definition
- RedBlackTree.h   # RedBlackTree class interface
- RedBlackTree.cpp # RedBlackTree class implementation
- Driver.cpp       # Driver/program tester
- README.md        # Project description

## Features
- Iterative and Recursive Insertion
- Iterative and Recursive Deletion
- Iterative and recursive Search
- Tree Rotations ( Left/Right )
- Fix-up procedures after Insertion and Deletion
- Retrieval of Minimum element
- Tree Traversals:
  -> Preorder
  -> Inorder
  -> Postorder
- Deep copy ( Copy constructor )
- Assignment operator overload
- Proper memory management ( Destructor )

## Red-Black Tree Properties
The implementation maintains the core RBT properties:
1. Each Node is either Red or Black
2. The Root is always Black
3. No two consecutive Red Nodes exist
4. Every path from a node to its descendant NULL nodes has the same number of black nodes
5. All the Inserted Node is Red at first
6. Nulls are always Black
7. If Aunt is Black RBT fixation is Rotation
8. If Aunt is Red RBT fixation is Color Flip
------ Balancing is achieved by:
   - RotateLeft
   - RotateRight
   - fixInsert
   - fixDeletion

## Time Complexity
- Insertion -> O(logn)
- Deletion -> O(logn)
- Search -> O(logn)
- Minimum -> O(logn)

## Concepts used
- OOP (Object-Oriented Programming)
- Self-Balancing Binary search trees
- Recursion
- Iteration
- Dynamic Memory management
- Deep copy semantics
- Operator Overloading
