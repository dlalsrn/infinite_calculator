#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
int Operator_Count(char* ary)
{
	int index;
	for (index = 0; (((ary[index] != '+') && (ary[index] != '-')) && (ary[index] != 0)); index++)
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
			if (temp[i - 1] == '.')
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
			if (temp[i - 1] == '.')
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
		char * temp2 = (char*)malloc(strlen(temp));
		for (int i = 0; i < strlen(temp)-1; i++)
			temp2[i] = temp[i+1];
		temp2[strlen(temp)-1] = '\0';
		return temp2;
	}
	else
		return temp;
}
void Array_Sum(char* a)
{
	char* temp;
	char oper;
	char* total;
	int count = strlen(a);
	char* Num = (char*)malloc(count + 1);
	strcpy(Num, a);
	
	int first_count = Operator_Count(Num);
	char* first_Num = (char*)malloc(first_count + 1);
	strncpy(first_Num, Num, first_count);
	first_Num[first_count] = '\0';
	Num += first_count;
	oper = *Num;
	Num++;

	int second_count = Operator_Count(Num);
	char* second_Num = (char*)malloc(second_count + 1);
	strncpy(second_Num, Num, second_count);
	second_Num[second_count] = '\0';

	Num += second_count;
	//printf("%s\n%s\n", first_Num, second_Num);
	//int cnt = 0;
	while (1)
	{
		int first_point = Find_Point(first_Num);
		int second_point = Find_Point(second_Num);
		//printf("%d %d\n", first_point, second_point);

		//int first_temp = first_point, second_temp = second_point;

		int first_integer = first_count - (first_count - first_point);
		int second_integer = second_count - (second_count - second_point);
		int max_integer = (first_count - (first_count - first_point)) > (second_count - (second_count - second_point)) ? first_count - (first_count - first_point) : second_count - (second_count - second_point);
		int max_point = first_point > second_point ? first_point : second_point;
		int max_point_num = first_count - first_point - 1 > second_count - second_point - 1 ? first_count - first_point - 1 : second_count - second_point - 1;
		//printf("%d %d\n", max_integer, max_point_num);
		temp = (char*)malloc(max_integer + max_point + 2);

		temp[max_point] = '.';
		//printf("시작\n");
		if (oper == '+')
		{
			for (int i = 1; max_point - i > -1; i++)
			{
				if ((first_point - i > -1) && (second_point - i > -1))
					temp[max_point - i] = first_Num[first_point - i] + (second_Num[second_point - i] - 48);
				else if (first_point - i > -1)
					temp[max_point - i] = first_Num[first_point - i];
				else if (second_point - i > -1)
					temp[max_point - i] = second_Num[second_point - i];
				//printf("%c\n", temp[max_point - i]);
			}
			for (int i = 0; i < max_point_num; i++)
			{
				if ((first_point + i + 1 < first_count) && (second_point + i + 1 < second_count))
					temp[max_point + i + 1] = first_Num[first_point + i + 1] + (second_Num[second_point + i + 1] - 48);
				else if (first_point + i + 1 < first_count)
					temp[max_point + i + 1] = first_Num[first_point + i + 1];
				else if (second_point + i + 1 < second_count)
					temp[max_point + i + 1] = second_Num[second_point + i + 1];
				//printf("%c\n", temp[max_point + i + 1]);
			}
		}
		else
		{
			for (int i = 1; max_point - i > -1; i++)
            {   
                if ((first_point - i > -1) && (second_point - i > -1))
                    temp[max_point - i] = first_Num[first_point - i] - (second_Num[second_point - i] - 48); 
                else if (first_point - i > -1) 
                    temp[max_point - i] = first_Num[first_point - i]; 
                //else if (second_point - i > -1) 
				//{
                   // temp[max_point - i] = 58 - (second_Num[second_point - i]-48); 
                //printf("%c\n", temp[max_point - i]);
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
						temp[max_point + i]--;
					}
				}
                //printf("%c\n", temp[max_point + i + 1]);
            } 
		}
		temp[max_integer + max_point_num + 1] = '\0';
		free(first_Num);
		free(second_Num);
		total = Round(temp, max_point);
		free(temp);
		//printf("%s\n", total);
		first_Num = (char*)malloc(strlen(total) + 1);
		strcpy(first_Num, total);
		if (*Num == '\0')
		{
			printf("%s\n", first_Num);
			break;
		}
		else
		{
			oper = *Num;
			Num += 1;
		}
		//printf("%s\n", Num);
		//if (Num == NULL)
			//break;
		first_Num[strlen(first_Num)] = '\0';
		//printf("%s\n", first_Num);
		//free(temp);
		first_count = strlen(first_Num);
		second_count = Operator_Count(Num);
		//Num += second_count;
		second_Num = (char*)malloc(second_count + 1);
		//printf("%d %d\n", first_count, second_count);
		strcpy(second_Num, Num);
		//strncpy(second_Num, Num, second_count);

		Num += second_count;
		//printf("%s\n%s\n", first_Num, second_Num);
	}
	//printf("%s\n", first_Num);
	//char* total = Round(first_Num);
	//printf("%s\n", total);
}

int main(int argc, char* argv[])
{
	Array_Sum(argv[1]);
	return 0;
}
