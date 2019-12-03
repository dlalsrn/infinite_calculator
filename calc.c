#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef	char	DATA;

struct linked_list {
	DATA				d;
	struct linked_list	*next;
};

typedef	struct linked_list	ELEMENT;
typedef	ELEMENT				*LINK;


LINK add(LINK a,LINK b);
LINK minus(LINK a,LINK b);
LINK multiply(LINK a,LINK b);
LINK calc(char * str);
LINK string_to_list(char s[])
{
	LINK head;

	if (s[0] == '\0')	/* base case */
		return NULL;
	else {
		head = malloc(sizeof(ELEMENT));
		head->d = s[0];
		head->next = string_to_list(s + 1);
		return head;
	}
}

void print_list(LINK head)
{
	if (head == NULL)
		printf("NULL");
	else {
		printf("%c --> ", head->d);
		print_list(head->next);
	}
}

LINK calc(char * str)
{
	char * address = str;
	int operand1 = 0;
	int operand2 = 0;
	char operator;
	while (*str != '\0') 
	{
		if (*str == '+' || *str == '-' || *str == '*')
		{
			operator = *str;
			while(operand1 == 1 && operand2 == 1)
			{
				str--;
				if (isspace(
				
				

		str++;
	}
}
// 123 456 + 324 -
int main(void) {
	LINK a;
	a = string_to_list("123456 689789 +");
	print_list(a);
	return 0;
}
