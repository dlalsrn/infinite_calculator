#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>

struct node { 
	int data; 
	struct node* next; 
}; 

struct node* new_node_(int data) 
{ 
	struct node* temp_node = (struct node*)malloc(sizeof(struct node)); 
	temp_node->data = data; 
	temp_node->next = NULL; 
	return temp_node; 
} 

int empty_(struct node* head) 
{ 
	if(!head){ 
		printf("stack is empty\n");
		return 1;
	}
	return 0; 
} 

void push_(struct node** head, int data) 
{ 
	struct node* temp_node = new_node_(data); 
	temp_node->next = *head; 
	*head = temp_node; 
	printf("PUSH: [%c]\n", data);
} 

int pop_(struct node** head) 
{ 
	if (empty_(*head)){
		return INT_MIN;
	}
	struct node* temp = *head; 
	*head = (*head)->next; 
	int element = temp->data; 
	free(temp); 

	printf("POP: [%c]\n", element);
	return element; 
} 

int top_(struct node* head) 
{ 
	if(empty_(head)) 
		return INT_MIN; 
	return head->data; 
}

void display_(struct node* head){

	if(empty_(head)){
		return;
	}
	struct node* cursor = NULL;
	cursor = head;

	printf("STACK:");
	while (cursor != NULL) {
		printf(" [%c]", cursor->data);
		cursor = cursor->next;
	}
	printf("\n");
	return;
}
