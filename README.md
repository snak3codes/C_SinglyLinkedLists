# C_SinglyLinkedLists
Singly Linked List and Circular Linked List in C Language


# Notes_Singly_Linked_Lists

1.> :::::::::: Declaring a Linked list :::::::::::

In C language, a linked list can be implemented using structure and pointers .

struct LinkedList{
    int data;
    struct LinkedList *next;
 };
 
2.> :::::::::: Creating a Node:::::::::

Let's define a data type of struct LinkedListto make code cleaner.

typedef struct LinkedList *node; //Define node as pointer of data type struct LinkedList

node createNode(){
    node temp; // declare a node
    temp = (node)malloc(sizeof(struct LinkedList)); // allocate memory using malloc()
    temp->next = NULL;// make next point to NULL
    return temp;//return the new node
}
• typedef is used to define a data type in C.

• malloc() is used to dynamically allocate a single block of memory in C, it is available in the header file stdlib.h.

• sizeof() is used to determine size in bytes of an element in C. Here it is used to determine size of each node and sent as a parameter to malloc.
