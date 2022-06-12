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

void readFile(FILE **file, char *fileName);
Queue *createQueue();
Node *createNode(int arrive, int treat);
void pushQueue(Queue *queue, int arrive, int treat);
void popQueue(Queue *queue);
bool isQueueEmpty(Queue *queue);
void showQueue(Queue *queue);

int main(void)
{
    int staffTime = 0, clientTime = 0, clientCount = 0; // ҵ��Ա�ȴ�ʱ�䣬�ͻ��ܵĴ�ʱ�䣬�ͻ���������
    int clock = 0;                                      // �ñ���clock��ģ�⵱ǰʱ��
    int arriveTime, treatTime;
    int willOverClock;
    Queue *queue = createQueue();
    FILE *fp;
    readFile(&fp, "./queue.txt");
    fscanf(fp, "%d %d", &arriveTime, &treatTime); // �����һλ�ͻ���Ϣ���ݴ������
    do
    {
        if (isQueueEmpty(queue) && !feof(fp)) // �ȴ�����Ϊ�գ����һ��пͻ�
        {
            // ֻ�����ʱ�� ������Ա����Ҫ�ȴ�
            staffTime += arriveTime - clock;              // �ۼ�ҵ��Ա�ܵȴ�ʱ��
            clock = arriveTime;                           // ʱ���ƽ����ݴ�����еĿͻ��ĵ���ʱ��
            pushQueue(queue, arriveTime, treatTime);      // �ݴ�����еĿͻ���Ϣ����
            fscanf(fp, "%d %d", &arriveTime, &treatTime); // ��ȡ��һλ�ͻ���Ϣ���ݴ����
        }
        clientTime = clientTime + (clock - queue->front->data.arrive); // ���ÿͻ��ĵȴ�ʱ���ۼƵ��ͻ����ܵȴ�ʱ��
        willOverClock = clock + queue->front->data.treat;              // �趨��ǰ�ͻ���ҵ��������ʱ��
        popQueue(queue);                                               // �ӵȴ����г���һλ�ͻ�
        clientCount++;                                                 // �ۼƿͻ�����
        while (willOverClock > arriveTime && !feof(fp))                // ��һλ�ͻ��ĵ���ʱ���ڵ�ǰ�ͻ��������֮ǰ�����һ��пͻ�
        {
            // printf("arrive%d\n", arriveTime);
            pushQueue(queue, arriveTime, treatTime);      // �ݴ�����еĿͻ���Ϣ����
            fscanf(fp, "%d %d", &arriveTime, &treatTime); // ��ȡ��һλ�ͻ���Ϣ���ݴ����
        }
        clock = willOverClock;                   // ʱ���ƽ�����ǰ�ͻ��������ʱ��
    } while (!isQueueEmpty(queue) || !feof(fp)); // �ȴ����в�Ϊ�ջ��߻��пͻ���have==2��

    clientTime = clientTime + (clock - arriveTime); // ���ÿͻ��ĵȴ�ʱ���ۼƵ��ͻ����ܵȴ�ʱ��
    clientCount++;                                  // �ۼƿͻ�����

    printf("������Ա�ȴ�ʱ�䣺%d\n�ͻ�ƽ���ȴ�ʱ�䣺%lf\n�ͻ�����%d\n", staffTime, (float)clientTime / clientCount, clientCount);
    return 0;
}

void readFile(FILE **file, char *fileName)
{
    int a, b;
    if ((*file = fopen(fileName, "r")) == NULL)
    {
        printf("�ļ��򿪳���");
        exit(0);
    }
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
    printf("--------\n");
    while (node != NULL)
    {
        printf("%d: arrive:%d, treat:%d\n", i++, node->data.arrive, node->data.treat);
        node = node->next;
    }
    printf("--------\n");
}