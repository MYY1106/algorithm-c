#include "stdio.h"
#include "stdlib.h"
#define MaxVertexNum 100 // 定义最大顶点数

typedef struct
{
    char vexs[MaxVertexNum];               // 顶点表
    int edges[MaxVertexNum][MaxVertexNum]; // 邻接矩阵，可看作边表
    int n, e;                              // 图中的顶点数n和边数e
} MGraph;                                  // 用邻接矩阵表示的图的类型

//=========建立邻接矩阵=======
void CreatMGraph(MGraph *G)
{
    int i, j, k;
    char a;
    printf("Input VertexNum(n) and EdgesNum(e): ");
    scanf("%d,%d", &G->n, &G->e); // 输入顶点数和边数
    scanf("%c", &a);              // 吸收换行符
    printf("Input Vertex string:");
    for (i = 0; i < G->n; i++)
    {
        scanf("%c", &a);
        G->vexs[i] = a; // 读入顶点信息，建立顶点表
    }
    for (i = 0; i < G->n; i++)
        for (j = 0; j < G->n; j++)
            G->edges[i][j] = 0; // 初始化邻接矩阵
    printf("Input edges,Creat Adjacency Matrix\n");
    for (k = 0; k < G->e; k++)
    {                          // 读入e条边，建立邻接矩阵
        scanf("%d%d", &i, &j); // 输入边（Vi，Vj）的顶点序号
        G->edges[i][j] = 1;
        G->edges[j][i] = 1; // 若为无向图，矩阵为对称矩阵；若建立有向图，去掉该条语句
    }
}

//=========定义标志向量，为全局变量=======
typedef enum
{
    FALSE,
    TRUE
} Boolean;
Boolean visited[MaxVertexNum];

//========DFS：深度优先遍历的递归算法======
void DFSM(MGraph *G, int i)
{ // 以Vi为出发点对邻接矩阵表示的图G进行DFS搜索，邻接矩阵是0，1矩阵
    int j;
    printf("%c", G->vexs[i]);  // 访问顶点Vi
    visited[i] = TRUE;         // 置已访问标志
    for (j = 0; j < G->n; j++) // 依次搜索Vi的邻接点
        if (G->edges[i][j] == 1 && !visited[j])
            DFSM(G, j); // （Vi，Vj）∈E，且Vj未访问过，故Vj为新出发点
}

void DFS(MGraph *G)
{ // 此段代码有一处错误
    for (int i = 0; i < G->n; i++)
        visited[i] = FALSE; // 标志向量初始化
    for (int i = 0; i < G->n; i++)
        if (!visited[i]) // Vi未访问过
            DFSM(G, i);  // 以Vi为源点开始DFS搜索
}

//===========BFS：广度优先遍历=======
void BFS(MGraph *G, int k)
{ // 以Vk为源点对用邻接矩阵表示的图G进行广度优先搜索
    int i, j;
    int f = 0, r = 0;     // r(rear)是队列的队尾的指针，f(front)是队列的队头的指针
    int cq[MaxVertexNum]; // 定义队列

    for (i = 0; i < G->n; i++)
        visited[i] = FALSE; // 标志向量初始化
    for (i = 0; i <= G->n; i++)
        cq[i] = -1; // 队列初始化

    printf("%c", G->vexs[k]); // 访问源点Vk
    visited[k] = TRUE;
    cq[r] = k; // Vk已访问，将其入队。注意，实际上是将其序号入队
    while (cq[f] != -1)
    { // 队非空则执行
        i = cq[f];
        f = f + 1;                 // Vf出队
        for (j = 0; j < G->n; j++) // 依次Vi的邻接点Vj
            if (G->edges[i][j] == 1 && !visited[j])
            {                             // Vj未访问 以下三行代码有一处错误
                printf("%c", G->vexs[j]); // 访问Vj
                visited[j] = TRUE;
                r = r + 1;
                cq[r] = j; // 访问过Vj入队
            }
    }
}

//==========main=====
void main()
{
    MGraph *G;
    G = (MGraph *)malloc(sizeof(MGraph)); // 为图G申请内存空间
    CreatMGraph(G);                       // 建立邻接矩阵
    printf("Print Graph DFS: ");
    DFS(G); // 深度优先遍历
    printf("\n");
    printf("Print Graph BFS: ");
    BFS(G, 3); // 以序号为3的顶点开始广度优先遍历
    printf("\n");
}


