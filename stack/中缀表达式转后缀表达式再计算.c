#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct node
{
    char val;
    struct node *prev;
    struct node *next;
} Node; // ˫������

typedef struct stack
{
    Node *front;
    Node *rear;
} Stack;

typedef struct NumNode
{
    float val;
    struct NumNode *prev;
    struct NumNode *next;
} NumNode; // ˫������

typedef struct NumStack
{
    NumNode *front;
    NumNode *rear;
} NumStack;

char *infixToSuffix();
Stack *createStack();
Node *nodeInit(char symbol);
void pushStack(Stack *stack, char symbol);
void showStack(Stack *stack);
void popStack(Stack *stack);
int isPrior(Stack *stack);
int getLevel(char symbol);
int getPrior(char symbol, Stack *stack);
int isStackEmpty(Stack *stack);
float calSuffix(char *suffix);
NumStack *createNumStack();
int isNum(char *str);
void calculate(NumStack *stack, char *str);
void pushNumStack(NumStack *stack, float num);
NumNode *numNodeInit(float num);
void popNumStack(NumStack *stack);

int main(void)
{
    char str[MAX_SIZE];
    char suffix[MAX_SIZE] = ""; // ��ź�׺���ʽ
    printf("��������׺���ʽ��֧�ֶ�λ�����磺1+2*4+9*(6*9+2)/5 �� 17+20*4+9*(64*9+2)/5����\n");
    gets(str); // ��ѻ��з������ˣ����Բ��ùܻ��з�������
    infixToSuffix(str, suffix);
    calSuffix(suffix);
    return 0;
}

float calSuffix(char *suffix)
{
    puts(suffix);
    NumStack *numStack = createNumStack();
    char *token;

    /* ��ȡ��һ�����ַ��� */
    token = strtok(suffix, " ");

    /* ������ȡ���������ַ��� */
    while (token != NULL)
    {
        calculate(numStack, token); // ִ���жϲ���
        token = strtok(NULL, " ");  // strtok()ʹ��static���������һ�δ��ָ��ַ����ĵ�ַ,������strΪNULLʱʹ�øõ�ַ�����ָ�,������strtok()������ͨ��static�������һ��strtok()������
    }
    float res = numStack->rear->val; // �õ����ļ�����
    popNumStack(numStack);
    printf("result=%f", res);
    return 0;
}

void calculate(NumStack *stack, char *str)
{
    float res;
    if (isNum(str)) // ���������
    {
        pushNumStack(stack, atoi(str)); // ��ջ
    }
    else // �����ַ�
    {
        float a = stack->rear->val; // ջ���ĵ�һ��Ԫ��
        popNumStack(stack);
        float b = stack->rear->val; // ջ���ĵڶ���Ԫ��
        popNumStack(stack);
        switch (str[0]) // ����
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
        pushNumStack(stack, res); // ������������ջ��
    }
}

char *infixToSuffix(char *infix, char *suffix)
{
    Stack *stack = createStack();
    int pos = 0; // ����ָ��suffix�������±�
    for (int i = 0; i < strlen(infix); i++)
    {
        if (isdigit(infix[i]) || infix[i] == '.') // �������������ֻ���С���㣬ֱ�����
        {
            suffix[pos++] = infix[i];
        }
        else
        {
            suffix[pos++] = ' ';
            if (!isStackEmpty(stack)) // ��ջ�ǿ�
            {
                switch (getPrior(infix[i], stack))
                {
                case 2: // ������������������ʱ
                    while (stack->rear->val != '(')
                    {
                        suffix[pos++] = stack->rear->val;
                        popStack(stack);
                        suffix[pos++] = ' ';
                    }
                    popStack(stack);
                    break;
                case 1: // �����������ַ����ȼ�����ջ��Ԫ��ʱ
                    pushStack(stack, infix[i]);
                    break;
                case 0:                                                            // �����������ַ����ȼ�С�ڻ����ջ��Ԫ��ʱ
                    while (!isStackEmpty(stack) && getPrior(infix[i], stack) == 0) // ��ջ�����ȼ����ڻ��ߵ����ַ��ĵ���
                    {
                        suffix[pos++] = stack->rear->val;
                        popStack(stack);
                        suffix[pos++] = ' ';
                    }
                    pushStack(stack, infix[i]); // ���ַ�����ջ��
                    break;
                }
            }
            else
            {
                pushStack(stack, infix[i]); // ֱ������ջ��
            }
        }
    }
    suffix[pos++] = ' ';
    while (!isStackEmpty(stack)) // ��ջ��ʣ����ŵ���
    {
        suffix[pos++] = stack->rear->val;
        suffix[pos++] = ' ';
        popStack(stack);
    }
    // printf("%s\n", suffix);
}

// ����ջ
// ����ֵ��ջ��ָ��
Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->front = NULL;
    stack->rear = NULL;
    return stack;
}

// ��ʼ���ڵ�
// symbol���ַ�
Node *nodeInit(char symbol)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = symbol;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// ��ջ
// stack��ջ��ָ��
// symbol���ַ�
void pushStack(Stack *stack, char symbol)
{
    // printf("%c��ջ\n", symbol);
    Node *node = nodeInit(symbol);
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
void popStack(Stack *stack)
{
    // printf("%c��ջ\n", stack->rear->val);
    Node *node = stack->rear;
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

// ��ӡջ
// stack��ջ��ָ��
void showStack(Stack *stack)
{
    Node *p = stack->front;
    int i = 1;
    printf("------------\n");
    while (p != NULL)
    {
        printf("%d: %c\n", i++, p->val);
        p = p->next;
    }
    printf("------------\n");
}

// �жϷ�����ջ�����ŵ����ȼ�
// ������2����Ϊ������
// ������1����������ȼ�����ջ����Ϊ������
// ������0����������ȼ�С�ڵ���ջ��
int getPrior(char symbol, Stack *stack)
{
    int symbolLevel = getLevel(symbol);
    int rearLevel = getLevel(stack->rear->val);
    if (symbolLevel == 0)
        return 2;
    else if (symbolLevel > rearLevel || stack->rear->val == '(')
        return 1;
    else if (symbolLevel <= rearLevel)
        return 0;
}

// ��ȡ�ַ������ȼ�
// symbol���ַ�
int getLevel(char symbol)
{
    switch (symbol)
    {
    case ')':
        return 0;
    case '+':
        return 1;
    case '-':
        return 1;
    case '*':
        return 2;
    case '/':
        return 2;
    case '(':
        return 3;
    default:
        return -1;
    }
}

// �ж�ջ�Ƿ�Ϊ��
// stack��ջ��ָ��
int isStackEmpty(Stack *stack)
{
    return stack->front == NULL && stack->rear == NULL;
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
NumNode *numNodeInit(float num)
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
void pushNumStack(NumStack *stack, float num)
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