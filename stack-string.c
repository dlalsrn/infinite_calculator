#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h>

typedef struct Node { 
	char* data; 
	struct Node* next; 
}string_node; 

string_node* new_node(char* data) 
{ 
	string_node* temp_node = (string_node*)malloc(sizeof(string_node)); 
	temp_node->data = data; 
	temp_node->next = NULL; 
	return temp_node; 
} 

int empty(string_node* head) 
{ 
	if(!head){ 
		printf("stack is empty\n");
		return 1;
	}
	return 0; 
} 

void push(string_node** head, char* data) 
{ 
	string_node* temp_node = new_node(data); 
	temp_node->next = *head; 
	*head = temp_node; 
	printf("PUSH: [%s]\n", data);
} 

char* pop(string_node** head) 
{ 
	if (empty(*head)){
		return "empty";
	}
	string_node* temp = *head; 
	*head = (*head)->next; 
	char* element = temp->data; 
	free(temp); 

	printf("POP: [%s]\n", element);
	return element; 
} 

char* top(string_node* head) 
{ 
	if(empty(head)) 
		return "empty"; 
	return head->data; 
}

void display(string_node* head){

	if(empty(head)){
		return;
	}
	string_node* cursor = NULL;
	cursor = head;

	printf("STACK:");
	while (cursor != NULL) {
		printf(" [%s]", cursor->data);
		cursor = cursor->next;
	}
	printf("\n");
	return;
}
