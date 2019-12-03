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

char* Change_str(char* a)
{
	int cnt = 0;
	int point = 0;
	for (int i = 0; i < strlen(a); i++)
	{
		if (a[i] == '.')
			point = 1;
		if ((a[i] == '+' || a[i] == '-') && i != 0)
		{
			if (point == 1)
				point = 0;
			else
				cnt++;
		}
	}
	char* temp = (char*)malloc(strlen(a)+cnt+1);
	point = 0;
	for (int i = 0, s = 0; i <= strlen(a); i++, s++)
	{
		if (a[i] == '.')
			point = 1;
		if ((a[i] == '+' || a[i] == '-') || a[i] == '\0')
		{
			if (point == 0)
			{
				if (i != 0)
				{
					temp[s] = '.';
					s++;
				}
			}
			else
				point = 0;
		}	
		temp[s] = a[i];
	}
	
	temp[strlen(a)+cnt+1] = '\0';
	return temp;
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
		temp[i] = '\0';
	if (temp[i] == '.')
		temp[i] = '\0';
	return temp;
}

void Array_Sum(char* Num)
{
	char* temp;
	char oper; // 연산자 저장 변수
	char* total;
	char sign; // 부호 변수
	char* first_Num;
	//char* Num = Change_str(a);
	string_node* head = NULL;
	if (Num[0] == '-')
	{
		sign = '-';
		Num++;
	}
	else
		sign = '+';
	int first_count = Operator_Count(Num);
	first_Num = (char*)malloc(first_count+1);
    strncpy(first_Num, Num, first_count);
	first_Num[first_count] = '\0';
	Num += first_count;
	while (1)
	{
		/*
		int first_count = Operator_Count(Num);
		first_Num = (char*)malloc(first_count + 1);
		strncpy(first_Num, Num, first_count);
		first_Num[first_count] = '\0';
		*/
		if (first_Num[0] == '+' || first_Num[0] == '-' || first_Num[0] == '*')
		{
			//printf("%s\n", head->data);
			total = calc((head->next)->data, head->data, first_Num[0]);
			pop(&head);
			pop(&head);
			push(&head, total);
		}
		else
			push(&head, first_Num);

		if (*Num == '\0')
			break;
		else
			Num++;
		//Num += first_count;
		int first_count = Operator_Count(Num);
		first_Num = (char*)malloc(first_count+1);
		strncpy(first_Num, Num, first_count);
		Num += first_count;
		first_Num[first_count] = '\0';
		//free(first_Num);
	}

	display(head);
	/*
	Num += first_count;
	oper = *Num;
	Num++;

	int second_count = Operator_Count(Num);
	char* second_Num = (char*)malloc(second_count + 1);
	strncpy(second_Num, Num, second_count);
	second_Num[second_count] = '\0';
	Num += second_count;

	while (1)
	{
		int first_point = Find_Point(first_Num);
		int second_point = Find_Point(second_Num);
		int first_integer = first_count - (first_count - first_point);
		int second_integer = second_count - (second_count - second_point);
		int max_integer = (first_count - (first_count - first_point)) > (second_count - (second_count - second_point)) ? first_count - (first_count - first_point) : second_count - (second_count - second_point);
		int max_point = first_point > second_point ? first_point : second_point;
		int max_point_num = first_count - first_point - 1 > second_count - second_point - 1 ? first_count - first_point - 1 : second_count - second_point - 1;
		temp = (char*)malloc(max_integer + max_point + 2);

		temp[max_point] = '.';
		if (oper == '+')
		{
			if (sign == '+')
			{
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
			}
			else // - +
			{
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
					sign = '+';
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
					sign = '-';
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
                        sign = '+';
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
                        sign = '-';
					}
				}
			}
		}
		else // ? -
		{
			if (sign == '-')
			{
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
			}
			else
			{
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
                    sign = '-';
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
                    sign = '+';
				}
				else // + -
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
                    	sign = '-';
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
                    	sign = '+';
					}
				}
			}
		}
		temp[max_integer + max_point_num + 1] = '\0';
		free(first_Num);
		free(second_Num);
		total = Round(temp, max_point);
		free(temp);
		first_Num = (char*)malloc(strlen(total) + 1);
		strcpy(first_Num, total);
		free(total);
		if (*Num == '\0')
		{
			total = Clear(first_Num);
			if (sign == '-')
			{
				if (*total != '0')
					printf("%c%s\n", sign, total);
				else
					printf("%s\n", total);
			}
			else
				printf("%s\n", total);
			break;
		}
		else
		{
			oper = *Num;
			Num += 1;
		}
		first_Num[strlen(first_Num)] = '\0';
		first_count = strlen(first_Num);
		second_count = Operator_Count(Num);
		second_Num = (char*)malloc(second_count + 1);
		strncpy(second_Num, Num, second_count);
		second_Num[second_count] = '\0';
		Num += second_count;
	}
	*/
}


int main(int argc, char* argv[])
{
	Array_Sum(argv[1]);
	return 0;
}

