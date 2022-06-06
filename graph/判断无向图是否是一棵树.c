#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100

typedef enum
{
    FALSE = 0,
    TRUE = 1
} boolean; // C������û��boolean���ͣ���������ö�ٽ��й���boolean����

typedef struct vertex
{
    char data;
} Vertex;

typedef struct amgrath
{
    Vertex vertexes[MAX_VEX];    // ��������
    int edges[MAX_VEX][MAX_VEX]; // �ڽӾ���
    int vertexCnt, edgeCnt;      // ͼ�е�ǰ�Ķ������ͱ���
} AMGraph;

AMGraph *createAMGraph();
boolean isTree(AMGraph *graph);
void DFSForAM(AMGraph *graph, int i, boolean *visited);

int main(void)
{
    AMGraph *graph = createAMGraph();
    if (isTree(graph))
        printf("Graph is a tree!");
    else
        printf("Graph is not a tree!");
    return 0;
}

// ����ͼ
// return ͼ��ָ��
AMGraph *createAMGraph()
{
    AMGraph *graph = (AMGraph *)malloc(sizeof(AMGraph)); // ����ռ�

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
            graph->edges[i][j] = 0; // ���ڽӾ����ʼ��Ϊ0

    for (int i = 0; i < graph->edgeCnt; i++)
    {
        int a, b;
        printf("�������%d����(����������������(��1��ʼ), ��1,2):", i + 1);
        scanf("%d,%d", &a, &b);
        graph->edges[a - 1][b - 1] = 1; // ���ڽӾ������±�Ϊ a-1,b-1 ��Ԫ����Ϊ1
        graph->edges[b - 1][a - 1] = 1; // ���ڽӾ������±�Ϊ b-1,a-1 ��Ԫ����Ϊ1
    }

    return graph;
}

// �ж�����ͼ�Ƿ���һ����
// graph ͼ��ָ��
// return �����򷵻�1�����򷵻�0
boolean isTree(AMGraph *graph)
{
    boolean visited[MAX_VEX]; // ��Ƕ����Ƿ񱻷��ʹ�������
    for (int i = 0; i < graph->vertexCnt; i++)
        visited[i] = FALSE; // ��ʼ��

    if (graph->edgeCnt != graph->vertexCnt - 1) // ��� ���� ������ ������-1
        return FALSE;                           // ����ֱ���жϲ�Ϊһ����

    DFSForAM(graph, 0, visited);               // ������ȱ���
    for (int i = 0; i < graph->vertexCnt; i++) // ���� ��Ƕ����Ƿ񱻷��ʹ�������
        if (!visited[i])                       // ���ж���δ������
            return FALSE;                      // ����ֱ���жϲ�Ϊһ����
    return TRUE;                               // ��� ���� ���� ������-1�������ж��㶼�������ˣ�˵������ͼ��һ����
}

// �ڽӾ����������ȵݹ��㷨
// graph ͼ��ָ��
// i �����Ķ����ڶ���������±�
// visited ��Ƕ����Ƿ񱻷��ʹ�������
void DFSForAM(AMGraph *graph, int i, boolean *visited)
{
    visited[i] = TRUE; // ���õ���Ϊ�ѱ���
    for (int j = 0; j < graph->vertexCnt; j++)
        if (!visited[j] && graph->edges[i][j] == 1)
            DFSForAM(graph, j, visited);
}