#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

char* temp_Round(char* ary, int max_point)
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
	}
	return temp;
}

int find_point(char* Num)
{
	int point = 0;
	for(int i = 0; i < strlen(Num); i++)
	{
		if (Num[i] == '.')
		{
			point = 1;
			break;
		}
	}
	return point;
}

char* calc(char * first_Num, char* second_Num,  char oper)
{
	char* total;
	char* temp;
	char first_sign = '+';
	char second_sign = '+';
	int first_point = 0;
	int second_point = 0;
	first_point = find_point(first_Num);
	second_point = find_point(second_Num);
	if (first_point != 1)
	{
		temp = (char*)malloc(strlen(first_Num)+2);
		strcat(temp, first_Num);
		strcat(temp, ".\0");
		free(first_Num);
		first_Num = (char*)malloc(strlen(temp)+1);
		strcpy(first_Num, temp);
		free(temp);
	}
	if (second_point != 1)
	{
		temp = (char*)malloc(strlen(second_Num)+2);
        strcat(temp, second_Num);
        strcat(temp, ".\0");
		free(second_Num);
		second_Num = (char*)malloc(strlen(temp)+1);
        strcpy(second_Num, temp);
 		free(temp);
	}
	printf("%s\n%s\n", first_Num, second_Num);
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
	printf("%s\n", temp);
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
		for (int s = strlen(second_Num)-1; s > second_point; s--)
		{	
			num = (first_Num[i]-48) * (second_Num[s]-48);
			if (temp[i+s+cnt-main_cnt] == '.')
				main_cnt++;
			printf("i : %d, s : %d, num : %d, main_cnt : %d, index : %d\n", i, s, num, main_cnt, i+s+cnt-main_cnt);
			temp[i+s+cnt-main_cnt] += num%10;
			if (temp[i+s+cnt-main_cnt-1] == '.')
				temp[i+s+cnt-main_cnt-2] += num/10;
			else
				temp[i+s+cnt-main_cnt-1] += num/10;
		}

		if (i+(strlen(second_Num)-1)+cnt > first_point+second_point)
            main_cnt = 0;
		temp = temp_Round(temp, first_point+second_point);
		printf("%s\n", temp);
		//cnt = 0;
		//main_cnt = 0;
	}
	printf("정수 부분\n");
	main_cnt = 0;
	cnt = 1;
	int gap = (first_integer > second_integer) ? first_integer-second_integer : second_integer-first_integer;
	for (int i = strlen(first_Num)-1; i > -1; i--)
    {
        if (first_Num[i] == '.')
        {
            cnt++;
            continue;
        }
        for (int s = second_point-1; s > -1; s--)
        {
            num = (first_Num[i]-48) * (second_Num[s]-48);
            if (temp[i+s+cnt-main_cnt] == '.' && main_cnt == 0)
                main_cnt++;

            printf("i : %d, s : %d, num : %d, main_cnt : %d, index : %d\n", i, s, num, main_cnt, i+s+cnt-main_cnt);
			if (temp[i+s+cnt-main_cnt] == '.')
				temp[i+s+cnt-main_cnt-1] += num%10;
			else
            	temp[i+s+cnt-main_cnt] += num%10;
            if (temp[i+s+cnt-main_cnt-1] == '.')
                temp[i+s+cnt-main_cnt-2] += num/10;
            else
                temp[i+s+cnt-main_cnt-1] += num/10;
        }
		if (i > first_point)
			main_cnt = 0;
		temp = temp_Round(temp, first_point+second_point);
		printf("%s\n", temp);
        //cnt = 0;
        //main_cnt = 0;
    }

	printf("%s\n", temp);
	
	// 미완
	if (first_sign != second_sign)
    {
        total = Round(temp, first_integer+second_integer);
        char* temp2 = (char*)malloc(strlen(total)+2);
        temp2[0] = '-';
        strcat(temp2, total);
        free(temp);
        total = Clear(temp2);
        //total = Round(temp2, max_point+1);
    }
    else
        total = Clear(Round(temp, first_integer+second_integer));

    return total;
}
