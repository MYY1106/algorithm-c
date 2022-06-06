#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int bool;

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

bool isValid(char *s);
Stack *createStack();
void showStack(Stack *stack);
Node *nodeInit(char symbol);
void pushStack(Stack *stack, char symbol);
bool isSameSymbol(Stack *stack, char symbol);
void popStack(Stack *stack);
bool isStackEmpty(Stack *stack);

int main(void)
{
    char str[10000];
    gets(str); // ��ѻ��з������ˣ����Բ��ùܻ��з�������
    printf("%d", isValid(str));
    return 0;
}

bool isValid(char *s)
{
    Stack *stack = createStack();
    int len = strlen(s);
    if (len % 2 != 0) // �������ż����ֱ����Ч
        return 0;
    for (int i = 0; i < len; i++)
    {
        switch (s[i])
        {
        case '(':
            pushStack(stack, s[i]);
            break;
        case '[':
            pushStack(stack, s[i]);
            break;
        case '{':
            pushStack(stack, s[i]);
            break;
        case ')':
            if (!isStackEmpty(stack) && isSameSymbol(stack, '('))
                popStack(stack);
            else
                return 0;
            break;
        case ']':
            if (!isStackEmpty(stack) && isSameSymbol(stack, '['))
                popStack(stack);
            else
                return 0;
            break;
        case '}':
            if (!isStackEmpty(stack) && isSameSymbol(stack, '{'))
                popStack(stack);
            else
                return 0;
            break;
        default:
            return 0;
        }
    }
    return isStackEmpty(stack) ? 1 : 0; // �ų� {([����}])�����
}

void showStack(Stack *stack)
{
    Node *p = stack->front;
    int i = 1;
    while (p != NULL)
    {
        printf("%d: %c\n", i++, p->val);
        p = p->next;
    }
}

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->front = NULL;
    stack->rear = NULL;
    return stack;
}

Node *nodeInit(char symbol)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = symbol;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void pushStack(Stack *stack, char symbol)
{
    printf("%c��ջ\n", symbol);
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
}

bool isSameSymbol(Stack *stack, char symbol)
{
    return stack->rear->val == symbol;
}

void popStack(Stack *stack)
{
    printf("%c��ջ\n", stack->rear->val);
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

bool isStackEmpty(Stack *stack)
{
    return stack->front == NULL && stack->rear == NULL;
}