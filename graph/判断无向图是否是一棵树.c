#include <stdio.h>
#include <stdlib.h>

#define MAX_VEX 100

typedef enum
{
    FALSE = 0,
    TRUE = 1
} boolean; // C语言中没有boolean类型，可以利用枚举进行构造boolean类型

typedef struct vertex
{
    char data;
} Vertex;

typedef struct amgrath
{
    Vertex vertexes[MAX_VEX];    // 顶点数组
    int edges[MAX_VEX][MAX_VEX]; // 邻接矩阵
    int vertexCnt, edgeCnt;      // 图中当前的顶点数和边数
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

// 创建图
// return 图的指针
AMGraph *createAMGraph()
{
    AMGraph *graph = (AMGraph *)malloc(sizeof(AMGraph)); // 申请空间

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
            graph->edges[i][j] = 0; // 将邻接矩阵初始化为0

    for (int i = 0; i < graph->edgeCnt; i++)
    {
        int a, b;
        printf("请输入第%d条边(输入两个顶点的序号(从1开始), 如1,2):", i + 1);
        scanf("%d,%d", &a, &b);
        graph->edges[a - 1][b - 1] = 1; // 将邻接矩阵中下标为 a-1,b-1 的元素置为1
        graph->edges[b - 1][a - 1] = 1; // 将邻接矩阵中下标为 b-1,a-1 的元素置为1
    }

    return graph;
}

// 判断无向图是否是一棵树
// graph 图的指针
// return 若是则返回1，否则返回0
boolean isTree(AMGraph *graph)
{
    boolean visited[MAX_VEX]; // 标记顶点是否被访问过的数组
    for (int i = 0; i < graph->vertexCnt; i++)
        visited[i] = FALSE; // 初始化

    if (graph->edgeCnt != graph->vertexCnt - 1) // 如果 边数 不等于 顶点数-1
        return FALSE;                           // 可以直接判断不为一颗树

    DFSForAM(graph, 0, visited);               // 深度优先遍历
    for (int i = 0; i < graph->vertexCnt; i++) // 遍历 标记顶点是否被访问过的数组
        if (!visited[i])                       // 若有顶点未被访问
            return FALSE;                      // 可以直接判断不为一颗树
    return TRUE;                               // 如果 边数 等于 顶点数-1，且所有顶点都被访问了，说明无向图是一棵树
}

// 邻接矩阵的深度优先递归算法
// graph 图的指针
// i 遍历的顶点在顶点数组的下标
// visited 标记顶点是否被访问过的数组
void DFSForAM(AMGraph *graph, int i, boolean *visited)
{
    visited[i] = TRUE; // 将该点标记为已遍历
    for (int j = 0; j < graph->vertexCnt; j++)
        if (!visited[j] && graph->edges[i][j] == 1)
            DFSForAM(graph, j, visited);
}