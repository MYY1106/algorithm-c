#include "stdio.h"
#include "stdlib.h"
#define MaxVertexNum 100 // ������󶥵���

typedef struct
{
    char vexs[MaxVertexNum];               // �����
    int edges[MaxVertexNum][MaxVertexNum]; // �ڽӾ��󣬿ɿ����߱�
    int n, e;                              // ͼ�еĶ�����n�ͱ���e
} MGraph;                                  // ���ڽӾ����ʾ��ͼ������

//=========�����ڽӾ���=======
void CreatMGraph(MGraph *G)
{
    int i, j, k;
    char a;
    printf("Input VertexNum(n) and EdgesNum(e): ");
    scanf("%d,%d", &G->n, &G->e); // ���붥�����ͱ���
    scanf("%c", &a);              // ���ջ��з�
    printf("Input Vertex string:");
    for (i = 0; i < G->n; i++)
    {
        scanf("%c", &a);
        G->vexs[i] = a; // ���붥����Ϣ�����������
    }
    for (i = 0; i < G->n; i++)
        for (j = 0; j < G->n; j++)
            G->edges[i][j] = 0; // ��ʼ���ڽӾ���
    printf("Input edges,Creat Adjacency Matrix\n");
    for (k = 0; k < G->e; k++)
    {                          // ����e���ߣ������ڽӾ���
        scanf("%d%d", &i, &j); // ����ߣ�Vi��Vj���Ķ������
        G->edges[i][j] = 1;
        G->edges[j][i] = 1; // ��Ϊ����ͼ������Ϊ�Գƾ�������������ͼ��ȥ���������
    }
}

//=========�����־������Ϊȫ�ֱ���=======
typedef enum
{
    FALSE,
    TRUE
} Boolean;
Boolean visited[MaxVertexNum];

//========DFS��������ȱ����ĵݹ��㷨======
void DFSM(MGraph *G, int i)
{ // ��ViΪ��������ڽӾ����ʾ��ͼG����DFS�������ڽӾ�����0��1����
    int j;
    printf("%c", G->vexs[i]);  // ���ʶ���Vi
    visited[i] = TRUE;         // ���ѷ��ʱ�־
    for (j = 0; j < G->n; j++) // ��������Vi���ڽӵ�
        if (G->edges[i][j] == 1 && !visited[j])
            DFSM(G, j); // ��Vi��Vj����E����Vjδ���ʹ�����VjΪ�³�����
}

void DFS(MGraph *G)
{ // �˶δ�����һ������
    for (int i = 0; i < G->n; i++)
        visited[i] = FALSE; // ��־������ʼ��
    for (int i = 0; i < G->n; i++)
        if (!visited[i]) // Viδ���ʹ�
            DFSM(G, i);  // ��ViΪԴ�㿪ʼDFS����
}

//===========BFS��������ȱ���=======
void BFS(MGraph *G, int k)
{ // ��VkΪԴ������ڽӾ����ʾ��ͼG���й����������
    int i, j;
    int f = 0, r = 0;     // r(rear)�Ƕ��еĶ�β��ָ�룬f(front)�Ƕ��еĶ�ͷ��ָ��
    int cq[MaxVertexNum]; // �������

    for (i = 0; i < G->n; i++)
        visited[i] = FALSE; // ��־������ʼ��
    for (i = 0; i <= G->n; i++)
        cq[i] = -1; // ���г�ʼ��

    printf("%c", G->vexs[k]); // ����Դ��Vk
    visited[k] = TRUE;
    cq[r] = k; // Vk�ѷ��ʣ�������ӡ�ע�⣬ʵ�����ǽ���������
    while (cq[f] != -1)
    { // �ӷǿ���ִ��
        i = cq[f];
        f = f + 1;                 // Vf����
        for (j = 0; j < G->n; j++) // ����Vi���ڽӵ�Vj
            if (G->edges[i][j] == 1 && !visited[j])
            {                             // Vjδ���� �������д�����һ������
                printf("%c", G->vexs[j]); // ����Vj
                visited[j] = TRUE;
                r = r + 1;
                cq[r] = j; // ���ʹ�Vj���
            }
    }
}

//==========main=====
void main()
{
    MGraph *G;
    G = (MGraph *)malloc(sizeof(MGraph)); // ΪͼG�����ڴ�ռ�
    CreatMGraph(G);                       // �����ڽӾ���
    printf("Print Graph DFS: ");
    DFS(G); // ������ȱ���
    printf("\n");
    printf("Print Graph BFS: ");
    BFS(G, 3); // �����Ϊ3�Ķ��㿪ʼ������ȱ���
    printf("\n");
}


