#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

char *postfix(char *infix);
struct node;
struct node* new_node_(int data);
int empty_(struct node* head);
void push_(struct node** head, int data);
int pop_(struct node** head);
int top_(struct node* head);
void display_(struct node* head);


