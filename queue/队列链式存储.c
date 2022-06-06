#include <stdio.h>
#include <stdlib.h>

typedef int bool;

typedef struct
{
    int arrive;
    int treat; // 客户的信息结构
} Data;

typedef struct Node
{
    Data data;
    struct Node *next; // 队列中的元素信息
} Node;

typedef struct
{
    Node *front; // 队头指针
    Node *rear;  // 队尾指针
} Queue;         // 链队列类型

Queue *createQueue();
Node *createNode(int arrive, int treat);
void pushQueue(Queue *queue, int arrive, int treat);
void popQueue(Queue *queue);
bool isQueueEmpty(Queue *queue);
void showQueue(Queue *queue);

int main(void)
{
    Queue *q = createQueue();
    pushQueue(q, 1, 2);
    pushQueue(q, 6, 10);
    showQueue(q);
    popQueue(q);
    popQueue(q);
    printf("%d", isQueueEmpty(q));
    return 0;
}

// 创建队列
Queue *createQueue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// 初始化结点
Node *createNode(int arrive, int treat)
{
    Node *node = malloc(sizeof(Node));
    node->data.arrive = arrive;
    node->data.treat = treat;
    node->next = NULL;
    return node;
}

// 入列
void pushQueue(Queue *queue, int arrive, int treat)
{
    Node *newNode = createNode(arrive, treat);
    if (queue->rear == NULL)
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode; // 原先的队尾元素的指针域指向newNode
        queue->rear = newNode;       // 队尾是newNode
    }
}

// 出列
void popQueue(Queue *queue)
{
    Node *node = queue->front;
    if (queue->front == queue->rear)
    {
        queue->front = NULL;
        queue->rear = NULL;
    }
    else
    {
        queue->front = queue->front->next;
    }
    free(node);
}

// 队列是否为空
bool isQueueEmpty(Queue *queue)
{
    return queue->front == NULL && queue->rear == NULL;
}

// 打印队列
void showQueue(Queue *queue)
{
    Node *node = queue->front;
    int i = 1;
    while (node != NULL)
    {
        printf("%d: arrive:%d, treat:%d\n", i++, node->data.arrive, node->data.treat);
        node = node->next;
    }
}