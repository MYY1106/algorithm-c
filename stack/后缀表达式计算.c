#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct NumNode
{
    int val;
    struct NumNode *prev;
    struct NumNode *next;
} NumNode; // ˫������

typedef struct NumStack
{
    NumNode *front;
    NumNode *rear;
} NumStack;

void func(NumStack *stack, char *str);
void pushNumStack(NumStack *stack, int num);
NumNode *numNodeInit(int num);
void popNumStack(NumStack *stack);
NumStack *createNumStack();
int isNum(char *str);
int evalRPN(char **tokens, int tokensSize);

int main(void)
{
    char *token[] = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    printf("%d", evalRPN(token, 13));
}

int evalRPN(char **tokens, int tokensSize)
{
    NumStack *numStack = createNumStack();

    for (int i = 0; i < tokensSize; i++)
    {
        func(numStack, tokens[i]);
    }

    return numStack->rear->val;
}

void func(NumStack *stack, char *str)
{
    int res;
    if (isNum(str) || (str[0] == '-' && strlen(str) != 1))
    {
        pushNumStack(stack, atoi(str));
    }
    else
    {
        int a = stack->rear->val;
        popNumStack(stack);
        int b = stack->rear->val;
        popNumStack(stack);
        switch (str[0])
        {
        case '+':
            res = a + b;
            break;
        case '-':
            res = b - a;
            break;
        case '*':
            res = a * b;
            break;
        case '/':
            res = b / a;
            break;
        }
        pushNumStack(stack, res);
    }
}

// ��������ջ
// ����ֵ��ջ��ָ��
NumStack *createNumStack()
{
    NumStack *stack = (NumStack *)malloc(sizeof(NumStack));
    stack->front = NULL;
    stack->rear = NULL;
    return stack;
}

// ��ʼ���ڵ�
// num������
NumNode *numNodeInit(int num)
{
    NumNode *node = (NumNode *)malloc(sizeof(NumNode));
    node->val = num;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// ��ջ
// stack��ջ��ָ��
// num������
void pushNumStack(NumStack *stack, int num)
{
    NumNode *node = numNodeInit(num);
    if (stack->front == NULL)
    {
        stack->front = node;
        stack->rear = node;
    }
    else
    {
        stack->rear->next = node;
        node->prev = stack->rear;
        stack->rear = node;
    }
    // showStack(stack);
}

// ��ջ
// stack��ջ��ָ��
void popNumStack(NumStack *stack)
{
    NumNode *node = stack->rear;
    if (node->prev == NULL) //ֻʣ��һ��Ԫ��
    {
        stack->front = NULL;
        stack->rear = NULL;
    }
    else
    {
        stack->rear = node->prev;
        node->prev->next = NULL;
    }
    free(node);
}

int isNum(char *str)
{
    int len = strlen(str), i = 0;

    for (i = 0; i < len; i++)
    {
        if (!(isdigit(str[i])))
            return 0;
    }
    return 1;
}