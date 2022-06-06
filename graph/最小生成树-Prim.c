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
    Vertex vertexes[MAX_VEX];     // 顶点表
    Edge edges[MAX_VEX][MAX_VEX]; // 邻接矩阵
    int vertexCnt, edgeCnt;       // 图中当前的顶点数和边数
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

    printf("输入顶点数和边数(如:8,9):");
    scanf("%d,%d", &(graph->vertexCnt), &(graph->edgeCnt));
    getchar(); // 吸收换行符

    for (int i = 0; i < graph->vertexCnt; i++)
    {
        printf("请输入第%d个顶点的值:", i + 1);
        scanf("%c", &(graph->vertexes[i].data));
        getchar(); // 吸收换行符
    }

    for (int i = 0; i < graph->vertexCnt; i++)
        for (int j = 0; j < graph->vertexCnt; j++)
            graph->edges[i][j].weight = INF;

    for (int i = 0; i < graph->edgeCnt; i++)
    {
        int a, b, weight;
        printf("请输入第%d条边及权值(如: 0 2 8):", i + 1);
        scanf("%d %d %d", &a, &b, &weight);
        graph->edges[a][b].weight = weight;
        graph->edges[b][a].weight = weight;
    }

    return graph;
}

void Prim(AMGraph *graph)
{
    int lowCost[MAX_VEX]; // lowCost[i]记录以i为终点的边的最小权值，当lowCost[i]=0时表示终点i加入生成树
    int mst[MAX_VEX];     // mst[i]记录对应lowCost[i]的起点，当mst[i]=0时表示起点i加入生成树
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