#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "str.h"
#define MAX 8000000

void space_exception()
{
    printf("공백이 포함되어 있습니다.\n");
    exit(1);
}

void exception(char *infix)
{
    int cnt = 1;
    int point_cnt = 0;    // 소수점의 개수
    int oper_cnt = 0;    // 연산자의 개수
    int ob_cnt = 0;        // 여는 괄호의 개수
    int ob_next = 0;    // 괄호 다음 문자가 숫자인지 여부를 확인
    if(*infix == '*' || *infix == '+')
    {
        printf("첫 번째 문자에 '+'나 '*'는 올 수 없습니다.\n");
        exit(1);
    }
    if(*infix == '.')
    {
        printf("첫 번째 문자에 '.'는 올 수 없습니다.\n");
        exit(1);
    }
    while(*infix != '\0')
    {
        if(!(*infix >= 48 && *infix < 58) && (*infix != '+' && *infix != '-' && *infix != '*' && *infix != '(' && *infix != ')') && *infix != '.')
        {
            printf("알 수 없는 값이 존재합니다.\n");
            exit(1);
        }
        else
        {
            if(*infix == '.')
            {
                if(oper_cnt > 0)
                {
                    printf("연산자 다음에는 소수점이 올 수 없습니다.\n");
                    exit(1);
                }
                if(*(infix + 1) == '+' || *(infix + 1) == '-' || *(infix + 1) == '*' || *(infix - 1) == '(' || *(infix - 1) == ')' || *(infix + 1) == '(' || *(infix + 1) == ')')
                {
                    printf("소수점의 앞뒤로 연산자나 괄호가 올 수 없습니다.\n");
                    exit(1);
                }
                point_cnt++;
            }
            else if(*infix == '+' || *infix == '-' || *infix == '*')
            {
                if(ob_next > 0 && (*infix == '+' || *infix == '*'))
                {
                    printf("여는 괄호 다음에는 '+'나 '*'가 올 수 없습니다.\n");
                    exit(1);
                }
                point_cnt = 0;
                oper_cnt++;
            }
            else if(*infix == '(')
            {
                point_cnt = 0;
                oper_cnt = 0;
                ob_next++;
                ob_cnt++;
            }
            else if(*infix == ')')
            {
                if(ob_next > 0)
                {
                    printf("괄호 안에 아무것도 존재하지 않습니다.\n");
                    exit(1);
                }
                if(oper_cnt > 0)
                {
                    printf("연산자 다음을 괄호로 닫을 수 없습니다.\n");
                    exit(1);
                }
                oper_cnt = 0;
                ob_cnt--;
            }
            else
            {
                ob_next = 0;
                oper_cnt = 0;
            }
        }
        if(ob_cnt < 0)
        {
            printf("부적절한 괄호가 포함되어있습니다.\n");
            exit(1);
        }
        if(oper_cnt > 1)
        {
            printf("부적절한 연산자가 포함되어있습니다.\n");
            exit(1);
        }
        if(point_cnt > 1)
        {
            printf("부적절한 소수가 포함되어있습니다.\n");
            exit(1);
        }
        infix++;
    }
    if(ob_cnt > 0)
    {
        printf("부적절한 괄호가 포함되어있습니다.\n");
        exit(1);
    }
    if(oper_cnt > 0)
    {
        printf("연산자로 끝날 수 없습니다.\n");
        exit(1);
    }
    if(*(infix - 1) == '.')
    {
        printf("소수점으로 끝날 수 없습니다.\n");
        exit(1);
    }
}

char *postfix(char *infix)
{
	char *str;
	str = (char *) malloc(2*sizeof(char)*strlen(infix)+1);
	memset(str, 0, 2*sizeof(char)*strlen(infix)+1);
	struct node* head = NULL; //stack <char> operator;
	char* temp = "";
	temp = (char *) malloc(sizeof(char));
	char* space = " ";
	int count = 1;
	int point = 0;
	while (*infix != '\0') 
	{
		if (*infix != '+' && *infix != '-' && *infix != '*' && *infix != '(' && *infix != ')')
		{
			strncat(str, infix, 1);
		}
		else 
		{
			if (count != 1 && *infix != '(' && *temp != '(')
				strncat(str, space, 1);
			if (*infix == '+' || *infix == '-') 
			{
				if (count == 1)
					strncat(str, infix, 1);
				else if (empty_(head) || top_(head) == '(')
				{
					*temp = *infix;
					push_(&head, *infix);
				}
				else if (top_(head) == '-')
				{
					*temp = pop_(&head);
					strncat(str, temp, 1);
					strncat(str, space, 1);
					push_(&head, *infix);
				}
				else if (top_(head) == '+')
				{
					*temp = *infix;
					push_(&head, *infix);
				}
				else if (top_(head) == '*')
				{
					while (top_(head) == '*' || top_(head) == '-')
					{
						*temp = pop_(&head);
						strncat(str,temp,1);
						strncat(str,space,1);
					}
					push_(&head, *infix);
				}
			}
			else if (*infix == '*')
			{
				*temp = *infix;
				push_(&head, *infix);
			}
			else
			{
				if (*infix == '(')
				{
					push_(&head, *infix);
				}
				else // ')' 일 때
				{
					while (top_(head) != '(')
					{
						*temp = pop_(&head);
						strncat(str, temp, 1);
						strncat(str, space, 1);
					}
					*temp = pop_(&head);
				}
			}
		}
		if ((*infix >= 48 && *infix < 58) && infix[1] == '(')
		{
			strcat(str, " ");
			push_(&head, '*');
			*temp = '*';
		}
		else if (*infix == ')' && (infix[1] >= 48 && infix[1] < 58))
		{
			push_(&head, '*');
			*temp = '*';
		}
		else if (*infix == ')' && infix[1] == '(')
		{
			push_(&head, '*');
			*temp = '*';
		}

		if (*infix == '(' && infix[1] == '-')
		{
			strcat(str, "-");
			infix++;
		}

		count++;
		infix++;
		display_(head);
	}
	if (*temp != '(')
		strncat(str, space, 1);
	while (!empty_(head)) 
	{
		*temp = top_(head);
		pop_(&head);
		strncat(str,temp,1);
		strncat(str,space,1);
	}
	return str;
}

long long getElapsedTime(unsigned int nFlag)
{
	const long long NANOS = 1000000000LL;
	static struct timespec startTS, endTS;
	static long long retDiff = 0;

	if (nFlag == 0) {
		retDiff = 0;
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
	}
	else {
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
		retDiff = NANOS * (endTS.tv_sec - startTS.tv_sec) + (endTS.tv_nsec - startTS.tv_nsec);
 	}

	return retDiff;
}

int main(int argc, char* argv[]) 
{
	getElapsedTime(0);
	FILE * OP = fopen(argv[1], "r");
	char result[MAX];
	char* total;
	fscanf(OP, "%s", result);
	for (; fscanf(OP, "%s", result) != EOF;)
		space_exception();
	fclose(OP);
	exception(result);
	total = postfix(result);
	Array_Sum(total);
	printf("Elapsed Time: %lld\n", getElapsedTime(1));
}
