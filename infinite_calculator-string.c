#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"
int Operator_Count(char* ary)
{
	int index;
	for (index = 0; ((ary[index] != ' ') && (ary[index] != 0)); index++)
		;
	return index;
}

int Find_Point(char* ary)
{
	int i = 0;
	for (i = 0; ary[i] != '.'; i++)
		;
	return i;
}

char* Round(char* ary, int max_point)
{
	char* temp = (char*)malloc(strlen(ary) + 1);
	strcpy(temp, ary);
	for (int i = strlen(temp) - 1; i > 0; i--)
	{
		if (temp[i] == '.' && i == max_point)
			continue;

		if(temp[i] >= 58)
		{
			if (temp[i - 1] == '.' && i - 1 == max_point)
			{
				while (temp[i] >= 58)
				{
					temp[i] -= 10;
					temp[i - 2]++;
				}
			}
			else
			{
				while (temp[i] >= 58)
				{
					temp[i] -= 10;
					temp[i - 1]++;
				}
			}
		}
		else if (temp[i] <= 47)
		{
			if (temp[i - 1] == '.' && i - 1 == max_point)
			{
				while (temp[i] <= 47)
				{
					temp[i] += 10;
					temp[i - 2]--;
				}
			}
			else
			{
				while (temp[i] <= 47)
				{
					temp[i] += 10;
					temp[i - 1]--;
				}
			}
		}
	}
	if (temp[0] >= 58)
	{
		char* temp2 = (char*)malloc(strlen(temp) + 2);
		temp2[0] = '0';
		for (int i = 0; i < strlen(temp); i++)
			temp2[i + 1] = temp[i];
		while (temp2[1] >= 58)
		{
			temp2[1] -= 10;
			temp2[0]++;
		}
		temp2[strlen(temp)+1] = '\0';
		return temp2;
	}
	else if (temp[0] <= 48)
	{
		int cnt = 0;
		for (int i = 0; ; i++)
		{
			if (temp[i+1] == '.' || temp[i+1] == '\0')
				break;
			if (temp[i] != '0')
				break;
			cnt++;
		}
		char * temp2 = (char*)malloc(strlen(temp)+1-cnt);
		for (int i = 0; i < strlen(temp)-cnt; i++)
			temp2[i] = temp[i+cnt];
		temp2[strlen(temp)-cnt] = '\0';
		return temp2;
	}
	else
		return temp;
}

char* Clear(char* a)
{
	char* temp = (char*)malloc(strlen(a)+1);
	strcpy(temp, a);
	int i;
	for (i = strlen(temp) - 1; temp[i] == '0'; i--)
	{
		if (temp[i-1] == '.')
			break;
		temp[i] = '\0';
	}
	return temp;
}

void Array_Sum(char* Num)
{
	FILE* CP = fopen("result", "w");
	char* temp;
	char oper; // 연산자 저장 변수
	char* total;
	char sign; // 부호 변수
	char* first_Num;
	string_node* head = NULL;
	int first_count = Operator_Count(Num);
	first_Num = (char*)malloc(first_count+1);
    strncpy(first_Num, Num, first_count);
	first_Num[first_count] = '\0';
	Num += first_count;
	while (1)
	{
		if (first_Num[0] == '+' || first_Num[0] == '-' || first_Num[0] == '*')
		{
			if (first_Num[1] != '\0')
				push(&head, first_Num);
			else
			{
				total = calc((head->next)->data, head->data, first_Num[0]);
				pop(&head);
				pop(&head);
				push(&head, total);
			}
		}
		else
		{
			push(&head, first_Num);
		}

		if (Num[1] == '\0')
			break;
		else
			Num++;
		int first_count = Operator_Count(Num);
		first_Num = (char*)malloc(first_count+1);
		strncpy(first_Num, Num, first_count);
		Num += first_count;
		first_Num[first_count] = '\0';
	}
	
	total = pop(&head);
	if (total[0] == '-' && total[1] == '0' && total[strlen(total)-1] == '.')
	{
		total++;
		temp = (char*)malloc(strlen(total)+2);
		strcpy(temp, total);
		strcat(temp, "0");
		
	}
	else if (total[strlen(total)-1] == '.')
	{
		temp = (char*)malloc(strlen(total)+2);
		strcpy(temp, total);
		strcat(temp, "0");
	}
	else if (total[0] == '-' && total[1] == '0' && total[2] == '.' && total[3] == '0')
	{
		total++;
		temp = (char*)malloc(strlen(total)+2);
		strcpy(temp, total);
	}
	else
	{
		temp = (char*)malloc(strlen(total)+2);
		strcpy(temp, total);
	}
	printf("%s\n", temp);
	fprintf(CP, "%s", temp);
	fprintf(CP, "%s", "\n"); 
	fclose(CP);
}
