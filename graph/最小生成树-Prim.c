#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100
#define INF 0x3f3f3f3f

typedef struct vertex
{
    char data;
} Vertex;

typedef struct edge
{
    int weight;
} Edge;

typedef struct mgrath
{
    Vertex vertexes[MAX_VEX];     // �����
    Edge edges[MAX_VEX][MAX_VEX]; // �ڽӾ���
    int vertexCnt, edgeCnt;       // ͼ�е�ǰ�Ķ������ͱ���
} AMGraph;

AMGraph *createAMGraph();
void Prim(AMGraph *graph);

int main(void)
{
    AMGraph *graph = createAMGraph();
    // printf("Print Graph DFS: ");
    Prim(graph);
    return 0;
}

AMGraph *createAMGraph()
{
    AMGraph *graph = (AMGraph *)malloc(sizeof(AMGraph));

    printf("���붥�����ͱ���(��:8,9):");
    scanf("%d,%d", &(graph->vertexCnt), &(graph->edgeCnt));
    getchar(); // ���ջ��з�

    for (int i = 0; i < graph->vertexCnt; i++)
    {
        printf("�������%d�������ֵ:", i + 1);
        scanf("%c", &(graph->vertexes[i].data));
        getchar(); // ���ջ��з�
    }

    for (int i = 0; i < graph->vertexCnt; i++)
        for (int j = 0; j < graph->vertexCnt; j++)
            graph->edges[i][j].weight = INF;

    for (int i = 0; i < graph->edgeCnt; i++)
    {
        int a, b, weight;
        printf("�������%d���߼�Ȩֵ(��: 0 2 8):", i + 1);
        scanf("%d %d %d", &a, &b, &weight);
        graph->edges[a][b].weight = weight;
        graph->edges[b][a].weight = weight;
    }

    return graph;
}

void Prim(AMGraph *graph)
{
    int lowCost[MAX_VEX]; // lowCost[i]��¼��iΪ�յ�ıߵ���СȨֵ����lowCost[i]=0ʱ��ʾ�յ�i����������
    int mst[MAX_VEX];     // mst[i]��¼��ӦlowCost[i]����㣬��mst[i]=0ʱ��ʾ���i����������
    int minEdgeCnt = 0;
    int sum = 0;

    for (int i = 0; i < graph->vertexCnt; i++)
    {
        lowCost[i] = graph->edges[0][i].weight;
        printf("%d ", lowCost[i]);
        mst[i] = 0;
    }

    lowCost[0] = 0;

    while (minEdgeCnt != graph->vertexCnt - 1)
    {
        minEdgeCnt++;
        int min = INF;
        int minPos = -1;

        for (int i = 0; i < graph->vertexCnt; i++)
            if (lowCost[i] < min && lowCost[i] != 0)
            {
                min = lowCost[i];
                minPos = i;
            }

        printf("%c - %c: %d\n", graph->vertexes[mst[minPos]].data, graph->vertexes[minPos].data, min);

        sum += lowCost[minPos];
        lowCost[minPos] = 0;

        for (int i = 0; i < graph->vertexCnt; i++)
            if (graph->edges[minPos][i].weight < lowCost[i])
            {
                lowCost[i] = graph->edges[minPos][i].weight;
                mst[i] = minPos;
            }
    }
    printf("sum:%d", sum);
}