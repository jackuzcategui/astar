//
//  List.c
//  AStar
//
//  Created by Suiz Uzcategui on 24/10/14.
//  Copyright (c) 2014 ___JuanUzcategui___. All rights reserved.
//

#include <stdio.h>
#include "List.h"
#include "ListTest.c"
#include "status.h"

/** Empty List creation by dynamic memory allocation (O(1)).
 * @param comp comparison function between elements (ala strcmp())
 * @param pr display function for list elements
 * @return a new (empty) list if memory allocation OK
 * @return 0 otherwise
 */
List*	newList	(compFun comp,prFun pr) {
    
    List *s;
    
    s = malloc(sizeof(List));
    
    if (s) {
        
        s->nelts = 0;
        s->head = 0;
        s->comp = comp;
        s->pr = pr;
        
        return s;
    }
    
    return 0;
}

/** destroy the list by deallocating used memory (O(N)).
 * @param l the list to destroy */
void 	delList	(List*s) {
    free(s);
}

/** get the Nth element of the list (O(N)).
 * @param l the list
 * @param n the index of the element in list
 * @param e (out) the searched element
 * @return OK if element found
 * @return INDER if index out of list bounds
 */
status 	nthInList	(List*s,int n,void**e) {
    if (s->nelts <= n) {
        
        Node *k = s->head;
        
        for (int i = 0; i <= n; i++) {
            *e = k->val;
            k = k->next;
        }
        
        return OK;
    }
    
    return INDER;
}

/** Insert element at a given position in the list (O(N)).
 * @param l the list to store the element in
 * @param p the position of the insertion point
 * @param e the element to insert
 * @return INDER if position is out of list bounds
 * @return ERRALLOC if memory allocation failed
 * @return OK otherwise
 */
status 	addListAt	(List*s,int n,void*e) {
    if (s->nelts <= n) {
        
        Node *newNode = (Node*)malloc(sizeof(Node));
        
        if (newNode) {
            newNode->val = e;
            newNode->next = NULL;
        }
        
        else {
            return ERRALLOC;
        }
        
        if (s->head == NULL) {
            //if list is empty insert Node as new Head.
            
            s->head = newNode;
            
            //Node successfully inserted in empty list
            s->nelts++;
            
            //printf("Node successfully inserted in empty list");
            
            return OK;
        }
        else if (n == 0) {
         
            //if position to be inserted into is 0
            newNode->next = s->head;
            s->head = newNode;
            
            //Node succesfully inserted at initial position
            s->nelts++;
            
            //printf("Node successfully inserted at initial position");
            
            return OK;
        }
        else {
            
            //Otherwise
            int atPosition;
            
            Node *tmp = s->head;
            
            for (atPosition = 1; atPosition < n; atPosition++) {
                tmp = tmp->next;
            }
            
            newNode->next = tmp->next;
            tmp->next = newNode;
            
            //Node succesfully inserted at position n
            s->nelts++;
            
            //printf("Node successfully inserted at position %d", atPosition);
            
            return OK;
            
            /*while (tmp != NULL) {
                if (atPosition == n) {
                    newNode->next = tmp->next;
                    tmp->next = newNode;
                    
                    //Node succesfully inserted at position n
                    s->nelts++;
                    
                    //printf("Node successfully inserted at position %d", atPosition);
                    
                    return OK;
                }
                
                tmp = tmp->next;
                
                atPosition++;
            }*/
            
        }
        
    }
    
    return INDER;
}

/** remove the element located at a given position in list (O(N)).
 * @param l the list to remove the element from
 * @param p the position of the element to remove
 * @param e (out) the removed element
 * @return INDER if position is out of list bounds
 * @return OK otherwise
 */
status 	remFromListAt	(List*s,int n,void**e) {
    
    if (s->nelts <= n) {
        Node *delNode = (Node*)malloc(sizeof(Node));
        
        delNode = s->head;
        
        Node *tmp = NULL;
        
        for(int i = 0; i < n; i++)
        {
            
            tmp = delNode;
            delNode = delNode->next;
            
        }
        
        if(n != 0) {
            tmp->next = delNode->next;
        }
        else {
            s->head = s->head->next;
        }
        
        *e = delNode->val;
        free(delNode);
        
        //Node successfully deleted from position n
        s->nelts--;
        return OK;
    }
    
    return INDER;
    
}

/** remove given element from given list (O(N)).
 * @param l the list to remove the element from
 * @param e the element to remove
 * @return ERRABSENT if element is not found in list
 * @return OK otherwise
 */
status 	remFromList	(List*s,void*e) {
    
    Node *findNode = (Node*)malloc(sizeof(Node));
    Node *tmp = (Node*)malloc(sizeof(Node));
    
    findNode = s->head;
    tmp = NULL;
    
    if (findNode->val == e) {
        s->head = findNode->next;
        
        //Successfully removed element with value e at position 0
        free(findNode);
        s->nelts--;
        
        return OK;
    }
    else {
        for (int i = 1; i < s->nelts; i++) {
            tmp = findNode;
            findNode = findNode->next;
            
            if (findNode == e) {
                tmp->next = findNode->next;
                
                //Successfully removed element with value e
                free(findNode);
                s->nelts--;
                
                return OK;
                
            }
        }
    }
    
    return ERRABSENT;
    
}

/** display list elements as "[ e1 ... eN ]" (O(N)).
 * The display of the element is delegated to the prFun function
 * @param l the list to display.
 */
void 	displayList	(List*s) {
    Node *listNode = (Node*)malloc(sizeof(Node));
    listNode = s->head;
    
    printf("LIST: [ ");
    
    for (int i = 1; i <= s->nelts; i++) {
        //Print function implemented from ListTest.c
        
        prString(listNode->val);
        if (i < s->nelts) {
            printf(", ");
        }
        
        listNode = listNode->next;
    }
    
    printf(" ]");
    
}

/** sequencially call given function with each element of given list (O(NxF)).
 * @param l the list
 * @param f the function
 */
void	forEach		(List*s,void(*f)(void*)) {
    
    Node *forEachNode= (Node*)malloc(sizeof(Node));
    forEachNode = s->head;
    
    for (int i = 1; i <= s->nelts; i++) {
        f(forEachNode->val);
        
        forEachNode = forEachNode->next;
    }
    
}


/** compute and return the number of elements in given list (O(1)).
 * @param l the list
 * @return the number of elements in given list
 */
int	lengthList	(List*s) {
    return s->nelts;
}

/** add given element to given list according to compFun function (O(N)).
 * @param l the list (supposedly sorted according to compFun function)
 * @param e the element to add
 * @return ERRALLOC if memory allocation failed
 * @return OK otherwise
 */
status	addList	(List*s,void*e) {
    Node* currentNode = (Node *)malloc(sizeof(Node));
    
    Node* newNode = (Node *)malloc(sizeof(Node));
    
    if (newNode) {
        newNode->val = e;
        newNode->next = NULL;
    }
    
    if (s->head == NULL || s->head->val >= newNode->val)
    {
        newNode->next = s->head;
        s->head = newNode;
        
        s->nelts++;
        
        return OK;
    }
    
    else
    {
    
        currentNode = s->head;
        
        while (currentNode->next != NULL && currentNode->next->val < newNode->val)
        {
            currentNode = currentNode->next;
        }
        
        newNode->next = currentNode->next;
        currentNode->next = newNode;
        
        s->nelts++;
        
        return OK;
    }
    return ERRALLOC;
}

/** tests whether the list contains given element (O(N)).
 * @param l the list
 * @param e the searched element
 * @return 0 if element is not found in list
 * @return 1 if element is at the head of the list (no predecessor)
 * @return (a pointer to) the predecessor of the search element otherwise
 */
Node*	isInList	(List*s,void*e) {
    Node *findNode = (Node*)malloc(sizeof(Node));
    
    findNode = s->head;
    
    if (findNode) {
        
        if (compString(findNode->val, e) == 0) {
            
            return findNode;
        }
        else {
            for (int i = 1; i <= s->nelts; i++) {
                
                if (compString(findNode->val, e) == 0) {
                    
                    return findNode;
                    
                }
                
                findNode = findNode->next;
                
            }
        }
    }
    
    return 0;
}