#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==========================
// 1. STRUCT DEFINITIONS
// ==========================

#define MAX 100

typedef struct {
    int items[MAX];          // array to store stack elements
    int top;                 // index of the current top element
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
int top(Stack* s);
void display(Stack* s);

// ==========================
// 3. FUNCTION DEFINITIONS
// ==========================

Stack* initialize(){
    Stack* s = malloc(sizeof(Stack));   // allocate memory for Stack struct
    if(s != NULL){                      // check if malloc succeeded
        s->top = -1;                    // set top to -1 (empty stack)
    }
    return s;                           // return pointer to new stack
}

bool isFull(Stack* s){
    return s->top == MAX - 1;           // true if top reached last index
}

bool isEmpty(Stack* s){
    return s->top == -1;                // true if top is -1 (no elements)
}

void push(Stack* s, int value){
    if(!isFull(s)){                     // check if stack is not full
        s->top++;                       // increment top first
        s->items[s->top] = value;       // place new value at top position
    }
}

int pop(Stack* s){
    if(!isEmpty(s)){                    // check if stack is not empty
        int value = s->items[s->top];   // get value at current top
        s->top--;                       // decrement top
        return value;                   // return retrieved value
    }
    return -1;                          // return -1 if stack is empty
}

int peek(Stack* s){
    if(!isEmpty(s)){                    // check if stack is not empty
        return s->items[s->top];        // return value at top without removing
    }
    return -1;                          // return -1 if stack is empty
}

int top(Stack* s){
    return s->top;                      // return the current top index
}

void display(Stack* s){
    if(!isEmpty(s)){                            // check if stack is not empty
        for(int i = s->top; i >= 0; i--){       // iterate from top down to bottom
            printf("%d ", s->items[i]);          // print each element
        }
        printf("\n");                            // print newline at the end
    }
}

// ==========================
// 4. MAIN FUNCTION
// ==========================

int main(){
    Stack* S = initialize();            // create a new empty stack

    // push examples
    push(S, 1);                         // stack: [1]        top: 0
    push(S, 3);                         // stack: [1,3]      top: 1
    push(S, 2);                         // stack: [1,3,2]    top: 2
    push(S, 5);                         // stack: [1,3,2,5]  top: 3
    display(S);                         // prints: 5 2 3 1 (top to bottom)

    // pop example
    int val = pop(S);                   // val = 5, top: 2
    printf("popped: %d\n", val);        // prints: popped: 5
    display(S);                         // prints: 2 3 1

    // peek example
    int peeked = peek(S);               // peeked = 2 (top element)
    printf("peek: %d\n", peeked);       // prints: peek: 2

    // top example
    int topIdx = top(S);                // topIdx = 2 (current top index)
    printf("top index: %d\n", topIdx);  // prints: top index: 2

    // isFull / isEmpty examples
    printf("isFull: %d\n", isFull(S));   // prints: isFull: 0 (false)
    printf("isEmpty: %d\n", isEmpty(S)); // prints: isEmpty: 0 (false)

    free(S);                            // free the stack struct
    return 0;
}
