#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
} * HEAD;

// Creating a Circular Linked List from an Array A
void create(int A[], int n) {
    int i;
    struct Node *t, *last;
    HEAD = (struct Node *)malloc(sizeof(struct Node));
    HEAD->data = A[0];
    HEAD->next = HEAD; // Points to itself.
    last = HEAD;

    for (i = 1; i < n; i++) {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = A[i];
        t->next = last->next;
        last->next = t;
        last = t;
    }
}

void Display(struct Node *head) {
    do {
        head->next == HEAD ? printf("%d ", head->data) : printf("%d -> ", head->data);
        head = head->next;
    } while (head != HEAD);
    printf("\n");
}

void DisplayRecursive(struct Node *head) {
    static int flag = 0;
    if (head != HEAD || !flag) {
        flag = 1;
        head->next == HEAD ? printf("%d ", head->data) : printf("%d -> ", head->data);
        DisplayRecursive(head->next);
    }
    flag = 0;
}

// NOTE: Getting the Length of a Circular Linked List
int LengthList(struct Node *head) {
    int len = 0;
    do {
        len++;
        head = head->next;
    } while (head != HEAD);
    return len;
}

// NOTE: Inserting in a Circular Linked List
/* 
Case 1. Inserting before HEAD. // Moving the HEAD pointer to the new node is Optional.
Case 2. Inserting elsewhere in a given position
 */

void Insert(struct Node *head, int pos, int x) {
    struct Node *t;

    t = (struct Node *)malloc(sizeof(struct Node));
    t->data = x;

    if (pos < 0 || pos > LengthList(HEAD))
        return;

    if (pos == 0) {
        if (!HEAD) {
            HEAD = t;
            HEAD->next = HEAD;
        } else {
            head = HEAD;
            while (head->next != HEAD)
                head = head->next;
            head->next = t;
            t->next = HEAD;
            HEAD = t;
        }
    } else {
        head = HEAD;
        for (int i = 0; i < pos - 1; i++)
            head = head->next;
        t->next = head->next;
        head->next = t;
    }
}

// NOTE: Deleting a node from a Circular Linked List
/* 
Case 1. Deleting HEAD node
Case 2. Deleting any other node from a given position
*/
int Delete(struct Node *p, int index) {
    int x;
    struct Node *q;

    if (index < 0 || index > LengthList(HEAD))
        return -1;
    if (index == 1) { // Deleting HEAD Node
        while (p->next != HEAD)
            p = p->next;
        x = HEAD->data;
        if (HEAD == p) {
            free(HEAD);
            HEAD = NULL;
        } else {
            p->next = HEAD->next;
            free(HEAD);
            HEAD = p->next;
        }
    } else {
        for (int i = 0; i < index - 1; i++)
            p = p->next;
        q = p->next;
        p->next = q->next;
        x = q->data;
        free(q);
        q = NULL;
    }
    return x;
}

// main function
int main() {

    int A[] = {8, 3, 9, 6, 2};
    create(A, 5);
    // Display(HEAD);
    printf("Original: ");
    DisplayRecursive(HEAD);
    printf("\nInserting elements...\n");
    Insert(HEAD, 0, 5); // 5 at index 0
    Insert(HEAD, 4, 4); // 4 at index 4
    DisplayRecursive(HEAD);
    printf("\nLength: %d\n", LengthList(HEAD));
    printf("Deleting node at index 3 with value %d\n", Delete(HEAD, 3));
    DisplayRecursive(HEAD);
    return 0;
} // end of main
