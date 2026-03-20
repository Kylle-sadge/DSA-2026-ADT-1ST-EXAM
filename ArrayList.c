#include <stdio.h>
#include <stdlib.h>

// ==========================
// 1. STRUCT DEFINITIONS
// ==========================

#define MAX 100

typedef struct {
    int elem[MAX];           // array to store elements
    int count;               // number of elements currently in the list
} List;

// ==========================
// 2. FUNCTION PROTOTYPES
// ==========================

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);

// ==========================
// 3. FUNCTION DEFINITIONS
// ==========================

List initialize(List L){
    L.count = 0;             // set count to 0 (empty list)
    return L;                // return the initialized list
}

List insertPos(List L, int data, int position){
    if(position <= L.count && L.count != MAX){  // check if position valid and not full
        for(int i = L.count; i > position; i--){  // shift elements right
            L.elem[i] = L.elem[i-1];               // move each element one slot right
        }
        L.elem[position] = data;                // place new value at position
        L.count++;                              // increment count
    }
    return L;                                   // return modified list
}

List deletePos(List L, int position){
    if(position <= L.count){                        // check if position is valid
        for(int i = position; i < L.count - 1; i++){  // shift elements left
            L.elem[i] = L.elem[i+1];                   // move each element one slot left
        }
        L.count--;                              // decrement count
    }
    return L;                                   // return modified list
}

int locate(List L, int data){
    for(int i = 0; i < L.count; i++){           // loop through all elements
        if(L.elem[i] == data)                   // if data matches
            return i;                           // return current index
    }
    return -1;                                  // return -1 if not found
}

List insertSorted(List L, int data){
    if(L.count != MAX){                         // check if array is not full
        int position = 0;                       // start position at 0
        while(position < L.count && L.elem[position] < data){  // find correct position
            position++;                         // move position forward
        }
        for(int i = L.count; i > position; i--){  // shift elements right
            L.elem[i] = L.elem[i-1];               // move each element one slot right
        }
        L.elem[position] = data;                // place new value at position
        L.count++;                              // increment count
    }
    return L;                                   // return modified list
}

void display(List L){
    for(int i = 0; i < L.count; i++){           // loop through all elements
        printf("%d ", L.elem[i]);               // print current element
    }
    printf("\n");                               // print newline at the end
}

// ==========================
// 4. MAIN FUNCTION
// ==========================

int main(){
    List L;                                     // declare a List variable
    L = initialize(L);                          // initialize the list

    // insertPos examples
    L = insertPos(L, 1, 0);                     // list: [1]
    L = insertPos(L, 3, 1);                     // list: [1, 3]
    L = insertPos(L, 2, 2);                     // list: [1, 3, 2]
    L = insertPos(L, 5, 3);                     // list: [1, 3, 2, 5]
    display(L);                                 // prints: 1 3 2 5

    // deletePos example
    L = deletePos(L, 1);                        // list: [1, 2, 5]
    display(L);                                 // prints: 1 2 5

    // locate example
    int idx = locate(L, 2);                     // idx = 1
    printf("locate: %d\n", idx);               // prints: locate: 1

    // insertSorted examples
    List S;                                     // declare a new List for sorted
    S = initialize(S);                          // initialize the sorted list
    S = insertSorted(S, 1);                     // list: [1]
    S = insertSorted(S, 3);                     // list: [1, 3]
    S = insertSorted(S, 5);                     // list: [1, 3, 5]
    S = insertSorted(S, 10);                    // list: [1, 3, 5, 10]
    S = insertSorted(S, 8);                     // list: [1, 3, 5, 8, 10]
    display(S);                                 // prints: 1 3 5 8 10

    return 0;
}
