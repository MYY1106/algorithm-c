#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100

typedef struct vertex
{
    char data;
} Vertex;

typedef struct mgrath
{
    Vertex vertexes[MAX_VEX];    // 顶点表
    int edges[MAX_VEX][MAX_VEX]; // 邻接矩阵
    int vertexCnt, edgeCnt;      // 图中当前的顶点数和边数
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
    DFSTraverseAM(graph); // 深度优先遍历
    return 0;
}

AMGraph *createAMGraph()
{
    AMGraph *graph = (AMGraph *)malloc(sizeof(AMGraph));

    printf("输入顶点数和边数(如:8,9):");
    scanf("%d,%d", &(graph->vertexCnt), &(graph->edgeCnt));
    getchar(); // 吸收换行符

    for (int i = 0; i < graph->vertexCnt; i++)
    {
        printf("请输入第%d个顶点:", i + 1);
        scanf("%c", &(graph->vertexes[i].data));
        getchar(); // 吸收换行符
    }

    for (int i = 0; i < graph->vertexCnt; i++)
        for (int j = 0; j < graph->vertexCnt; j++)
            graph->edges[i][j] = 0;

    for (int i = 0; i < graph->edgeCnt; i++)
    {
        int a, b;
        printf("请输入第%d条边:", i + 1);
        scanf("%d %d", &a, &b);
        graph->edges[a][b] = 1;
        graph->edges[b][a] = 1;
    }

    return graph;
} 

// 邻接矩阵的深度优先递归算法
void DFSForAM(AMGraph *graph, int i) // i点，对与i相邻的点进行访问
{
    printf("%c ", graph->vertexes[i].data);
    visited[i] = TRUE;
    for (int j = 0; j < graph->vertexCnt; j++)
        if (!visited[j] && graph->edges[i][j] == 1)
            DFSForAM(graph, j);
}

// 邻接矩阵的深度优先遍历操作
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