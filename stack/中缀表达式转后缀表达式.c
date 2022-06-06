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

int main(void)
{
    char str[MAX_SIZE];
    printf("��������׺���ʽ��֧��С�����磺1+2*4+9*(6*9+2)/5 �� 1.7+2*4+9*(6*9+2)/5����\n");
    gets(str); // ��ѻ��з������ˣ����Բ��ùܻ��з�������
    infixToSuffix(str);
    return 0;
}

char *infixToSuffix(char *infix)
{
    Stack *stack = createStack();
    char suffix[MAX_SIZE] = ""; // ��ź�׺���ʽ
    int pos = 0;                // ����ָ��suffix�������±�
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
    printf("%s\n", suffix);
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