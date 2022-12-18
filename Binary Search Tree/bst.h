#ifndef BST_H
#define BST_H

/*
    - This module implements a binary search tree(bst)

    - A bst is a node-based binary tree data structure which has the following properties:
        - The left subtree of a BSTNode contains only BSTNodes with keys lesser than the BSTNode’s key.
        - The right subtree of a BSTNode contains only BSTNodes with keys greater than the BSTNode’s key.
        - The left and right subtree each must also be a binary search tree.

    - A valid BSTNode has BSTElement != NULL

    - In this module its assumed BST != NULL, BSTElement != NULL and BSTNode != NULL for functions that recieve
      those as parameters 

    - It's necessary to free the memory allocated for BST and BSTNode using the functions provided in this module
*/

#include <stdbool.h>

typedef void *BST;
typedef void *BSTNode;
typedef void *BSTElement;

/*
    Returns: -1 if el1 < el2
             +1 if el1 > el2
             0 if el1 == el2
*/
typedef int (* CompareElementsBST)(BSTElement el1, BSTElement el2);

/*
    # Input:
        - compare: Function to compare BSTElement for new BST
    
    # Description:
        - Returns a pointer to a new BST
*/
BST newTree(CompareElementsBST compare);

/*
    # Input:
        - bst: BST
    
    # Description:
        - Returns true if bst is empty, false otherwise
*/
bool isBSTEmpty(BST bst);

/*
    # Input:
        - node: Node from a BST
    
    # Description:
        - Returns the height of the subtree with node as its root
*/
int getSubBSTHeight(BSTNode node);

/*
    # Input:
        - bst: BST
        - element: Element to be inserted
    
    # Description:
        - Inserts element in bst

        - Returns a pointer to the node created for element
*/
BSTNode insertBST(BST bst, BSTElement element);

/*
    # Input:
        - bst: BST
        - node: BSTNode from bst
    
    # Description:
        - Removes node from bst and returns
          element stored in node

        - node must be in bst
*/
BSTElement removeBST(BST bst, BSTNode node);

/*
    # Input:
        - bst: BST
    
    # Description:
        - Returns bst root

        - bst must not be empty
*/
BSTNode getBSTRoot(BST bst);

/*
    # Input:
        - bst: BST
        - node: BSTNode from bst
    
    # Description:
        - Returns BSTNode that is the root of the left
          subtree pointed by node
*/
BSTNode getBSTNodeLeftNode(BST bst, BSTNode node);

/*
    # Input:
        - bst: BST
        - node: BSTNode from bst
    
    # Description:
        - Returns BSTNode that is the root of the right
          subtree pointed by node
*/
BSTNode getBSTNodeRightNode(BST bst, BSTNode node);

/*
    # Input:
        - bst: BST
        - node: BSTNode from bst
    
    # Description:
        - Returns BSTNode that is the "father" of node
*/
BSTNode getBSTNodeFatherNode(BST bst, BSTNode node);

/*
    # Input:
        - bst: BST
        - node: BSTNode from bst
    
    # Description:
        - Returns the element stored in node
*/
BSTElement getBSTNodeElement(BST bst, BSTNode node);

#endif