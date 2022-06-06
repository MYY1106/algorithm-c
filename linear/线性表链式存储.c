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

// ��ʼ��������ͷ��㣩
LinkList initList()
{
    LinkList head = (LinkNode *)malloc(sizeof(LinkNode));
    if (!head) // ������ʧ��
    {
        printf("Memory is full!!!\n");
        exit(0);
    }
    head->next = NULL;
    return head;
}

// ͷ�巨����Ԫ��
// head: ����ͷָ��
// val: ������Ľṹ��
void insertListHead(LinkList head, Item val)
{
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // �����ڴ�
    if (!newNode)                                             // ������ʧ��
    {
        printf("Memory is full!!!\n");
        return;
    }

    newNode->data = val;
    newNode->next = head->next;
    head->next = newNode;
}

// β�巨����Ԫ��
// head: ����ͷָ��
// val: ���������������
void insertListTail(LinkList head, Item val)
{
    LinkNode *node = head;

    // �ҵ����һ�����
    while (node && node->next)
    {
        node = node->next;
    }

    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // �����½����ڴ�
    if (!newNode)                                             // ������ʧ��
    {
        printf("Memory is full!!!\n");
        return;
    }

    newNode->data = val;  // ��ֵ
    newNode->next = NULL; // �½���ָ����ָ��NULL
    node->next = newNode; // ���һ������ָ����ָ���½��
}

// ��ȡ�����е����ݣ�����ֵ��itemָ��
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

// ��ӡ����
// head: ����ͷָ��
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

// ɾ��Ԫ��
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

// ��������
// head: ����ͷָ��
void reverseList(LinkList head)
{
    if (!head->next) // ������Ϊ��
    {
        printf("List is empty!!!");
        return;
    }
    LinkNode *tmpNode1 = head->next; // ��һ�����
    while (tmpNode1->next != NULL)
    {
        LinkNode *tmpNode2 = tmpNode1->next; // �ҵ� ԭ��һ��������һ�����
        tmpNode1->next = tmpNode2->next;     // ԭ��һ������ָ���� ָ�� ��һ������ָ����
        tmpNode2->next = head->next;         //��һ������ָ���� ָ�� �ֵ�һ�����
        head->next = tmpNode2;               // ͷ����ָ���� ָ�� ��һ�����
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