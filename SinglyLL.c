#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
} * first, *second, *third; // Global pointer first.

/**
 * @brief Creates a Linked List from array
 * 
 */
void create(int A[], int n) {
    int i;                                              // Scanning through array
    struct Node *t, *last;                              // Temporary node pointer,
    first = (struct Node *)malloc(sizeof(struct Node)); // New node in heap and first will point to it
    first->data = A[0];
    first->next = NULL;
    last = first;

    for (i = 1; i < n; i++) { // 0th element is created
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t; // Adds node to the last of the previous Node
        last = t;       // T becomes last node.
    }
}

void create2(int A[], int n) {
    int i;
    struct Node *t, *last;
    second = (struct Node *)malloc(sizeof(struct Node));
    second->data = A[0];
    second->next = NULL;
    last = second;

    for (i = 1; i < n; i++) { // 0th element is created
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = NULL;
        last->next = t; // Adds node to the last of the previous Node
        last = t;       // T becomes last node.
    }
}

void Display(struct Node *p) { // Has access to first pointer
    while (p != NULL) {
        !p->next ? printf("%d", p->data) : printf("%d -> ", p->data);
        p = p->next;
    }
}

void Display_Recursive(struct Node *p) {
    if (p) {
        !p->next ? printf("%d", p->data) : printf("%d -> ", p->data);
        Display_Recursive(p->next);
    }
}
void Display_Recursive_Reverse(struct Node *p) {
    if (p) {
        Display_Recursive_Reverse(p->next);
        printf("%d -> ", p->data);
    }
}

int countNodes(struct Node *p) {
    int count = 0;
    while (p) {
        count += 1;
        p = p->next;
    }
    return count;
}

int countNodes_Recursive(struct Node *p) {
    // If p is not null, it should count
    if (!p)
        return 0;
    else
        return 1 + countNodes_Recursive(p->next); // Done at returning
}

int sumNodes(struct Node *p) {
    int sum = 0;
    while (p) {
        sum += p->data;
        p = p->next;
    }
    return sum;
}

int sumNodes_Recursive(struct Node *p) {
    if (!p)
        return 0;
    else
        return p->data + sumNodes_Recursive(p->next);
}

int maxElement(struct Node *p) {
    if (!p) {
        return INT_MIN;
    }
    int currMax = p->data;
    while (p) {
        p->data > currMax ? currMax = p->data : 1;
        p = p->next;
    }
    return currMax;
}

int maxElement_Recursive(struct Node *p) {
    int x = 0;
    if (!p)
        return INT_MIN;
    else {
        x = maxElement_Recursive(p->next);
        return x > p->data ? x : p->data; // Ternary. (Condition ? True(if yes) : False(if no))
    }
}

// NOTE: Searching in a Linked List

struct Node *Search(struct Node *p, int key) {
    while (p) {
        if (key == p->data)
            return p;
        p = p->next;
    }
    return NULL; // Key is not found
}

struct Node *Search_Recursive(struct Node *p, int key) {
    if (!p)
        return NULL;
    if (key == p->data)
        return p;
    return Search_Recursive(p->next, key);
}

bool Search_Bool(struct Node *p, int key) {
    while (p) {
        if (key == p->data)
            return true;
        p = p->next;
    }
    return false;
}

struct Node *Search_Improved(struct Node *p, int key) {
    struct Node *q = NULL; // Node follows
    while (p) {
        if (key == p->data) {
            q->next = p->next;
            p->next = first;
            first = p;
            return p; // or return first, p is now the head.
        }
        q = p;
        p = p->next;
    }
    return NULL;
}

// NOTE: Inserting in a Linked List
/* 
Case 1. Insert before first node = O(1) Constant Time
    - Create a new node with the data
        Node *t = new Node;
        t->data = x;
        t->next = first;
        first = t;
    - Make it point on first
    - Make first point to new node
Case 2. Inserting after given position (i.e. position=4) = O(n) Linear Time
    - Create a new node with the data
        Traverse with a pointer p until before insertion position by 1
        Node *t = new Node;
        t->data = x;
        TRAVERSE
        for(i = 0: i < pos - 1; i++) p = p->next;
        t->next = p->next;
        p->next = t;

 */
void insert(struct Node *p, int pos, int x) {
    struct Node *t;
    if (pos < 0 || pos > countNodes(p))
        return;
    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;

    if (pos == 0) {
        t->next = first;
        first = t;
    } else {
        for (int i = 0; i < pos - 1; i++)
            p = p->next;
        t->next = p->next;
        p->next = t;
    }
}

void insertLast(struct Node *p, int x) {
    struct Node *last;
    struct Node *t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;
    if (!p) {
        first = last = t;
    }
    while (p->next) {
        p = p->next;
    }
    p->next = t;
}

void insertSorted(struct Node *p, int x) {
    struct Node *t, *q = NULL;
    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;
    t->next = NULL;

    if (!first)
        first = t;
    else {
        while (p && p->data < x) {
            q = p;
            p = p->next;
        }
        if (p == first) {
            t->next = first;
            first = t;
        } else {
            t->next = q->next;
            q->next = t;
        }
    }
}

// NOTE: Deleting node from Linked List
// Case 1. Deleting head node O(1).
/* 
Node *p = first;
first = first->next;
x = p->data;
delete p;
 */
// Case 2. Deleting any other node

int deleteNode(struct Node *p, int pos) {
    int x;
    if (pos == 0) {
        first = first->next;
        x = p->data;
        free(p);
    } else {
        struct Node *q = NULL;
        for (int i = 0; i < pos - 1; i++) {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        x = p->data;
        free(p);
    }

    return x;
}

// NOTE: Check if Linked List is sorted

bool isSorted(struct Node *p) {
    int x = INT_MIN;
    while (p) {
        if (p->data < x)
            return false;
        x = p->data;
        p = p->next;
    }
    return true;
}

// NOTE: Remove duplicate data nodes

void removeDuplicates(struct Node *p) {
    // BUG: Only removes if duplicates are adjacent to each other.
    struct Node *q = p->next;
    while (q) {
        if (p->data != q->data) {
            // Slide the pointers
            p = q;
            q = q->next;
        } else {
            p->next = q->next;
            free(q);
            q = p->next;
        }
    }
}

// NOTE: Reversing Linked List

void reverseIterative(struct Node *p) {
    struct Node *q = NULL, *r = NULL;
    while (p) {
        // Slide
        r = q;
        q = p;
        p = p->next;
        // Reverse
        q->next = r;
    }
    // q is now at the end and should be made the head
    first = q;
}

void reverseRecursive(struct Node *p, struct Node *q) {
    if (p) {
        reverseRecursive(p->next, p);
        p->next = q;
    } else {
        first = q;
    }
}

// NOTE: Merging two sorted linked lists

void Merge(struct Node *p, struct Node *q) {
    struct Node *last;
    if (p->data < q->data) {
        third = last = p;
        p = p->next;
        third->next = NULL;
    } else {
        third = last = q;
        q = q->next;
        third->next = NULL;
    }
    while (p && q) {
        if (p->data < q->data) {
            last->next = p;
            last = p;
            p = p->next;
            last->next = NULL;
        } else {
            last->next = q;
            last = q;
            q = q->next;
            last->next = NULL;
        }
    }
    if (p) {
        last->next = p;
    }
    if (q) {
        last->next = q;
    }
}

// NOTE: Check for LOOP in the Linked List
bool isLoop(struct Node *f) {
    struct Node *p, *q;
    p = q = f;
    do {
        p = p->next;
        q = q->next;
        q = q != NULL ? q->next : q;
    } while (p && q && p != q);
    if (p == q)
        return true;
    return false;
}

void newline() {
    //NOTE: Newline easy!
    printf("\n");
}

// main function
int main() {
    // NOTE: Displaying a Singly Linked List
    int A[] = {3, 5, 7, 10, 15}; // Array of elements
    // -- Creating Linked List --
    create(A, sizeof(A) / sizeof(int));
    // Testing Display
    printf("Displaying: ");
    Display(first);
    newline();
    printf("Displaying recursively: ");
    Display_Recursive(first);
    newline();
    printf("Displaying recursively reverse: ");
    Display_Recursive_Reverse(first);
    newline();
    // Testing counting nodes
    printf("Number of nodes in Linked List: %d\n", countNodes(first));
    printf("Number of nodes in Linked List Recursively: %d\n", countNodes_Recursive(first));
    // Testing sum nodes
    printf("Sum of nodes in Linked List: %d\n", sumNodes(first));
    printf("Sum of nodes in Linked List Recursively: %d\n", sumNodes_Recursive(first));
    // Testing max node
    printf("Maximum element in Linked List: %d\n", maxElement(first));
    printf("Maximum element in Linked List Recursively: %d\n", maxElement_Recursive(first));
    // Testing searching
    struct Node *found = Search(first, 7);
    if (found) {
        printf("Node found: %d", found->data);
    } else {
        printf("Node not found :(");
    }
    newline();
    struct Node *found2 = Search(first, 10);
    if (found2) {
        printf("Node found: %d", found2->data);
    } else {
        printf("Node not found :(");
    }
    newline();
    // Testing bool searching
    int x = 10;
    if (Search_Bool(first, x)) {
        printf("Node %d found (yes)", x);
    } else {
        printf("Node %d not found (no)", x);
    }
    newline();
    struct Node *found3 = Search_Improved(first, 15);
    if (found3) {
        printf("Node found: %d", found3->data);
    } else {
        printf("Node not found :(");
    }
    newline();
    printf("Displaying new improved Linked List\n");
    Display(first);
    // Testing insertion
    insert(first, 3, 45); // Inserting at index 3
    newline();
    printf("Inserted 45 at index 3");
    newline();
    printf("Displaying new Linked List: ");
    Display(first);
    newline();
    // Testing insertion at end
    insertLast(first, 60);
    printf("Inserted 60 at the end of the Linked List:");
    newline();
    printf("Displaying new Linked List: ");
    Display(first);
    // Testing deletion
    deleteNode(first, 0);
    newline();
    printf("Deleted first node (15): ");
    Display(first);
    deleteNode(first, 3); // Delete node at position 3, that has index 2
    newline();
    printf("Deleted third node (45): ");
    Display(first);
    newline();
    if (isSorted(first)) {
        printf("Linked List is sorted!");
    } else {
        printf("Linked List is not sorted!");
    }
    // Testing removing duplicates
    insertLast(first, 60);
    newline();
    printf("Adding a 60 to the end: ");
    Display(first);
    printf("\nRemoving duplicates...");
    removeDuplicates(first);
    newline();
    Display(first);
    newline();
    printf("Reversing Linked List...");
    newline();
    reverseIterative(first);
    printf("Reversed Linked List: ");
    Display(first);
    reverseIterative(first);
    newline();
    printf("Reversing Linked List Recursively...");
    newline();
    reverseRecursive(first, NULL);
    printf("Reversed Linked List Recursively: ");
    Display(first);
    newline();
    // Testing merging two linked lists
    int B[] = {0, 4, 6, 8, 11};
    create2(B, 5);
    reverseRecursive(first, NULL); // Linked List in increasing order now
    printf("First Linked List: ");
    Display(first);
    newline();
    printf("Second Linked List: ");
    Display(second);
    printf("\nMerging...");
    Merge(first, second);
    newline();
    printf("New merged sorted Linked List: ");
    Display(third);
    newline();
    return 0;
} // end of main
