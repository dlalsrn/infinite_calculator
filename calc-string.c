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
	
	if (oper == '*')
		total = multiply(first_Num, second_Num, first_sign, second_sign);
	else if (first_sign == '+')
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
		//total = temp2;
		total = Clear(temp2);
	}
	else
		total = Clear(Round(temp, max_point));

	return total;
}

char* minus(char* first_Num, char* second_Num, char first_sign)
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

	if (second_integer > first_integer)
	{
		for (int i = 1; max_point - i > -1; i++)
        {   
            if ((first_point - i > -1) && (second_point - i > -1))
            	temp[max_point - i] = second_Num[second_point - i] - (first_Num[first_point - i] - 48); 
            else if (second_point - i > -1) 
                temp[max_point - i] = second_Num[second_point - i]; 
        }   
        for (int i = 0; i < max_point_num; i++)
        {   	
        	if ((first_point + i + 1 < first_count) && (second_point + i + 1 < second_count))
                temp[max_point + i + 1] = second_Num[second_point + i + 1] - (first_Num[first_point + i + 1] - 48); 
            else if (second_point + i + 1 < second_count)
                temp[max_point + i + 1] = second_Num[second_point + i + 1]; 
            else if (first_point + i + 1 < first_count)
			{
				if (first_Num[first_point + i + 1] == '0')
					temp[max_point + i + 1] = '0';
				else
				{
                    temp[max_point + i + 1] = 58 - (first_Num[first_point + i + 1]-48);
					if (temp[max_point + i] == '.')
                        temp[max_point + i -1]--;
                    else
                        temp[max_point + i]--;
				}
			}
        }
		if (first_sign == '+')
			first_sign = '-';
		else
			first_sign = '+';
	}
	else if (first_integer > second_integer)
	{
		for (int i = 1; max_point - i > -1; i++)
        {
            if ((first_point - i > -1) && (second_point - i > -1))
                temp[max_point - i] = first_Num[first_point - i] - (second_Num[second_point - i] - 48); 
            else if (first_point - i > -1) 
            	temp[max_point - i] = first_Num[first_point - i]; 
        }
        for (int i = 0; i < max_point_num; i++)
        {    
            if ((first_point + i + 1 < first_count) && (second_point + i + 1 < second_count))
                temp[max_point + i + 1] = first_Num[first_point + i + 1] - (second_Num[second_point + i + 1] - 48); 
            else if (first_point + i + 1 < first_count)
                temp[max_point + i + 1] = first_Num[first_point + i + 1]; 
            else if (second_point + i + 1 < second_count)
            {
                if (second_Num[second_point + i + 1] == '0')
                    temp[max_point + i + 1] = '0';
                else
                {
                    temp[max_point + i + 1] = 58 - (second_Num[second_point + i + 1]-48);
                    if (temp[max_point + i] == '.')
                        temp[max_point + i -1]--;
                    else
                        temp[max_point + i]--;
                }
            }
        }
	}
	else // - +
	{
		if (strcmp(first_Num, second_Num) <= 0)
        {

            for (int i = 1; max_point - i > -1; i++)
            {
				if ((first_point - i > -1) && (second_point - i > -1))
                	temp[max_point - i] = second_Num[second_point - i] - (first_Num[first_point - i] - 48);
                else if (second_point - i > -1)
                    temp[max_point - i] = second_Num[second_point - i];
            }
            for (int i = 0; i < max_point_num; i++)
            {
                if ((first_point + i + 1 < first_count) && (second_point + i + 1 < second_count))
                    temp[max_point + i + 1] = second_Num[second_point + i + 1] - (first_Num[first_point + i + 1] - 48);
                else if (second_point + i + 1 < second_count)
                    temp[max_point + i + 1] = second_Num[second_point + i + 1];
                else if (first_point + i + 1 < first_count)
                {
                    if (first_Num[first_point + i + 1] == '0')
                        temp[max_point + i + 1] = '0';
                    else
                    {
                        temp[max_point + i + 1] = 58 - (first_Num[first_point + i + 1]-48);
                        if (temp[max_point + i] == '.')
                            temp[max_point + i -1]--;
                        else
                            temp[max_point + i]--;
                    }
                }
            }
			if (first_sign == '+')
				first_sign = '-';
			else
				first_sign = '+';
        }
		else
		{
			for (int i = 1; max_point - i > -1; i++)
            {
            	if ((first_point - i > -1) && (second_point - i > -1))
                	temp[max_point - i] = first_Num[first_point - i] - (second_Num[second_point - i] - 48);
                else if (first_point - i > -1)
                    temp[max_point - i] = first_Num[first_point - i];
            }
            for (int i = 0; i < max_point_num; i++)
            {
                if ((first_point + i + 1 < first_count) && (second_point + i + 1 < second_count))
                    temp[max_point + i + 1] = first_Num[first_point + i + 1] - (second_Num[second_point + i + 1] - 48);
                else if (first_point + i + 1 < first_count)
                    temp[max_point + i + 1] = first_Num[first_point + i + 1];
                else if (second_point + i + 1 < second_count)
                {
                    if (second_Num[second_point + i + 1] == '0')
                        temp[max_point + i + 1] = '0';
                    else
                    {
                        temp[max_point + i + 1] = 58 - (second_Num[second_point + i + 1]-48);
                        if (temp[max_point + i] == '.')
                        	temp[max_point + i -1]--;
                        else
                            temp[max_point + i]--;
                    }
                }
            }
		}
	}
	temp[max_integer + max_point_num + 1] = '\0';
    if (first_sign == '-')
    {
        total = Round(temp, max_point);
        char* temp2 = (char*)malloc(strlen(total)+2);
        temp2[0] = '-';
        strcat(temp2, total);
        free(temp);
		//total = temp2;
        total = Clear(temp2);
        //total = Round(temp2, max_point+1);
    }
    else
        total = Clear(Round(temp, max_point));

    return total;
}

char* multiply(char* first_Num, char* second_Num, char first_sign, char second_sign)
{
	char* total;
    char* temp;
    int first_count = strlen(first_Num);
    int second_count = strlen(second_Num);
    int first_point = Find_Point(first_Num);
    int second_point = Find_Point(second_Num);
	int max_integer = (first_count - (first_count - first_point)) > (second_count - (second_count - second_point)) ? first_count - (first_count - first_point) : second_count - (second_count - second_point);
    int max_point = first_point > second_point ? first_point : second_point;
    int max_point_num = first_count - first_point - 1 > second_count - second_point - 1 ? first_count - first_point - 1 : second_count - second_point - 1;

    int first_integer = first_count - (first_count - first_point);
    int second_integer = second_count - (second_count - second_point);
	/*
    int max_integer = (first_count - (first_count - first_point)) > (second_count - (second_count - second_point)) ? first_count - (first_count - first_point) : second_count - (second_count - second_point);
    int max_point = first_point > second_point ? first_point : second_point;
    int max_point_num = first_count - first_point - 1 > second_count - second_point - 1 ? first_count - first_point - 1 : second_count - second_point - 1;
*/
	temp = (char*)malloc(first_integer+second_integer+(first_count-first_point-1)+(second_count-second_point-1)+2);
	//temp[first_integer+second_integer+(first_count-first_point-1)+(second_count-second_point-1)+1] = '\0';
	for(int i = 0; i < first_integer+second_integer+(first_count-first_point-1)+(second_count-second_point-1)+1; i++)
		temp[i] = '0';
	temp[first_integer+second_integer] = '.';
	int num;
	int cnt = 0;
	int main_cnt = 0;
	for (int i = strlen(first_Num)-1; i > -1; i--)
	{
		if (first_Num[i] == '.')
		{
			cnt++;
			continue;
		}
		for (int s = strlen(second_Num)-1; s > -1; s--)
		{	
			if (second_Num[s] == '.')
			{
				cnt++;
				continue;
			}
			num = (first_Num[i]-48) * (second_Num[s]-48);
			printf("%d\n", num);
			if (temp[i+s+cnt-main_cnt] == '.')
				main_cnt++;
			temp[i+s+cnt-main_cnt] += num%10;
			if (temp[i+s+cnt-main_cnt-1] == '.')
				temp[i+s+cnt-main_cnt-2] += num/10;
			else
				temp[i+s+cnt-main_cnt-1] += num/10;
		}
		printf("%s\n", temp);
		cnt = 0;
		main_cnt = 0;
	}

	printf("%s\n", temp);
	if (first_sign != second_sign)
    {
        total = Round(temp, first_integer+second_integer);
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
