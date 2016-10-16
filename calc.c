#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 100

int num_stack[N];
int op_stack[N];
int n_top = 0;
int op_top = -1;

void n_push(int);
int n_pop();
char op_pop();
void op_push(char);
char top();
int prior(char);
int isOp(char);
void print();
int main()
{
	char input[]="-5=\0";
	char integer[N];
	int i=0;
	char op;
	int j=0;
	int operand1,operand2;
	int result=0;
	//op_stack[0] = '#';
	op_push('#');
	while(input[i]!='\0')
	{
		print();
		if(input[i] >= '0' && input[i] <= '9' )
		{
			integer[j]=input[i];
			printf("%c \n",integer[j]);
			j++;
		}
		else if(isOp(input[i]) == 1 || input[i] == '=')
		{
			integer[j] = '\0';
			n_push(atoi(integer));
			j=0;

			if(prior(input[i]) > prior(top()))
			{
				op_push(input[i]);
			}
			else
			{	
				while(prior(input[i]) <= prior(top()) )
				{
					operand2 = n_pop();
					operand1 = n_pop();
					op = op_pop();
					switch(op){
						case '+':result = operand1+operand2;
							printf("%d %c %d = %d \n",operand1,op,operand2,result);
							break;
						case '-':result = operand1-operand2;
							printf("%d %c %d = %d \n",operand1,op,operand2,result);
							break;
						case '*':result = operand1*operand2;
							printf("%d %c %d = %d \n",operand1,op,operand2,result);
							break;
						case '/':result = operand1/operand2;
							printf("%d %c %d = %d \n",operand1,op,operand2,result);
							break;
						case '%':result = operand1%operand2;
							printf("%d %c %d = %d \n",operand1,op,operand2,result);
							break;
					}
					n_push(result);
				}
				if(input[i]!='=')
					op_push(input[i]);
			}
		}
		i++;
	}
	printf("result is %d\n",n_pop());
}
void n_push(int num)
{
	if(n_top >= N-1)
	{
		printf("number stack is full\n");
		exit(-1);
	}
	else
		num_stack[++n_top] = num;
}
int n_pop()
{
	if(n_top<0)
	{
		printf("%d :num index is out of range\n",n_top);
		exit(-1);
	}
	else
		return num_stack[n_top--];
}
void op_push(char op)
{
	if(op_top>=N-1)
	{
		printf("operator stack is full\n");
		exit(-1);
	}
	op_stack[++op_top] = op;
}
char op_pop()
{
	if(op_top<0)
	{
		printf("opstack index is out of range\n");
		exit(-1);
	}
	else
		return op_stack[op_top--];
}
char top()
{
	return op_stack[op_top];
}
int prior(char op)
{
	switch(op){
		case '+':return 2;
			break;
		case '-':return 2;
			break;
		case '*':return 4;
			break;
		case '/':return 4;
			break;
		case '%':return 6;
			break;
		case '#':return 0;
			break;
		default:return 0;
			break;
	}
}
int isOp(char c)
{
	switch(c){
		case '+':return 1;
			break;
		case '-':return 1;
			break;
		case '*':return 1;
			break;
		case '/':return 1;
			break;
		case '%':return 1;
			break;
		default:return 0;
			break;
	}
}
void print()
{
	int i=0;
	printf("num stack: ");
	for(i=0;i<n_top;i++)
		printf("%d ",num_stack[i]);
	printf("\n");
	printf("opt stack: ");
	for(i=0;i<op_top;i++)
		printf("%c ",op_stack[i]);
	printf("\n");
}
