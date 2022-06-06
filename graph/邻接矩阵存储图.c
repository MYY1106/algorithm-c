#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100

typedef struct vertex
{
    char data;
} Vertex;

typedef struct mgrath
{
    Vertex vertexes[MAX_VEX];    // �����
    int edges[MAX_VEX][MAX_VEX]; // �ڽӾ���
    int vertexCnt, edgeCnt;      // ͼ�е�ǰ�Ķ������ͱ���
} AMGraph;

typedef enum
{
    FALSE,
    TRUE
} Boolean;

Boolean visited[MAX_VEX];

AMGraph *createAMGraph();
void DFSTraverseAM(AMGraph *graph);
void DFSForAM(AMGraph *graph, int i);

int main(void)
{
    AMGraph *graph = createAMGraph();
    printf("Print Graph DFS: ");
    DFSTraverseAM(graph); // ������ȱ���
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
        printf("�������%d������:", i + 1);
        scanf("%c", &(graph->vertexes[i].data));
        getchar(); // ���ջ��з�
    }

    for (int i = 0; i < graph->vertexCnt; i++)
        for (int j = 0; j < graph->vertexCnt; j++)
            graph->edges[i][j] = 0;

    for (int i = 0; i < graph->edgeCnt; i++)
    {
        int a, b;
        printf("�������%d����:", i + 1);
        scanf("%d %d", &a, &b);
        graph->edges[a][b] = 1;
        graph->edges[b][a] = 1;
    }

    return graph;
} 

// �ڽӾ����������ȵݹ��㷨
void DFSForAM(AMGraph *graph, int i) // i�㣬����i���ڵĵ���з���
{
    printf("%c ", graph->vertexes[i].data);
    visited[i] = TRUE;
    for (int j = 0; j < graph->vertexCnt; j++)
        if (!visited[j] && graph->edges[i][j] == 1)
            DFSForAM(graph, j);
}

// �ڽӾ����������ȱ�������
void DFSTraverseAM(AMGraph *graph)
{
    for (int i = 0; i < graph->vertexCnt; i++)
        visited[i] = FALSE;

    for (int i = 0; i < graph->vertexCnt; i++)
        if (!visited[i])
            DFSForAM(graph, i);
}

void BFSForAM(AMGraph *graph)
{
    
}