#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *prev; // 双向链表的目的就是当在pop的时候，可以不用遍历栈去找到栈顶的第二个元素
    struct node *next;
} Node;
typedef struct
{
    Node *head;
    Node *rear;
    Node *min_head;
    Node *min_rear;
    int min; // min不初始化就会getmin出问题，??-1094795586
} MinStack;

int minStackGetMin(MinStack *stack);

// 初始最小栈
MinStack *minStackCreate()
{
    MinStack *stack = malloc(sizeof(MinStack));
    stack->head = NULL;
    stack->rear = NULL;
    stack->min_head = NULL;
    stack->min_rear = NULL;
    return stack;
}

// 初始化节点
Node *nodeInit(int val)
{
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

void minStackPush(MinStack *stack, int val)
{
    printf("push=%d\n", val);
    // 初始化节点并赋??
    Node *node = nodeInit(val);

    // 栈顶赋值操??
    if (stack->head == NULL)
    {
        stack->min = val;   // 最小值就是x
        stack->head = node; // 栈底是node
        stack->rear = node; // 栈顶也是node
    }
    else
    {
        stack->rear->next = node;        // 原先的栈顶的指针域指向node
        node->prev = stack->rear;        // node的prev指向原先的栈??
        stack->rear = stack->rear->next; // 栈顶是node
    }

    if (stack->min > val)
    {
        stack->min = val;
    }

    if (stack->min_head == NULL)
    {
        Node *minNode = nodeInit(stack->min);
        stack->min_head = minNode;
        stack->min_rear = minNode;
    }
    else
    {
        int stackMinVal = minStackGetMin(stack);
        if (val > stackMinVal)
            val = stackMinVal;
        Node *minNode = nodeInit(val);
        stack->min_rear->next = minNode;
        minNode->prev = stack->min_rear;
        stack->min_rear = stack->min_rear->next;
    }
}

void minStackPop(MinStack *stack)
{
    if (stack->rear == NULL)
        return;
    Node *topNode = stack->rear;
    stack->rear = topNode->prev;
    printf("pop=%d\n", topNode->val); //假如只有一个节点，则此时t->prev==NULL
    if (stack->rear == NULL)
    {
        stack->head = NULL;
    }
    else
    {
        stack->rear->next = NULL;
    }
    free(topNode);
    Node *minTopNode = stack->min_rear;
    stack->min_rear = minTopNode->prev;
    if (stack->min_rear == NULL)
    {
        stack->min_head = NULL;
    }
    else
    {
        stack->min_rear->next = NULL;
    }
    free(minTopNode);
}

int minStackTop(MinStack *stack)
{
    return stack == NULL ? 0 : stack->rear->val;
}

int minStackGetMin(MinStack *stack)
{
    return stack == NULL ? 0 : stack->min_rear->val;
}

void minStackFree(MinStack *stack)
{
    while (stack->rear != NULL)
        minStackPop(stack);
    free(stack);
}

int main(void)
{
    MinStack *obj = minStackCreate();
    minStackPush(obj, 4);
    minStackPush(obj, 3);
    minStackPush(obj, 5);
    minStackPop(obj);
    int param_3 = minStackTop(obj);
    int param_4 = minStackGetMin(obj);
    minStackFree(obj);
}