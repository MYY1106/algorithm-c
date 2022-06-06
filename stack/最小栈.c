#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node *prev; // ˫�������Ŀ�ľ��ǵ���pop��ʱ�򣬿��Բ��ñ���ջȥ�ҵ�ջ���ĵڶ���Ԫ��
    struct node *next;
} Node;
typedef struct
{
    Node *head;
    Node *rear;
    Node *min_head;
    Node *min_rear;
    int min; // min����ʼ���ͻ�getmin�����⣬??-1094795586
} MinStack;

int minStackGetMin(MinStack *stack);

// ��ʼ��Сջ
MinStack *minStackCreate()
{
    MinStack *stack = malloc(sizeof(MinStack));
    stack->head = NULL;
    stack->rear = NULL;
    stack->min_head = NULL;
    stack->min_rear = NULL;
    return stack;
}

// ��ʼ���ڵ�
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
    // ��ʼ���ڵ㲢��??
    Node *node = nodeInit(val);

    // ջ����ֵ��??
    if (stack->head == NULL)
    {
        stack->min = val;   // ��Сֵ����x
        stack->head = node; // ջ����node
        stack->rear = node; // ջ��Ҳ��node
    }
    else
    {
        stack->rear->next = node;        // ԭ�ȵ�ջ����ָ����ָ��node
        node->prev = stack->rear;        // node��prevָ��ԭ�ȵ�ջ??
        stack->rear = stack->rear->next; // ջ����node
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
    printf("pop=%d\n", topNode->val); //����ֻ��һ���ڵ㣬���ʱt->prev==NULL
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