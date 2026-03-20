LinkList Implementation:

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;         
    struct Node* next; 
} Node;

typedef struct List {
    Node* head;       
    int count;         
} List;

List* initialize(){
    List* L = malloc(sizeof(List));  // create a new List struct in memory
    if(L != NULL){                   // check if malloc succeeded
        L->head = NULL;              // set head to NULL (no nodes yet)
        L->count = 0;               // set count to 0 (empty list)
    }
    return L;                        // return the new list
}

void empty(List *L){
    Node *trav = L->head;            // start traversal at the head
    Node *temp;                      // temporary pointer to hold next node
    while(trav != NULL){             // loop until end of list
        temp = trav->next;           // save next node before freeing current
        free(trav);                  // free current node
        trav = temp;                 // move to saved next node
    }
    L->head = NULL;                  // head no longer points to freed memory
    L->count = 0;                    // reset count to 0
}

void insertFirst(List *L, int val){
    Node *newNode = malloc(sizeof(Node));  // create a new node in memory
    if(newNode != NULL){                   // check if malloc succeeded
        newNode->data = val;               // set new node's data to val
        newNode->next = L->head;           // new node points to current head
        L->head = newNode;                 // head now points to new node
        L->count++;                        // increment count
    }
}

void insertLast(List *L, int val){
    Node *newNode = malloc(sizeof(Node));  // create a new node in memory
    if(newNode != NULL){                   // check if malloc succeeded
        newNode->data = val;               // set new node's data to val
        newNode->next = NULL;              // new node points to NULL (last node)
        if(L->head == NULL){               // if list is empty
            L->head = newNode;             // new node becomes the head
        } else {                           // if list is not empty
            Node *current = L->head;       // start traversal at head
            while(current->next != NULL){  // traverse until last node
                current = current->next;   // move to next node
            }
            current->next = newNode;       // attach new node at the end
        }
        L->count++;                        // increment count
    }
}

void insertPos(List *L, int val, int index){
    if(index < L->count){                  // check if index is valid
        if(index == 0){                    // if index is 0
            insertFirst(L, val);           // call insertFirst
        } else if(index == L->count){     // if index equals count
            insertLast(L, val);            // call insertLast
        } else {                           // otherwise insert in middle
            Node *newNode = malloc(sizeof(Node));  // create new node
            if(newNode != NULL){                   // check if malloc succeeded
                newNode->data = val;               // set new node's data
                Node *current = L->head;           // start traversal at head
                for(int i = 0; i < index - 1; i++){  // traverse index-1 times
                    current = current->next;           // move to next node
                }
                newNode->next = current->next;  // new node points to next node
                current->next = newNode;         // previous node points to new node
                L->count++;                      // increment count
            }
        }
    }
}

void deleteStart(List *L){
    if(L->head != NULL){             // check if list is not empty
        Node *current = L->head;     // save current head in pointer
        L->head = current->next;     // move head to next node
        free(current);               // free old head
        L->count--;                  // decrement count
    }
}

void deleteLast(List *L){
    if(L->head != NULL){                        // check if list is not empty
        if(L->count == 1){                      // if only one node
            free(L->head);                      // free the head node
            L->head = NULL;                     // set head to NULL
        } else {                                // if more than one node
            Node *current = L->head;            // start traversal at head
            for(int i = 0; i < L->count - 2; i++){  // traverse to second to last
                current = current->next;             // move to next node
            }
            free(current->next);                // free the last node
            current->next = NULL;               // second to last now points to NULL
        }
        L->count--;                             // decrement count
    }
}

void deletePos(List *L, int index){
    if(index < L->count){                  // check if index is valid
        if(index == 0){                    // if index is 0
            deleteStart(L);                // call deleteStart
        } else {                           // otherwise delete in middle
            Node *current = L->head;       // start traversal at head
            for(int i = 0; i < index - 1; i++){  // traverse index-1 times
                current = current->next;          // move to next node
            }
            Node *temp = current->next;    // save target node in temp
            current->next = temp->next;    // skip over target node
            free(temp);                    // free target node
            L->count--;                    // decrement count
        }
    }
}

int retrieve(List *L, int index){
    if(index < L->count){              // check if index is valid
        Node *current = L->head;       // start traversal at head
        for(int i = 0; i < index; i++){  // traverse index times
            current = current->next;     // move to next node
        }
        return current->data;          // return data at index
    }
    return -1;                         // return -1 if index invalid
}

int locate(List *L, int val){
    if(L->head == NULL) return -1;     // if list empty return -1
    Node *current = L->head;           // start traversal at head
    int index = 0;                     // start index counter at 0
    while(current != NULL){            // loop until end of list
        if(current->data == val)       // if data matches
            return index;              // return current index
        current = current->next;       // move to next node
        index++;                       // increment index
    }
    return -1;                         // return -1 if not found
}

void display(List *L){
    Node *current = L->head;           // start traversal at head
    while(current != NULL){            // loop until end of list
        printf("%d ", current->data);  // print current node's data
        current = current->next;       // move to next node
    }
    printf("\n");                      // print newline at the end
}
