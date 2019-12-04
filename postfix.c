#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str.h"

char *postfix(char *infix)
{
	char *str;
	str = (char *) malloc(2*sizeof(char)*strlen(infix)+1);
	memset(str, 0, 2*sizeof(char)*strlen(infix)+1);
	struct node* head = NULL; //stack <char> operator;
	char* temp;
	temp = (char *) malloc(sizeof(char));
	//char space = ' ';
	char* space = " ";
	int count = 1;

	//push(&top, 'C');
	while (*infix != '\0') 
	{
			printf("infix[%d]:%c\n",count,*infix);
		//if (97 <= *infix && *infix <= 122)
		if (*infix != '+' && *infix != '-' && *infix != '*' && *infix != '(' && *infix != ')')
		{
			strncat(str, infix, 1);
			//strncat(str, space, 1);
		}
		else 
		{
			strncat(str, space, 1);
			if (*infix == '+' || *infix == '-') 
			{
				if (empty_(head))
					push_(&head, *infix);
				else if (top_(head) == '-')
				{
					*temp = pop_(&head);
					//strncat(str, space, 1);
					strncat(str, temp, 1);
					strncat(str, space, 1);
					push_(&head, *infix);
				}
				else if (top_(head) == '+')
					push_(&head, *infix);
				else if (top_(head) == '*')
				{
					while (top_(head) == '*' || top_(head) == '-')
					{
						//printf("%c\n", top(head));
						*temp = pop_(&head);
						//strncat(str, space, 1);
						strncat(str,temp,1);
						strncat(str,space,1);
						//push(&head, *infix);
					}
					push_(&head, *infix);
				}
			}
			else if (*infix == '*')
			{
				push_(&head, *infix);
			}
			/*
			else if (*infix == '(') 
				push(&head, *infix);
			else if (*infix == ')')
			{
				while (top(head) != '(')
				{
					*temp = top(head);
					pop(&head);
					strncat(str,temp,1);
					strncat(str,space,1);

				}
				pop(&head);
			}
			*/
		}
		count++;
		infix++;
		display_(head);
	}
	strncat(str, space, 1);
	while (!empty_(head)) 
	{
		*temp = top_(head);
		pop_(&head);
		strncat(str,temp,1);
		strncat(str,space,1);
		printf("%s\n", str);
	}
	//free(str);
	return str;
}

int main(int argc, char* argv[]) 
{
	char* result;
	result = postfix(argv[1]);
	printf("%s\n", result);
	//free(result);
	Array_Sum(result);
	return 0;
}
