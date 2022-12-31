#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

typedef struct bstnode {
    int height;
    struct bstnode *parent, *leftChild, *rightChild;
    BSTElement element;
} BSTNODE;

typedef struct {
    CompareElementsBST compare;
    BSTNODE *root;
}BSTTREE;

BST newBST(CompareElementsBST compare) {
    if(!compare) {
        printf("WARNING: Invalid parameter -- newBST --\n");
        return NULL;
    }

    BSTTREE *bst = (BSTTREE *) malloc(sizeof(BSTTREE));
    if(!bst) {
        printf("ERROR: Could not allocate memory for new BST -- newBST --\n");
        return NULL;
    }

    bst->compare = compare;
    bst->root = NULL;

    return bst;
}

bool isBSTEmpty(BSTNode root) {
    if(!root) return true;

    return getBSTHeight(root) == 0;
}

int getBSTHeight(BSTNode root) {
    if(!root) return -1;

    BSTNODE *node = (BSTNODE *) root;

    return node->height;
}

/*
    # Description:
        - Returns a pointer to a new empty BSTNode
*/
BSTNODE *newBSTNode() {
    BSTNODE *node = (BSTNODE *) malloc(sizeof(BSTNODE));
    if(!node) {
        printf("ERROR: Could not allocate memory for new BSTNode -- newBSTNode --\n");
        return NULL;
    }

    node->element = NULL;
    node->height = 0;
    node->leftChild = NULL;
    node->parent = NULL;
    node->rightChild = NULL;

    return node;
}

void recalculateHeight(BSTNODE *root) {
    if(!root) return;
    
    int leftHeight = getBSTHeight(root->leftChild) + 1;
    int rightHeight = getBSTHeight(root->rightChild) + 1;

    root->height = (leftHeight > rightHeight) ? leftHeight : rightHeight;
    
    recalculateHeight(root->parent);
}

/*
    # Input:
        - compare: Function to compare two BSTElements
        - currentNode: BSTNode to be analysed
        - newNode: BSTNode to be inserted in a BST
    
    # Description:
        - Inserts newNode in the BST containing currentNode

        - The insertion follows the insertion rules of a BST
*/
void insertBSTNode(CompareElementsBST compare, BSTNODE *currentNode, BSTNODE *newNode) {
    if(compare(newNode->element, currentNode->element) > 1) {
        if(currentNode->rightChild) insertBSTNode(compare, currentNode->rightChild, newNode);
        else {
            newNode->parent = currentNode;
            currentNode->rightChild = newNode;
        }
    }
    else {
        if(currentNode->leftChild) insertBSTNode(compare, currentNode->leftChild, newNode);
        else {
            newNode->parent = currentNode;
            currentNode->leftChild = newNode;
        }
    }
}

BSTNode insertBST(BST bst, BSTElement element) {
    if(!bst || !element) {
        printf("WARNING: Invalid parameters -- insertBST --\n");
        return NULL;
    }

    BSTTREE *tree = (BSTTREE *) bst;

    BSTNODE *node = newBSTNode();
    if(!node) {
        printf("WARNING: Could not insert element in BST -- insertBST --\n");
        return NULL;
    }

    node->element = element;

    if(!tree->root) tree->root = node;
    else insertBSTNode(tree->compare, (BSTNODE *) getBSTRoot(bst), node);

    recalculateHeight(node);

    return node;
}

/*
    # Input:
        - root: Root node from a BST
    
    # Description:
        - Returns the node that stores the smallest element in the bst with root
          as its root node
*/
BSTNODE *getSmallestNode(BSTNODE *root) {
    if(!root->leftChild) return root;

    BSTNODE *smallest;
    for(smallest = root->leftChild; smallest->leftChild; smallest = smallest->leftChild);

    return smallest;
}

BSTElement removeBST(BST bst, BSTNode node) {
    if(!bst || !node) {
        printf("WARNING: Invalid parameters -- removeBST --\n");
        return NULL;
    }

    BSTTREE *tree = (BSTTREE *) bst;
    BSTNODE *nd = (BSTNODE *) node;
    BSTElement *element = nd->element;

    if(nd->leftChild && nd->rightChild) {
        node = getSmallestNode(nd->rightChild);
        nd->element = getBSTNodeElement(node);

        nd = (BSTNODE *) node;
    }

    bool parent = nd->parent;
    bool isNdLeftChild = (parent) ? (tree->compare(nd->parent->element, nd->element) <= 0) : false;
    if(!nd->leftChild && !nd->rightChild) {
        if(parent && isNdLeftChild) nd->parent->leftChild = NULL;
        else if(parent) nd->parent->rightChild = NULL;
    }
    else if(!nd->leftChild || !nd->rightChild) {
        BSTNODE *nextRoot = (nd->leftChild) ? nd->leftChild : nd->rightChild;

        if(parent && isNdLeftChild) nd->parent->leftChild = nextRoot;
        else if(parent) nd->parent->rightChild = nextRoot;

        nextRoot->parent = nd->parent;
    }

    recalculateHeight(nd->parent);

    free(node);
    node = NULL;

    return element;
}

BSTNode getBSTRoot(BST bst) {
    if(!bst) {
        printf("WARNING: Invalid parameter -- getBSTRoot --\n");
        return NULL;
    }

    BSTTREE *tree = (BSTTREE *) bst;

    return tree->root;
}

BSTNode getBSTNodeLeftNode(BSTNode node) {
    if(!node) {
        printf("WARNING: Invalid parameter -- getBSTNodeLeftNode --\n");
        return NULL;
    }

    BSTNODE *nd = (BSTNODE *) node;

    return nd->leftChild;
}

BSTNode getBSTNodeRightNode(BSTNode node) {
    if(!node) {
        printf("WARNING: Invalid parameter -- getBSTNodeRightNode --\n");
        return NULL;
    }

    BSTNODE *nd = (BSTNODE *) node;

    return nd->rightChild;
}

BSTNode getBSTNodeParentNode(BSTNode node) {
    if(!node) {
        printf("WARNING: Invalid parameter -- getBSTNodeParentNode --\n");
        return NULL;
    }

    BSTNODE *nd = (BSTNODE *) node;

    return nd->parent;
}

BSTElement getBSTNodeElement(BSTNode node) {
    if(!node) {
        printf("WARNING: Invalid parameter -- getBSTNodeElement --\n");
        return NULL;
    }

    BSTNODE *nd = (BSTNODE *) node;

    return nd->element;
}

/*
    # Input:
        - compare: Function to compare 2 bst elements
        - node: Node from a bst
        - element: Element to be found
    
    # Description:
        - Returns the node that stores element, if node doesn't exists, returns NULL
*/
BSTNODE *findBST(CompareElementsBST compare, BSTNODE *node, BSTElement element) {
    if(!node) return NULL;

    int cmp = compare(node->element, element);

    if(cmp == 0) return node;
    if(cmp == 1) return getBSTNodeLeftNode(node);
    return getBSTNodeRightNode(node);
}

BSTNode findBSTNodeElement(BST bst, BSTElement element) {
    if(!bst || !element) {
        printf("WARNING: Invalid parameters -- findBSTNodeElement --\n");
        return NULL;
    }

    BSTTREE *tree = (BSTTREE *) bst;
    BSTNODE *node = (BSTNODE *) getBSTRoot(bst);

    return findBST(tree->compare, node, element);
}

void inOrder(BST bst, BSTNODE *node, VisitBSTNode visit, void *extra) {
    if(!node) return;

    inOrder(bst, getBSTNodeLeftNode(node), visit, extra);
    if(visit) visit(bst, node, extra);
    inOrder(bst, getBSTNodeRightNode(node), visit, extra);
}

void inOrderBSTTraversal(BST bst, VisitBSTNode visit, void *extra) {
    if(!bst) {
        printf("WARNING: Invalid parameter -- inOrderBSTTraversal --\n");
        return;
    }

    inOrder(bst, getBSTRoot(bst), visit, extra);
}

void preOrder(BST bst, BSTNODE *node, VisitBSTNode visit, void *extra) {
    if(!node) return;

    if(visit) visit(bst, node, extra);
    preOrder(bst, getBSTNodeLeftNode(node), visit, extra);
    preOrder(bst, getBSTNodeRightNode(node), visit, extra);
}

void preOrderBSTTraversal(BST bst, VisitBSTNode visit, void *extra) {
    if(!bst) {
        printf("WARNING: Invalid parameter -- preOrderBSTTraversal --\n");
        return;
    }

    preOrder(bst, getBSTRoot(bst), visit, extra);
}

void postOrder(BST bst, BSTNODE *node, VisitBSTNode visit, void *extra) {
    if(!node) return;

    postOrder(bst, getBSTNodeLeftNode(node), visit, extra);
    postOrder(bst, getBSTNodeRightNode(node), visit, extra);
    if(visit) visit(bst, node, extra);
}

void postOrderBSTTraversal(BST bst, VisitBSTNode visit, void *extra) {
    if(!bst) {
        printf("WARNING: Invalid parameter -- postOrderBSTTraversal --\n");
        return;
    }

    postOrder(bst, getBSTRoot(bst), visit, extra);
}

/*
    # Input:
        - root: Root node from a BST
    
    # Description:
        - Reverse the bst with root as its root node
*/
void reverseBSTTree(BSTNODE *root) {
    if(!root) return;

    BSTNODE *temp = root->leftChild;
    root->leftChild = root->rightChild;
    root->rightChild = temp;

    reverseBSTTree(root->leftChild);
    reverseBSTTree(root->rightChild);
}

void reverseBST(BST bst) {
    if(!bst) {
        printf("WARNING: Invalid parameter -- reverseBST --\n");
        return;
    }

    BSTTREE *tree = (BSTTREE *) bst;

    reverseBST(tree);
}

/*
    # Input:
        - bst: BST
        - root: BST node
    
    # Description:
        - Destroy all nodes from the BST with root as it root
*/
void emptyTree(BST bst, BSTNODE *root) {
    while(root) {
        removeBST(bst, root);
        root = getBSTRoot(bst);
    }
}

void destroyBST(BST bst) {
    if(!bst) return;

    BSTTREE *tree = (BSTTREE *) bst;
    BSTNODE *root = (BSTNODE *) tree->root;

    emptyTree(bst, root);
    
    free(tree);
    bst = NULL;
}
