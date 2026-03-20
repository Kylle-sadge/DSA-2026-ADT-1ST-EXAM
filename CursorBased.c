#include <stdio.h>
#include <stdlib.h>

// ==========================
// 1. STRUCT DEFINITIONS
// ==========================

#define MAX 10

typedef struct {
    int elem[MAX];           // array to store element values
    int next[MAX];           // array to store next "addresses" (indices)
    int avail;               // index of first available cell
} VHeap;

// ==========================
// 2. FUNCTION PROTOTYPES
// ==========================

void initialize(VHeap* V);
int allocSpace(VHeap* V);
void deallocSpace(VHeap* V, int index);
void insertFirst(int* L, VHeap* V, int elem);
void insertLast(int* L, VHeap* V, int elem);
void insertPos(int* L, VHeap* V, int elem, int pos);
void insertSorted(int* L, VHeap* V, int elem);
void delete(int* L, VHeap* V, int elem);
void deleteAllOccurrence(int* L, VHeap* V, int elem);
void display(int L, VHeap V);

// ==========================
// 3. FUNCTION DEFINITIONS
// ==========================

void initialize(VHeap* V){
    V->avail = 0;                        // set avail to beginning of list
    for(int i = 0; i < MAX - 1; i++){    // traverse all cells except last
        V->next[i] = i + 1;              // each cell's next points to next index
    }
    V->next[MAX - 1] = -1;               // last cell's next is -1 (end of chain)
}

int allocSpace(VHeap* V){
    if(V->avail == -1){                  // check if there is an available cell
        return -1;                       // return -1 if no available cell
    }
    int index = V->avail;                // get index of first available cell
    V->avail = V->next[V->avail];        // update avail to next available cell
    return index;                        // return index of allocated cell
}

void deallocSpace(VHeap* V, int index){
    V->next[index] = V->avail;           // set next of deallocated cell to current avail
    V->avail = index;                    // update avail to newly deallocated cell
}

void insertFirst(int* L, VHeap* V, int elem){
    int newCell = allocSpace(V);         // allocate a new cell
    if(newCell != -1){                   // check if allocation was successful
        V->elem[newCell] = elem;         // set element of new cell
        V->next[newCell] = *L;           // set next of new cell to current head
        *L = newCell;                    // update list head to new cell
    }
}

void insertLast(int* L, VHeap* V, int elem){
    int newCell = allocSpace(V);         // allocate a new cell
    if(newCell != -1){                   // check if allocation was successful
        V->elem[newCell] = elem;         // set element of new cell
        V->next[newCell] = -1;           // set next of new cell to -1 (last cell)
        if(*L == -1){                    // if list is empty
            *L = newCell;                // new cell becomes the head
        } else {                         // if list is not empty
            int current = *L;            // start traversal at head
            while(V->next[current] != -1){  // traverse to last cell
                current = V->next[current]; // move to next cell
            }
            V->next[current] = newCell;  // link last cell to new cell
        }
    }
}

void insertPos(int* L, VHeap* V, int elem, int pos){
    int newCell = allocSpace(V);         // allocate a new cell
    if(newCell != -1){                   // check if allocation was successful
        V->elem[newCell] = elem;         // set element of new cell
        if(pos == 0){                    // if position is 0
            V->next[newCell] = *L;       // new cell points to current head
            *L = newCell;                // update head to new cell
        } else {                         // otherwise insert in middle
            int current = *L;            // start traversal at head
            for(int i = 0; i < pos - 1; i++){   // traverse to cell before position
                current = V->next[current];      // move to next cell
            }
            V->next[newCell] = V->next[current]; // new cell points to next cell
            V->next[current] = newCell;          // previous cell points to new cell
        }
    }
}

void insertSorted(int* L, VHeap* V, int elem){
    int newCell = allocSpace(V);             // allocate a new cell
    if(newCell != -1){                       // check if allocation was successful
        V->elem[newCell] = elem;             // set element of new cell
        if(*L == -1 || V->elem[*L] >= elem){ // if list empty or elem is smallest
            V->next[newCell] = *L;           // new cell points to current head
            *L = newCell;                    // update head to new cell
        } else {                             // otherwise find correct position
            int current = *L;                // start traversal at head
            while(V->next[current] != -1 &&  // traverse until end or
                  V->elem[V->next[current]] < elem){ // correct position found
                current = V->next[current];  // move to next cell
            }
            V->next[newCell] = V->next[current]; // new cell points to next cell
            V->next[current] = newCell;          // previous cell points to new cell
        }
    }
}

void delete(int* L, VHeap* V, int elem){
    if(*L == -1) return;                     // if list is empty do nothing
    if(V->elem[*L] == elem){                 // if head contains the element
        int temp = *L;                       // save head index
        *L = V->next[*L];                    // move head to next cell
        deallocSpace(V, temp);               // deallocate old head
        return;                              // done
    }
    int current = *L;                        // start traversal at head
    while(V->next[current] != -1){           // traverse until end
        if(V->elem[V->next[current]] == elem){  // if next cell has the element
            int temp = V->next[current];        // save next cell index
            V->next[current] = V->next[temp];   // skip over next cell
            deallocSpace(V, temp);              // deallocate removed cell
            return;                             // done (only first occurrence)
        }
        current = V->next[current];          // move to next cell
    }
}

void deleteAllOccurrence(int* L, VHeap* V, int elem){
    while(*L != -1 && V->elem[*L] == elem){  // while head contains the element
        int temp = *L;                        // save head index
        *L = V->next[*L];                     // move head to next cell
        deallocSpace(V, temp);                // deallocate old head
    }
    if(*L == -1) return;                      // if list is now empty do nothing
    int current = *L;                         // start traversal at head
    while(V->next[current] != -1){            // traverse until end
        if(V->elem[V->next[current]] == elem){   // if next cell has the element
            int temp = V->next[current];         // save next cell index
            V->next[current] = V->next[temp];    // skip over next cell
            deallocSpace(V, temp);               // deallocate removed cell
        } else {                                 // if no match
            current = V->next[current];          // move to next cell
        }
    }
}

void display(int L, VHeap V){
    int current = L;                         // start at list head
    while(current != -1){                    // loop until end of list
        printf("%d ", V.elem[current]);      // print current cell's element
        current = V.next[current];           // move to next cell
    }
    printf("\n");                            // print newline at the end
}

// ==========================
// 4. MAIN FUNCTION
// ==========================

int main(){
    VHeap V;                                 // declare VHeap
    initialize(&V);                          // initialize VHeap chain

    // declare two separate lists using same VHeap
    int L1 = -1;                             // list 1 head = -1 (empty)
    int L2 = -1;                             // list 2 head = -1 (empty)

    // insertFirst examples
    insertFirst(&L1, &V, 3);                 // L1: [3]
    insertFirst(&L1, &V, 1);                 // L1: [1] -> [3]
    insertFirst(&L1, &V, 5);                 // L1: [5] -> [1] -> [3]
    display(L1, V);                          // prints: 5 1 3

    // insertLast example
    insertLast(&L1, &V, 7);                  // L1: [5] -> [1] -> [3] -> [7]
    display(L1, V);                          // prints: 5 1 3 7

    // insertPos example
    insertPos(&L1, &V, 9, 2);               // L1: [5] -> [1] -> [9] -> [3] -> [7]
    display(L1, V);                          // prints: 5 1 9 3 7

    // insertSorted example (L2 stays sorted)
    insertSorted(&L2, &V, 5);               // L2: [5]
    insertSorted(&L2, &V, 3);               // L2: [3] -> [5]
    insertSorted(&L2, &V, 8);               // L2: [3] -> [5] -> [8]
    insertSorted(&L2, &V, 1);               // L2: [1] -> [3] -> [5] -> [8]
    display(L2, V);                          // prints: 1 3 5 8

    // delete example
    delete(&L1, &V, 9);                      // L1: [5] -> [1] -> [3] -> [7]
    display(L1, V);                          // prints: 5 1 3 7

    // deleteAllOccurrence example
    insertLast(&L1, &V, 5);                  // L1: [5] -> [1] -> [3] -> [7] -> [5]
    insertFirst(&L1, &V, 5);                 // L1: [5] -> [5] -> [1] -> [3] -> [7] -> [5]
    display(L1, V);                          // prints: 5 5 1 3 7 5
    deleteAllOccurrence(&L1, &V, 5);         // L1: [1] -> [3] -> [7]
    display(L1, V);                          // prints: 1 3 7

    return 0;
}
```

---

Key things to understand about VHeap:

| Concept | Explanation |
|---|---|
| `elem[]` | stores the actual values |
| `next[]` | stores the "address" (index) of next cell |
| `avail` | index of first free cell |
| `-1` | means NULL (end of list or no more free cells) |
| `int L` | just an index (the "address" of head) |
| Multiple lists | `L1` and `L2` can share one VHeap |
| `allocSpace` | gives you a free cell's index |
| `deallocSpace` | returns a cell back to the free chain |

---

Visualizing the VHeap:
```
Index:  [ 0 ][ 1 ][ 2 ][ 3 ][ 4 ]...
elem:   [ 5 ][ 1 ][ 3 ][ 7 ][ 0 ]...
next:   [ 1 ][ 2 ][ 3 ][-1 ][ 5 ]...
                              ↑
                         end of list

avail → first free cell
L1 = 0 → means head is at index 0
Reading L1: elem[0]=5 → elem[1]=1 → elem[2]=3 → elem[3]=7 → next=-1 STOP
