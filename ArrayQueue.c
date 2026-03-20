#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ==========================
// 1. STRUCT DEFINITIONS
// ==========================

#define MAX 100

typedef struct {
    int items[MAX];          // array to store queue elements
    int count;               // number of elements currently in queue
    int front;               // index of the front element
    int rear;                // index of the rear element
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
        q->count = 0;                   // set count to 0 (empty queue)
        q->front = 1;                   // set front to 1 (initial position)
        q->rear = 0;                    // set rear to 0 (initial position)
    }
    return q;                           // return pointer to new queue
}

bool isFull(Queue* q){
    return q->count == MAX;             // true if count reached MAX
}

bool isEmpty(Queue* q){
    return q->count == 0;               // true if count is 0 (no elements)
}

void enqueue(Queue* q, int value){
    if(!isFull(q)){                             // check if queue is not full
        q->rear = (q->rear + 1) % MAX;          // increment rear circularly
        q->items[q->rear] = value;              // place new value at rear position
        q->count++;                             // increment count
    }
}

int dequeue(Queue* q){
    if(!isEmpty(q)){                            // check if queue is not empty
        int value = q->items[q->front];         // store value at front before removing
        if(q->count == 1){                      // if this is the last element
            q->front = 1;                       // reset front to initial state
            q->rear = 0;                        // reset rear to initial state
        } else {                                // if not the last element
            q->front = (q->front + 1) % MAX;   // increment front circularly
        }
        q->count--;                             // decrement count
        return value;                           // return removed value
    }
    return -1;                                  // return -1 if queue is empty
}

int front(Queue* q){
    if(!isEmpty(q)){                    // check if queue is not empty
        return q->items[q->front];      // return value at front without removing
    }
    return -1;                          // return -1 if queue is empty
}

void display(Queue* q){
    if(!isEmpty(q)){                                    // check if queue is not empty
        int i = q->front;                               // start from front
        for(int c = 0; c < q->count; c++){              // loop count times
            printf("%d ", q->items[i]);                 // print current element
            i = (i + 1) % MAX;                          // move circularly to next
        }
        printf("\n");                                   // print newline at the end
    }
}

// ==========================
// 4. MAIN FUNCTION
// ==========================

int main(){
    Queue* Q = initialize();            // create a new empty queue
                                        // count: 0, front: 1, rear: 0

    // enqueue examples
    enqueue(Q, 1);                      // items: [1]        count:1 front:1 rear:1
    enqueue(Q, 3);                      // items: [1,3]      count:2 front:1 rear:2
    enqueue(Q, 2);                      // items: [1,3,2]    count:3 front:1 rear:3
    enqueue(Q, 5);                      // items: [1,3,2,5]  count:4 front:1 rear:4
    display(Q);                         // prints: 1 3 2 5 (front to rear)

    // dequeue example
    int val = dequeue(Q);               // val=1, count:3 front:2 rear:4
    printf("dequeued: %d\n", val);      // prints: dequeued: 1
    display(Q);                         // prints: 3 2 5

    // front example
    int f = front(Q);                   // f = 3 (current front element)
    printf("front: %d\n", f);           // prints: front: 3

    // isFull / isEmpty examples
    printf("isFull: %d\n", isFull(Q));   // prints: isFull: 0 (false)
    printf("isEmpty: %d\n", isEmpty(Q)); // prints: isEmpty: 0 (false)

    free(Q);                            // free the queue struct
    return 0;
}
