#ifndef LIST_H
#define LIST_H

/*
    - This module implements a doubly linked list(dll)

    - A dll is a linked data structure that consists of a set of sequentially linked ListNodes.
      Each ListNode contains three fields: 
        - 2 link fields (references to the previous and to the next ListNode in the sequence of ListNodes)
        - 1 data field (ListElement)

    - Each ListNode has a position inside the list, this position is inside the interval [0, list.size)

    - A valid ListNode has ListElement != NULL

    - All in this module assume List != NULL, ListElement != NULL and ListNode != NULL for functions that recieve
      those as parameters 

    - It's necessary to free the memory allocated for List and ListNode using the functions provided in this module
*/

#include <stdbool.h>

typedef void *List;
typedef void *ListElement;
typedef void *ListNode;

/*
    # Description:
        - Returns a pointer to a new empty list
*/
List newList();

/*
    # Input:
        - list: dll
    
    # Description:
        - Returns true if list is empty, false otherwise
*/
bool isListEmpty(List list);

/*
    # Input:
        - list: dll
    
    # Description:
        - Return the number of elements stored in list
*/
int getListSize(List list);

/*
    # Inputs:
        - list: dll
        - element: Element to be stored in list

    # Description:
        - Insert element at the start of list

        - Returns a pointer to the node created for element
*/
ListNode pushList(List list, ListElement element);

/*
    # Inputs:
        - list: dll
        - element: Element to be stored in list
        - position: Position in list to place element
    
    # Description:
        - Insert element at informed position

        - If position >= list.size or position == -1, 
          the element will be positioned at the end
          of the list

        - Returns a pointer to the node created for element
*/
ListNode insertList(List list, ListElement element, int position);

/*
    # Inputs:
        - list: dll
        - element: Element to be stored in list
        - node: Node from list
    
    # Description:    
        - Insert element after node

        - Returns a pointer to the node created for element
*/
ListNode insertAfterList(List list, ListElement element, ListNode node);

/*
    # Inputs:
        - list: dll
        - element: Element to be stored in list
        - node: Node from list
    
    # Description:    
        - Insert element before node

        - Returns a pointer to the node created for element
*/
ListNode insertBeforeList(List list, ListElement element, ListNode node);

/*
    # Inputs:
        - list: dll
        - element: Element to be stored in list

    # Description:
        - Insert element at the end of list

        - Returns a pointer to the node created for element
*/
ListNode insertEndList(List list, ListElement element);

/*
    # Input:
        - list: dll

    # Description:
        - Removes the first element from list
          and returns it
        
        - List cannot be empty
*/
ListElement pop(List list);

/*
    # Inputs:
        - list: dll
        - node: ListNode from list

    # Description:
        - Removes the node indicated by node form the list and returns
          the element that was stored in it

        - node must exist in list
*/
ListElement removeListNode(List list, ListNode node);

/*
    # Inputs:
        - list: dll
        - position: Position in list to place element
    
    # Description:
        - Remove element at informed position

        - If position > list.size or position == -1, 
          the last element from list will be removed

        - Returns the removed element

        - List cannot be empty
*/
ListElement removeList(List list, int position);

/*
    # Input:
        - list: dll
        - node: LisNode from list

    # Description:
        - Returns the element stored in node
*/
ListElement getListNodeElement(List list, ListNode node);

/*
    # Input:
        - list: dll
    
    # Description:
        - Returns the first node from list

        - List cannot be empty
*/
ListNode getFirstListNode(List list);

/*
    # Input:
        - list: dll
    
    # Description:
        - Returns the last node from list

        - List cannot be empty
*/
ListNode getLastListNode(List list);

/*
    # Input:
        - list: dll
        - node: ListNode from list
    
    # Description:
        - Returns the ListNode after node from list

        - If node is the last from list, returns NULL 
*/
ListNode getNextListNode(List list, ListNode node);

/*
    # Input:
        - list: dll
        - node: ListNode from list
    
    # Description:
        - Returns the ListNode before node from list

        - If node is the first from list, returns NULL 
*/
ListNode getPreviousListNode(List list, ListNode node);

/*
    # Input:
        - list: dll
    
    # Description:
        - Free all the memory used by list
*/
void destroyList(List list);

#endif