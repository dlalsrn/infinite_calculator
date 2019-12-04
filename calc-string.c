#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"
char* calc(char * first_Num, char* second_Num,  char oper)
{
	char* total;
	char first_sign = '+';
	char second_sign = '+';
	if (first_Num[0] == '-')
	{
		first_sign = '-';
		first_Num++;
	}
	if (second_Num[0] == '-')
	{
		second_sign = '-';
		second_Num++;
	}

	if (first_sign == '+')
	{
		if (oper == second_sign)
			total = add(first_Num, second_Num, first_sign);
		else
			total = minus(first_Num, second_Num, first_sign);
	}
	else if (first_sign == '-')
	{
		if (oper == second_sign)
			total = minus(first_Num, second_Num, first_sign);
		else
			total = add(first_Num, second_Num, first_sign);
	}
	/*
		else
			total = minus(first_Num, second_Num, sign);
	}
	else if (oper == '-')
	{
		if (sign == '+')
			total = minus(first_Num, second_Num, sign);
		else
			total = add(first_Num, second_Num, sign);
	}
	else if (oper == '*')
		total = multiply(first_Num, second_Num, sign);
	*/
	return total;
}

char* add(char* first_Num, char* second_Num, char first_sign)
{
	char* total;
	char* temp;
	int first_count = strlen(first_Num);
	int second_count = strlen(second_Num);
	int first_point = Find_Point(first_Num);
	int second_point = Find_Point(second_Num);
	int first_integer = first_count - (first_count - first_point);
	int second_integer = second_count - (second_count - second_point);
	int max_integer = (first_count - (first_count - first_point)) > (second_count - (second_count - second_point)) ? first_count - (first_count - first_point) : second_count - (second_count - second_point);
	int max_point = first_point > second_point ? first_point : second_point;
	int max_point_num = first_count - first_point - 1 > second_count - second_point - 1 ? first_count - first_point - 1 : second_count - second_point - 1;
	temp = (char*)malloc(max_integer + max_point + 2);
	temp[max_point] = '.';
	
	for (int i = 1; max_point - i > -1; i++)
	{
		if ((first_point - i > -1) && (second_point - i > -1))
			temp[max_point - i] = first_Num[first_point - i] + (second_Num[second_point - i] - 48);
		else if (first_point - i > -1)
			temp[max_point - i] = first_Num[first_point - i];
		else if (second_point - i > -1)
			temp[max_point - i] = second_Num[second_point - i];
	}
	for (int i = 0; i < max_point_num; i++)
	{
		if ((first_point + i + 1 < first_count) && (second_point + i + 1 < second_count))
			temp[max_point + i + 1] = first_Num[first_point + i + 1] + (second_Num[second_point + i + 1] - 48);
		else if (first_point + i + 1 < first_count)
			temp[max_point + i + 1] = first_Num[first_point + i + 1];
		else if (second_point + i + 1 < second_count)
			temp[max_point + i + 1] = second_Num[second_point + i + 1];
	}
	temp[max_integer + max_point_num + 1] = '\0';
	if (first_sign == '-')
	{
		total = Round(temp, max_point);
		char* temp2 = (char*)malloc(strlen(total)+2);
		temp2[0] = '-';
		strcat(temp2, total);
		free(temp);
		total = temp2;
		//total = Round(temp2, max_point+1);
	}
	else
		total = Round(temp, max_point);

	return total;
}

char* minus(char* first_Num, char* second_Num, char first_sign)
{
	
}

char* multiply(char* first_Num, char* second_Num, char sign)
{

}
