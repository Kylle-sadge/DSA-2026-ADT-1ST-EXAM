#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==========================
// 1. STRUCT DEFINITIONS
// ==========================

typedef struct Node {
    int data;                // data stored in the node
    struct Node* next;       // pointer to the next node
} Node;

typedef struct {
    Node* top;               // pointer to the top node of the stack
} Stack;

// ==========================
// 2. FUNCTION PROTOTYPES
// ==========================

Stack* initialize();
bool isFull(Stack* s);
bool isEmpty(Stack* s);
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);

// ==========================
// 3. FUNCTION DEFINITIONS
// ==========================

Stack* initialize(){
    Stack* s = malloc(sizeof(Stack));   // allocate memory for Stack struct
    if(s != NULL){                      // check if malloc succeeded
        s->top = NULL;                  // set top to NULL (empty stack)
    }
    return s;                           // return pointer to new stack
}

bool isFull(Stack* s){
    return false;                       // linked list can never be full
}

bool isEmpty(Stack* s){
    return s->top == NULL;              // true if top is NULL (no elements)
}

void push(Stack* s, int value){
    Node* newNode = malloc(sizeof(Node));   // allocate memory for new node
    if(newNode != NULL){                    // check if malloc succeeded
        newNode->data = value;              // set data of new node
        newNode->next = s->top;            // link new node to current top
        s->top = newNode;                  // update top to point to new node
    }
}

int pop(Stack* s){
    if(!isEmpty(s)){                        // check if stack is not empty
        Node* temp = s->top;               // get temporary pointer to top node
        int value = temp->data;            // store data of top node
        s->top = s->top->next;             // move top pointer to next node
        free(temp);                        // free memory of old top node
        return value;                      // return stored value
    }
    return -1;                             // return -1 if stack is empty
}

int peek(Stack* s){
    if(!isEmpty(s)){                        // check if stack is not empty
        return s->top->data;               // return data of top node
    }
    return -1;                             // return -1 if stack is empty
}

void display(Stack* s){
    if(!isEmpty(s)){                        // check if stack is not empty
        Node* current = s->top;            // create pointer starting at top
        while(current != NULL){            // traverse until end of list
            printf("%d ", current->data);  // print current node's data
            current = current->next;       // move to next node
        }
        printf("\n");                      // print newline at the end
    }
}

// ==========================
// 4. MAIN FUNCTION
// ==========================

int main(){
    Stack* S = initialize();            // create a new empty stack
                                        // top -> NULL

    // push examples
    push(S, 1);                         // top -> [1] -> NULL
    push(S, 3);                         // top -> [3] -> [1] -> NULL
    push(S, 5);                         // top -> [5] -> [3] -> [1] -> NULL
    display(S);                         // prints: 5 3 1

    // push one more
    push(S, 4);                         // top -> [4] -> [5] -> [3] -> [1] -> NULL
    display(S);                         // prints: 4 5 3 1

    // pop example
    int val = pop(S);                   // removes 4, top -> [5] -> [3] -> [1] -> NULL
    printf("popped: %d\n", val);        // prints: popped: 4
    display(S);                         // prints: 5 3 1

    // peek example
    int peeked = peek(S);               // peeked = 5 (current top)
    printf("peek: %d\n", peeked);       // prints: peek: 5

    // isEmpty / isFull examples
    printf("isEmpty: %d\n", isEmpty(S)); // prints: isEmpty: 0 (false)
    printf("isFull: %d\n", isFull(S));   // prints: isFull: 0 (always false)

    free(S);                            // free the stack struct
    return 0;
}
