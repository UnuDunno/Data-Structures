#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct listnode{
    ListElement element;
    struct listnode *previous, *next;
}LISTNODE;

typedef struct {
    int size;
    LISTNODE *head, *tail;
}LIST;

List newList() {
    LIST *dll = (LIST *) malloc(sizeof(LIST));
    if(!dll) {
        printf("ERROR: Could not allocate memory for new list -- newList --\n");
        return NULL;
    }

    dll->size = 0;
    dll->head = NULL;
    dll->tail = NULL;

    return dll;
}

bool isListEmpty(List list) {
    if(!list) {
        printf("WARNING: Invalid parameter -- isListEmpty --\n");
        return true;
    }

    return getListSize(list) == 0;
}

int getListSize(List list) {
    if(!list) {
        printf("WARNING: Invalid parameter -- getListSize --\n");
        return 0;
    }

    LIST *dll = (LIST *) list;

    return dll->size;
}

/*
    # Description:
        - Returns a pointer to a new list node
*/
LISTNODE *newListNode() {
    LISTNODE *lnd = (LISTNODE *) malloc(sizeof(LISTNODE));
    if(!lnd) {
        printf("ERROR: Could not allocate memory for new list node -- newListNode --\n");
        return NULL;
    }

    lnd->element = NULL;
    lnd->next = NULL;
    lnd->previous = NULL;

    return lnd;
}

ListNode pushList(List list, ListElement element) {
    if(!list || !element) {
        printf("WARNING: Invalid parameters -- pushList --\n");
        return NULL;
    }

    // Create new node
    LISTNODE *lnd = newListNode();
    lnd->element = element;
    lnd->next = getFirstListNode(list);

    // Adjust previous head pointer
    LIST *dll = (LIST *) list;
    if(dll->head) dll->head->previous = lnd;
    dll->head = lnd;

    // Check tail pointer
    if(isListEmpty(list)) dll->tail = lnd;

    // Update list size
    dll->size++;

    return lnd;
}

ListNode insertList(List list, ListElement element, int position) {
    if(!list || !element) {
        printf("WARNING: Invalid parameters -- insertList --\n");
        return NULL;
    }

    if(isListEmpty(list) || position == 0) return pushList(list, element);
    if(position >= getListSize(list) || position < 0) return insertEndList(list, element);

    // Find node at position
    ListNode node = getFirstListNode(list);
    for(int i = 0; i < position; i++) node = getNextListNode(list, node);

    // Place node
    return insertBeforeList(list, element, node);
}

ListNode insertAfterList(List list, ListElement element, ListNode node) {
    if(!list || !element || !node) {
        printf("WARNING: Invalid parameters -- insertAfterList --\n");
        return NULL;
    }

    LIST *dll = (LIST *) list;
    LISTNODE *lnd = (LISTNODE *) node;

    if(!lnd->next) return insertEndList(list, element);

    LISTNODE *newNode = newListNode();
    newNode->element = element;

    newNode->previous = lnd;
    newNode->next = lnd->next;

    // Adjust pointers
    lnd->next->previous = newNode;
    lnd->next = newNode;

    dll->size++;

    return newNode;
}

ListNode insertBeforeList(List list, ListElement element, ListNode node) {
    if(!list || !element || !node) {
        printf("WARNING: Invalid parameters -- insertBeforeList --\n");
        return NULL;
    }

    LIST *dll = (LIST *) list;
    LISTNODE *lnd = (LISTNODE *) node;

    if(!lnd->previous) return pushList(list, element);

    LISTNODE *newNode = newListNode();
    newNode->element = element;

    newNode->previous = lnd->previous;
    newNode->next = lnd;

    // Adjust pointers
    lnd->previous->next = newNode;
    lnd->previous = newNode;

    dll->size++;

    return newNode;
}

ListNode insertEndList(List list, ListElement element) {
    if(!list || !element) {
        printf("WARNING: Invalid parameters -- insertEndList --\n");
        return NULL;
    }

    LIST *dll = (LIST *) list;

    LISTNODE *lnd = newListNode();
    lnd->element = element;
    lnd->previous = dll->tail;

    if(dll->tail) dll->tail->next = lnd;
    dll->tail = lnd;

    dll->size++;

    return lnd;
}

ListElement pop(List list) {
    if(!list) {
        printf("WARNING: Invalid parameter -- pop --\n");
        return NULL;
    }

    if(isListEmpty(list)) return NULL;

    LIST *dll = (LIST *) list;

    ListElement element = dll->head->element;
    LISTNODE *head = dll->head;

    dll->head = dll->head->next;
    
    head->next = NULL;
    head->element = NULL;

    free(head);
    
    dll->size--;

    return element;
}

ListElement removeListNode(List list, ListNode node) {
    if(!list || !node) {
        printf("WARNING: Invalid parameters -- removeListNode --\n");
        return NULL;
    }

    if(isListEmpty(list)) return NULL;

    LIST *dll = (LIST *) list;

    LISTNODE *lnd = (LISTNODE *) node;
    if(!lnd->previous) return pop(list);

    ListElement element = lnd->element;
    
    lnd->previous->next = lnd->next;
    lnd->next->previous = lnd->previous;

    lnd->next = NULL;
    lnd->previous = NULL;
    lnd->element = NULL;

    free(lnd);

    dll->size--;

    return element;
}

ListElement removeList(List list, int position) {
    if(!list || position < 0) {
        printf("WARNING: Invalid parameters -- removeList --\n");
        return NULL;
    }

    if(isListEmpty(list)) return NULL;

    // Find node at position
    ListNode node = (position < 0) ? getLastListNode(list) : getFirstListNode(list);
    for(int i = 0; i < position; i++) node = getNextListNode(list, node);

    return removeListNode(list, node);
}

ListElement getListNodeElement(List list, ListNode node) {
    if(!list || !node) {
        printf("WARNING: Invalid parameters -- getListNodeElement --\n");
        return NULL;
    }

    LISTNODE *lnd = (LISTNODE *) node;

    return lnd->element;
}

ListNode getFirstListNode(List list) {
    if(!list) {
        printf("WARNING: Invalid parameter -- getFirstListNode --\n");
        return NULL;
    }

    if(isListEmpty(list)) return NULL;

    LIST *dll = (LIST *) list;

    return dll->head;
}

ListNode getLastListNode(List list) {
    if(!list) {
        printf("WARNING: Invalid parameter -- getLastListNode --\n");
        return NULL;
    }

    if(isListEmpty(list)) return NULL;

    LIST *dll = (LIST *) list;

    return dll->tail;
}

ListNode getNextListNode(List list, ListNode node) {
    if(!list || !node) {
        printf("WARNING: Invalid parameters -- getNextListNode --\n");
        return NULL;
    }

    LISTNODE *lnd = (LISTNODE *) node;

    return lnd->next;
}

ListNode getPreviousListNode(List list, ListNode node) {
    if(!list || !node) {
        printf("WARNING: Invalid parameters -- getPreviousListNode --\n");
        return NULL;
    }

    LISTNODE *lnd = (LISTNODE *) node;

    return lnd->previous;
}

void destroyList(List list) {
    if(!list) return;

    while(!isListEmpty(list)) removeListNode(list, getFirstListNode(list));

    free(list);

    list = NULL;
}
