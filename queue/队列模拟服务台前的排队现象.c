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

void readFile(FILE **file, char *fileName);
Queue *createQueue();
Node *createNode(int arrive, int treat);
void pushQueue(Queue *queue, int arrive, int treat);
void popQueue(Queue *queue);
bool isQueueEmpty(Queue *queue);
void showQueue(Queue *queue);

int main(void)
{
    int staffTime = 0, clientTime = 0, clientCount = 0; // 业务员等待时间，客户总的待时间，客户总人数等
    int clock = 0;                                      // 用变量clock来模拟当前时间
    int arriveTime, treatTime;
    int willOverClock;
    Queue *queue = createQueue();
    FILE *fp;
    readFile(&fp, "./queue.txt");
    fscanf(fp, "%d %d", &arriveTime, &treatTime); // 读入第一位客户信息于暂存变量中
    do
    {
        if (isQueueEmpty(queue) && !feof(fp)) // 等待队列为空，并且还有客户
        {
            // 只有这个时候 工作人员才需要等待
            staffTime += arriveTime - clock;              // 累计业务员总等待时间
            clock = arriveTime;                           // 时钟推进到暂存变量中的客户的到达时间
            pushQueue(queue, arriveTime, treatTime);      // 暂存变量中的客户信息进队
            fscanf(fp, "%d %d", &arriveTime, &treatTime); // 读取下一位客户信息于暂存变量
        }
        clientTime = clientTime + (clock - queue->front->data.arrive); // 将该客户的等待时间累计到客户的总等待时间
        willOverClock = clock + queue->front->data.treat;              // 设定当前客户的业务办理结束时间
        popQueue(queue);                                               // 从等待队列出队一位客户
        clientCount++;                                                 // 累计客户人数
        while (willOverClock > arriveTime && !feof(fp))                // 下一位客户的到达时间在当前客户处理结束之前，并且还有客户
        {
            // printf("arrive%d\n", arriveTime);
            pushQueue(queue, arriveTime, treatTime);      // 暂存变量中的客户信息进队
            fscanf(fp, "%d %d", &arriveTime, &treatTime); // 读取下一位客户信息于暂存变量
        }
        clock = willOverClock;                   // 时钟推进到当前客户办理结束时间
    } while (!isQueueEmpty(queue) || !feof(fp)); // 等待队列不为空或者还有客户（have==2）

    clientTime = clientTime + (clock - arriveTime); // 将该客户的等待时间累计到客户的总等待时间
    clientCount++;                                  // 累计客户人数

    printf("工作人员等待时间：%d\n客户平均等待时间：%lf\n客户数：%d\n", staffTime, (float)clientTime / clientCount, clientCount);
    return 0;
}

void readFile(FILE **file, char *fileName)
{
    int a, b;
    if ((*file = fopen(fileName, "r")) == NULL)
    {
        printf("文件打开出错");
        exit(0);
    }
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
    printf("--------\n");
    while (node != NULL)
    {
        printf("%d: arrive:%d, treat:%d\n", i++, node->data.arrive, node->data.treat);
        node = node->next;
    }
    printf("--------\n");
}