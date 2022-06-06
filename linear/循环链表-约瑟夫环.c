#include <stdio.h>
#include <stdlib.h>

typedef struct item
{
    int num;
} Item;

typedef struct LinkNode
{
    Item data;
    struct LinkNode *next;
} LinkNode, *LinkList;

LinkList initList();
LinkList initCyclic(int count);
void insertListHead(LinkList head, Item val);
void insertListTail(LinkList head, Item val);
void showList(LinkList head);
void reverseList(LinkList head);
void findAndOut(LinkList head, int k, int m);

int main(void)
{
    int n, k, m;
    printf("输入圆桌上的人数:");
    scanf("%d", &n);
    LinkList head = initCyclic(n);
    showList(head);
    printf("从第几个人开始报数(k>1且k<%d)：", n);
    scanf("%d", &k);
    printf("数到几的人出列：");
    scanf("%d", &m);
    findAndOut(head, k, m);
    return 0;
}

// 初始化链表（有头结点）
LinkList initList()
{
    LinkList head = (LinkNode *)malloc(sizeof(LinkNode));
    if (!head) // 若分配失败
    {
        printf("Memory is full!!!\n");
        exit(0);
    }
    head->next = NULL;
    return head;
}

// 头插法插入元素
// head: 链表头指针
// val: 待插入的结构体
void insertListHead(LinkList head, Item val)
{
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // 分配内存
    if (!newNode)                                             // 若分配失败
    {
        printf("Memory is full!!!\n");
        return;
    }

    newNode->data = val;
    newNode->next = head->next;
    head->next = newNode;
}

// 尾插法插入元素
// head: 链表头指针
// val: 待插入的整型数据
void insertListTail(LinkList head, Item val)
{
    LinkNode *node = head;

    // 找到最后一个结点
    while (node && node->next)
    {
        node = node->next;
    }

    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // 分配新结点的内存
    if (!newNode)                                             // 若分配失败
    {
        printf("Memory is full!!!\n");
        return;
    }

    newNode->data = val;  // 赋值
    newNode->next = NULL; // 新结点的指针域指向NULL
    node->next = newNode; // 最后一个结点的指针域指向新结点
}

// 获取链表中的数据，并赋值给item指针
void getItem(LinkList head, int index, Item **item)
{
    LinkNode *node = head->next;
    int j = 1;
    if (index <= 0)
    {
        printf("Index out of range!\n");
        return;
    }
    while (node && j < index)
    {
        node = node->next;
        j++;
    }
    if (node)
    {
        printf("Index out of range!\n");
    }
    else
    {
        *item = &(node->data);
    }
}

// 打印链表
// head: 链表头指针
void showList(LinkList head)
{
    LinkNode *node = head->next;
    int i = 1;
    while (node != head)
    {
        printf("%d: %d\n", i++, node->data.num);
        node = node->next;
    }
}

// 删除元素
void deleteList(LinkList head, int index)
{
    LinkNode *node = head->next;
    int j = 1;
    if (index <= 0)
    {
        printf("Index out of range!\n");
        return;
    }
    while (j < index - 1)
    {
        node = node->next;
        j++;
    }
    if (node)
    {
        printf("Index out of range!\n");
    }
    else
    {
        LinkNode *delNode = node->next;
        node->next = delNode->next;
        free(delNode);
    }
}

// 逆置链表
// head: 链表头指针
void reverseList(LinkList head)
{
    if (!head->next) // 若链表为空
    {
        printf("List is empty!!!");
        return;
    }
    LinkNode *tmpNode1 = head->next; // 第一个结点
    while (tmpNode1->next != NULL)
    {
        LinkNode *tmpNode2 = tmpNode1->next; // 找到 原第一个结点的下一个结点
        tmpNode1->next = tmpNode2->next;     // 原第一个结点的指针域 指向 下一个结点的指针域
        tmpNode2->next = head->next;         //下一个结点的指针域 指向 现第一个结点
        head->next = tmpNode2;               // 头结点的指针域 指向 下一个结点
    }
}

// 初始化约瑟夫环（有头结点）
LinkList initCyclic(int n)
{
    LinkList head = (LinkNode *)malloc(sizeof(LinkNode));
    if (!head) // 若分配失败
    {
        printf("Memory is full!!!\n");
        exit(0);
    }
    LinkNode *tmpNode1 = NULL;
    LinkNode *tmpNode2 = head;
    head->data.num = -1;
    head->next = NULL;

    for (int i = 1; i <= n; i++)
    {
        tmpNode1 = (LinkNode *)malloc(sizeof(LinkNode));
        if (!tmpNode1) // 若分配失败
        {
            printf("Memory is full!!!\n");
            return NULL;
        }
        tmpNode1->data.num = i;
        tmpNode1->next = NULL;
        tmpNode2->next = tmpNode1;
        tmpNode2 = tmpNode1;
    }
    tmpNode2->next = head;

    return head;
}

// 求解约瑟夫环问题
void findAndOut(LinkList head, int k, int m)
{
    LinkNode *p = head->next;
    LinkNode *tail = NULL; // p的结点的上一个结点，便于做删除操作

    // 找到num为k的人
    while (p->data.num != k)
    {
        tail = p; // p的结点的上一个结点，便于做删除操作
        p = p->next;
    }

    while (p->next->next != p)
    {
        // 报数操作
        for (int i = 1; i < m; i++)
        {
            if (p == head)
            {
                // 头结点报数不算
                i--;
            }
            tail = p; // p的结点的上一个结点，便于做删除操作
            p = p->next;
        }

        // 如果是头结点报到m这个数了，那么相当于其实是头结点的下一个节点报到了m这个数
        if (p == head)
        {
            tail = p;
            p = p->next;
        }
        tail->next = p->next;
        printf("出列人的编号为:%d\n", p->data.num);
        free(p);
        p = tail->next;
    }
}