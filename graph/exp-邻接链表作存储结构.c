#include "stdio.h"
#include "stdlib.h"

#define MaxVertexNum 50 // ������󶥵���

typedef struct node
{                      // �߱���
    int adjvex;        // �ڽӵ���
    struct node *next; // ����
} EdgeNode;

typedef struct vnode
{                        // �������
    char vertex;         // ������
    EdgeNode *firstedge; // �߱�ͷָ��
} VertexNode;

typedef VertexNode AdjList[MaxVertexNum]; // AdjList���ڽӱ�����

typedef struct
{
    AdjList adjlist; // �ڽӱ�
    int n, e;        // ͼ�е�ǰ�������ͱ���
} ALGraph;           // ͼ����

//=========����ͼ���ڽӱ�=======
void CreatALGraph(ALGraph *G)
{
    int i, j;
    char a;
    EdgeNode *s; // ����߱���
    printf("Input VertexNum(n) and EdgesNum(e): ");
    scanf("%d,%d", &G->n, &G->e); // ���붥�����ͱ���
    scanf("%c", &a);              // ���ջ��з�

    printf("Input Vertex string:");
    for (i = 0; i < G->n; i++) // ���������
    {
        scanf("%c", &a);
        G->adjlist[i].vertex = a;       // ���붥����Ϣ
        G->adjlist[i].firstedge = NULL; // �߱���Ϊ�ձ�
    }

    printf("Input edges,Creat Adjacency List\n");
    for (int k = 0; k < G->e; k++)
    {                                             // �����߱�
        scanf("%d%d", &i, &j);                    // ����ߣ�Vi��Vj���Ķ�������
        s = (EdgeNode *)malloc(sizeof(EdgeNode)); // ���ɱ߱���
        s->adjvex = j;                            // �ڽӵ����Ϊj
        s->next = G->adjlist[i].firstedge;
        G->adjlist[i].firstedge = s; // ���½��*S���붥��Vi�ı߱�ͷ��
        s = (EdgeNode *)malloc(sizeof(EdgeNode));
        s->adjvex = i; // �ڽӵ����Ϊi
        s->next = G->adjlist[j].firstedge;
        G->adjlist[j].firstedge = s; // ���½��*S���붥��Vj�ı߱�ͷ��
    }
}

// =========�����־������Ϊȫ�ֱ���=======
typedef enum
{
    FALSE,
    TRUE
} Boolean;
Boolean visited[MaxVertexNum];

// ========DFS��������ȱ����ĵݹ��㷨======
void DFSM(ALGraph *G, int i)
{ // ��ViΪ��������ڽ������ʾ��ͼG����DFS����
    EdgeNode *p;
    printf("%c", G->adjlist[i].vertex); // ���ʶ���Vi
    visited[i] = TRUE;                  // ���Vi�ѷ���
    p = G->adjlist[i].firstedge;        // ȡVi�߱��ͷָ��
    while (p)
    {                            // ��������Vi���ڽӵ�Vj������j=p->adjvex
                                 // ����3�д�����һ������
        if (!visited[p->adjvex]) // ��Vj��δ������
            DFSM(G, p->adjvex);  // ����VjΪ����������������
        p = p->next;             // ��Vi����һ���ڽӵ�
    }
}

void DFS(ALGraph *G)
{
    int i;
    for (i = 0; i < G->n; i++)
        visited[i] = FALSE; // ��־������ʼ��
    for (i = 0; i < G->n; i++)
        if (!visited[i]) // Viδ���ʹ�
            DFSM(G, i);  // ��ViΪԴ�㿪ʼDFS����
}

//==========BFS��������ȱ���=========
void BFS(ALGraph *G, int k)
{ // ��VkΪԴ������ڽ������ʾ��ͼG���й����������
    int i;
    int f = 0, r = 0;
    EdgeNode *p;
    int cq[MaxVertexNum]; // ����FIFO����

    for (i = 0; i < G->n; i++)
        visited[i] = FALSE; // ��־������ʼ��
    for (i = 0; i <= G->n; i++)
        cq[i] = -1; // ��ʼ����־����

    printf("%c", G->adjlist[k].vertex); // ����Դ��Vk
    visited[k] = TRUE;
    cq[r] = k; // Vk�ѷ��ʣ�������ӡ�ע�⣬ʵ�����ǽ���������
    while (cq[f] != -1)
    { // ���зǿ���ִ��
        i = cq[f];
        f = f + 1;                   // Vi����
        p = G->adjlist[i].firstedge; // ȡVi�ı߱�ͷָ��
        while (p)
        { // ��������Vi���ڽӵ�Vj����p->adjvex=j��
            if (!visited[p->adjvex])
            {                                               // ��Vjδ���ʹ�
                printf("%c", G->adjlist[p->adjvex].vertex); // ����Vj
                visited[p->adjvex] = TRUE;
                // ����3�д�����һ������
                r = r + 1;
                cq[r] = p->adjvex; // ���ʹ���Vj���
            }
            p = p->next; // ��Vi����һ���ڽӵ�
        }
    } // endwhile
}

//==========������===========
void main()
{
    int i;
    ALGraph *G;
    G = (ALGraph *)malloc(sizeof(ALGraph));
    CreatALGraph(G);
    printf("Print Graph DFS: ");
    DFS(G);
    printf("\n");
    printf("Print Graph BFS: ");
    BFS(G, 3);
    printf("\n");
}


