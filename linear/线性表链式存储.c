#include <stdio.h>
#include <stdlib.h>

typedef struct item
{
    int data;
    char name[10];
} Item;

typedef struct LinkNode
{
    Item data;
    struct LinkNode *next;
} LinkNode, *LinkList;

LinkList initList();
void insertListHead(LinkList head, Item val);
void insertListTail(LinkList head, Item val);
void showList(LinkList head);
void reverseList(LinkList head);

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
    while (node)
    {
        printf("%d: %d %s\n", i++, node->data.data, node->data.name);
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

int main(void)
{
    LinkList head = initList();
    insertListTail(head, (Item){10, "myy"});
    insertListTail(head, (Item){3, "fdsf"});
    insertListTail(head, (Item){1, "fdfy"});
    insertListTail(head, (Item){6, "efdfdfdy"});
    showList(head);
    return 0;
}