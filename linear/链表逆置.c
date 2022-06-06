#include <stdio.h>
#include <stdlib.h>

typedef struct LinkNode
{
    int data;
    struct LinkNode *next;
} LinkNode, *LinkList;

LinkList initList();
void insertNodeHead(LinkList head, int val);
void insertNodeTail(LinkList head, int val);
void showList(LinkList head);
void reverseList(LinkList head);
int isEmpty(LinkList head);

int main(void)
{
    // 初始化链表
    LinkList head = initList();
    // 插入数据
    insertNodeHead(head, 10);
    insertNodeHead(head, 6);
    insertNodeTail(head, 3);
    insertNodeTail(head, 5);
    // 打印链表
    showList(head);
    // 逆置链表
    reverseList(head);
    // 打印链表
    showList(head);
    return 0;
}

// 初始化链表（有头结点）
LinkList initList()
{
    LinkList head = (LinkNode *)malloc(sizeof(LinkNode)); // 分配头结点的空间
    head->data = 0;                                       // 初始化头结点
    head->next = NULL;                                    // 头结点的指针指向NULL
    return head;
}

// 头插法插入元素
// head: 链表头指针
// val: 待插入的整型数据
void insertNodeHead(LinkList head, int val)
{
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // 分配新结点的内存
    // 若分配失败
    if (!newNode)
    {
        printf("Memory is full!!!\n");
        return;
    }

    newNode->data = val;        // 赋值
    newNode->next = head->next; // 新结点的指针域指向第一个结点
    head->next = newNode;       // 头结点的指针域指向新结点
}

// 尾插法插入元素
// head: 链表头指针
// val: 待插入的整型数据
void insertNodeTail(LinkList head, int val)
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

// 打印链表
// head: 链表头指针
void showList(LinkList head)
{
    LinkNode *node = head->next; // 找到第一个结点
    int i = 1;
    printf("----------------\nprint list:\n");
    while (node)
    {
        printf("%d: %d\n", i++, node->data);
        node = node->next; // 找到下一个结点
    }
    printf("----------------\n");
}

// 逆置链表
// head: 链表头指针
void reverseList(LinkList head)
{
    if (isEmpty(head)) // 若链表为空
    {
        printf("List is empty!!!\n");
        return;
    }

    LinkNode *tmpNode1 = head->next; // 指向第一个结点
    LinkNode *tmpNode2 = NULL;       // 定义第二个临时指针

    while (tmpNode1->next)
    {
        tmpNode2 = tmpNode1->next;       // 找到 原第一个结点的下一个结点
        tmpNode1->next = tmpNode2->next; // 原第一个结点的指针域 指向 下一个结点的指针域
        tmpNode2->next = head->next;     // 下一个结点的指针域 指向 现第一个结点
        head->next = tmpNode2;           // 头结点的指针域 指向 tmpNode2(下一个结点)
    }
}

int isEmpty(LinkList head)
{
    return !head->next ? 1 : 0;
}