#include <stdio.h>
#include <stdlib.h>

typedef int bool;

typedef struct
{
    int arrive;
    int treat; // �ͻ�����Ϣ�ṹ
} Data;

typedef struct Node
{
    Data data;
    struct Node *next; // �����е�Ԫ����Ϣ
} Node;

typedef struct
{
    Node *front; // ��ͷָ��
    Node *rear;  // ��βָ��
} Queue;         // ����������

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

// ��������
Queue *createQueue()
{
    Queue *queue = malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// ��ʼ�����
Node *createNode(int arrive, int treat)
{
    Node *node = malloc(sizeof(Node));
    node->data.arrive = arrive;
    node->data.treat = treat;
    node->next = NULL;
    return node;
}

// ����
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
        queue->rear->next = newNode; // ԭ�ȵĶ�βԪ�ص�ָ����ָ��newNode
        queue->rear = newNode;       // ��β��newNode
    }
}

// ����
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

// �����Ƿ�Ϊ��
bool isQueueEmpty(Queue *queue)
{
    return queue->front == NULL && queue->rear == NULL;
}

// ��ӡ����
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