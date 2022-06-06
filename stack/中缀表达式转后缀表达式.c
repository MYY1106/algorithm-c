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
} Node; // 双向链表

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
    printf("请输入中缀表达式，支持小数（如：1+2*4+9*(6*9+2)/5 或 1.7+2*4+9*(6*9+2)/5）：\n");
    gets(str); // 会把换行符吸收了，所以不用管换行符的问题
    infixToSuffix(str);
    return 0;
}

char *infixToSuffix(char *infix)
{
    Stack *stack = createStack();
    char suffix[MAX_SIZE] = ""; // 存放后缀表达式
    int pos = 0;                // 用于指定suffix的数组下标
    for (int i = 0; i < strlen(infix); i++)
    {
        if (isdigit(infix[i]) || infix[i] == '.') // 若遇到的是数字或者小数点，直接输出
        {
            suffix[pos++] = infix[i];
        }
        else
        {
            suffix[pos++] = ' ';
            if (!isStackEmpty(stack)) // 若栈非空
            {
                switch (getPrior(infix[i], stack))
                {
                case 2: // 当遍历到的是右括号时
                    while (stack->rear->val != '(')
                    {
                        suffix[pos++] = stack->rear->val;
                        popStack(stack);
                        suffix[pos++] = ' ';
                    }
                    popStack(stack);
                    break;
                case 1: // 当遍历到的字符优先级大于栈顶元素时
                    pushStack(stack, infix[i]);
                    break;
                case 0:                                                            // 当遍历到的字符优先级小于或等于栈顶元素时
                    while (!isStackEmpty(stack) && getPrior(infix[i], stack) == 0) // 将栈内优先级高于或者等于字符的弹出
                    {
                        suffix[pos++] = stack->rear->val;
                        popStack(stack);
                        suffix[pos++] = ' ';
                    }
                    pushStack(stack, infix[i]); // 将字符推入栈中
                    break;
                }
            }
            else
            {
                pushStack(stack, infix[i]); // 直接推入栈中
            }
        }
    }
    suffix[pos++] = ' ';
    while (!isStackEmpty(stack)) // 将栈中剩余符号弹出
    {
        suffix[pos++] = stack->rear->val;
        suffix[pos++] = ' ';
        popStack(stack);
    }
    printf("%s\n", suffix);
}

// 创建栈
// 返回值：栈的指针
Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->front = NULL;
    stack->rear = NULL;
    return stack;
}

// 初始化节点
// symbol：字符
Node *nodeInit(char symbol)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = symbol;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// 入栈
// stack：栈的指针
// symbol：字符
void pushStack(Stack *stack, char symbol)
{
    // printf("%c入栈\n", symbol);
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

// 出栈
// stack：栈的指针
void popStack(Stack *stack)
{
    // printf("%c出栈\n", stack->rear->val);
    Node *node = stack->rear;
    if (node->prev == NULL) //只剩下一个元素
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

// 打印栈
// stack：栈的指针
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

// 判断符号与栈顶符号的优先级
// 若返回2，则为右括号
// 若返回1，则符号优先级大于栈顶或为左括号
// 若返回0，则符号优先级小于等于栈顶
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

// 获取字符的优先级
// symbol：字符
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

// 判断栈是否为空
// stack：栈的指针
int isStackEmpty(Stack *stack)
{
    return stack->front == NULL && stack->rear == NULL;
}