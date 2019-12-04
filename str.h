#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    char* data;     
	struct Node* next;
}string_node;

char *postfix(char *infix);
struct Node;
typedef struct Node string_node;
string_node* new_node(char* data);
int empty(string_node* head);
void push(string_node** head, char* data);
char* pop(string_node** head);
char* top(string_node* head);
void display(string_node* head);
char* add(char*, char*, char);
char* minus(char*, char*, char);
char* multiply(char*, char*, char);
char* calc(char*, char*, char);
int Operator_Count(char* ary);
int Find_Point(char* ary);
char* Clear(char* a);
char* Round(char* ary, int max_point);
char* Change_str(char* a);
void Array_Sum(char* Num);
struct node;
struct node* new_node_(int data);
int empty_(struct node* head);
void push_(struct node** head, int data);
int pop_(struct node** head);
int top_(struct node* head);
void display_(struct node* head);

