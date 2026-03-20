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
    Node* front;             // pointer to the front node of the queue
    Node* rear;              // pointer to the rear node of the queue
} Queue;

// ==========================
// 2. FUNCTION PROTOTYPES
// ==========================

Queue* initialize();
bool isFull(Queue* q);
bool isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
int front(Queue* q);
void display(Queue* q);

// ==========================
// 3. FUNCTION DEFINITIONS
// ==========================

Queue* initialize(){
    Queue* q = malloc(sizeof(Queue));   // allocate memory for Queue struct
    if(q != NULL){                      // check if malloc succeeded
        q->front = NULL;                // set front to NULL (empty queue)
        q->rear = NULL;                 // set rear to NULL (empty queue)
    }
    return q;                           // return pointer to new queue
}

bool isFull(Queue* q){
    return false;                       // linked list can never be full
}

bool isEmpty(Queue* q){
    return q->front == NULL;            // true if front is NULL (no elements)
}

void enqueue(Queue* q, int value){
    Node* newNode = malloc(sizeof(Node));   // allocate memory for new node
    if(newNode != NULL){                    // check if malloc succeeded
        newNode->data = value;              // set data of new node
        newNode->next = NULL;              // set next to NULL (will be last node)
        if(isEmpty(q)){                    // if queue is currently empty
            q->front = newNode;            // new node is both front
            q->rear = newNode;             // and rear
        } else {                           // if queue is not empty
            q->rear->next = newNode;       // link current rear to new node
            q->rear = newNode;             // update rear to new node
        }
    }
}

int dequeue(Queue* q){
    if(!isEmpty(q)){                        // check if queue is not empty
        Node* temp = q->front;             // store temporary pointer to front node
        int value = temp->data;            // store data of front node
        q->front = q->front->next;         // move front pointer to next node
        if(q->front == NULL){              // if queue becomes empty
            q->rear = NULL;                // update rear to NULL as well
        }
        free(temp);                        // free memory of old front node
        return value;                      // return stored value
    }
    return -1;                             // return -1 if queue is empty
}

int front(Queue* q){
    if(!isEmpty(q)){                        // check if queue is not empty
        return q->front->data;             // return data of front node
    }
    return -1;                             // return -1 if queue is empty
}

void display(Queue* q){
    if(!isEmpty(q)){                        // check if queue is not empty
        Node* current = q->front;          // start traversal at front
        while(current != NULL){            // loop until end of list
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
    Queue* Q = initialize();            // create a new empty queue
                                        // front -> NULL, rear -> NULL

    // enqueue examples
    enqueue(Q, 1);                      // front -> [1] <- rear
    enqueue(Q, 3);                      // front -> [1] -> [3] <- rear
    enqueue(Q, 5);                      // front -> [1] -> [3] -> [5] <- rear
    display(Q);                         // prints: 1 3 5

    // enqueue one more
    enqueue(Q, 4);                      // front -> [1] -> [3] -> [5] -> [4] <- rear
    display(Q);                         // prints: 1 3 5 4

    // dequeue example
    int val = dequeue(Q);               // removes 1, front -> [3] -> [5] -> [4] <- rear
    printf("dequeued: %d\n", val);      // prints: dequeued: 1
    display(Q);                         // prints: 3 5 4

    // front example
    int f = front(Q);                   // f = 3 (current front)
    printf("front: %d\n", f);           // prints: front: 3

    // isEmpty / isFull examples
    printf("isEmpty: %d\n", isEmpty(Q)); // prints: isEmpty: 0 (false)
    printf("isFull: %d\n", isFull(Q));   // prints: isFull: 0 (always false)

    // dequeue until empty
    dequeue(Q);                          // removes 3, front -> [5] -> [4] <- rear
    dequeue(Q);                          // removes 5, front -> [4] <- rear
    dequeue(Q);                          // removes 4, front -> NULL, rear -> NULL
    printf("isEmpty: %d\n", isEmpty(Q)); // prints: isEmpty: 1 (true)

    free(Q);                            // free the queue struct
    return 0;
}
