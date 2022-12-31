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
    - Function to compare 2 BSTElements

    - Returns: -1 if el1 < el2
             +1 if el1 > el2
             0 if el1 == el2
*/
typedef int (* CompareElementsBST)(BSTElement el1, BSTElement el2);

/*
    - Function utilized by the traversal functions

    - If this function returns true, the traversal will stop
*/
typedef bool (* VisitBSTNode)(BST bst, BSTNode node, void *extra);

/*
    # Input:
        - compare: Function to compare BSTElement for new BST
    
    # Description:
        - Returns a pointer to a new BST
*/
BST newBST(CompareElementsBST compare);

/*
    # Input:
        - root: Node from a BST
    
    # Description:
        - Returns true if the BST with root as its root node
          is empty, false otherwise
*/
bool isBSTEmpty(BSTNode root);

/*
    # Input:
        - root: Node from a BST
    
    # Description:
        - Returns the height of the BST with node as its root
*/
int getBSTHeight(BSTNode root);

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
        - node: BSTNode from bst
    
    # Description:
        - Returns BSTNode that is the root of the left
          subtree pointed by node
*/
BSTNode getBSTNodeLeftNode(BSTNode node);

/*
    # Input:
        - node: BSTNode from bst
    
    # Description:
        - Returns BSTNode that is the root of the right
          subtree pointed by node
*/
BSTNode getBSTNodeRightNode(BSTNode node);

/*
    # Input:
        - node: BSTNode from bst
    
    # Description:
        - Returns BSTNode that is the "father" of node
*/
BSTNode getBSTNodeParentNode(BSTNode node);

/*
    # Input:
        - node: BSTNode from bst
    
    # Description:
        - Returns the element stored in node
*/
BSTElement getBSTNodeElement(BSTNode node);

/*
    # Input:
        - bst: BST
        - element: Searched element
    
    # Description:
        - Returns the BSTNode in wich element is stored

        - If element is not in bst, returns NULL
*/
BSTNode findBSTNodeElement(BST bst, BSTElement element);

/*
    # Input:
        - bst: BST
        - visit: Function to be used during the traversal
        - extra: Extra pointer if necessary
    
    # Description:
        - Traverse tree in-order

        - visit and extra can be NULL
*/
void inOrderBSTTraversal(BST bst, VisitBSTNode visit, void *extra);

/*
    # Input:
        - bst: BST
        - visit: Function to be used during the traversal
        - extra: Extra pointer if necessary
    
    # Description:
        - Traverse tree pre-order

        - visit and extra can be NULL
*/
void preOrderBSTTraversal(BST bst, VisitBSTNode visit, void *extra);

/*
    # Input:
        - bst: BST
        - visit: Function to be used during the traversal
        - extra: Extra pointer if necessary
    
    # Description:
        - Traverse tree post-order

        - visit and extra can be NULL
*/
void postOrderBSTTraversal(BST bst, VisitBSTNode visit, void *extra);

/*
    # Input:
        - bst: BST
    
    # Description:
        - Reverse bst
*/
void reverseBST(BST bst);

/*
    # Input:
        - bst: BST
    
    # Description:
        - Free all the memory used by bst
*/
void destroyBST(BST bst);

#endif