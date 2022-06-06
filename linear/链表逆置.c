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
    // ��ʼ������
    LinkList head = initList();
    // ��������
    insertNodeHead(head, 10);
    insertNodeHead(head, 6);
    insertNodeTail(head, 3);
    insertNodeTail(head, 5);
    // ��ӡ����
    showList(head);
    // ��������
    reverseList(head);
    // ��ӡ����
    showList(head);
    return 0;
}

// ��ʼ��������ͷ��㣩
LinkList initList()
{
    LinkList head = (LinkNode *)malloc(sizeof(LinkNode)); // ����ͷ���Ŀռ�
    head->data = 0;                                       // ��ʼ��ͷ���
    head->next = NULL;                                    // ͷ����ָ��ָ��NULL
    return head;
}

// ͷ�巨����Ԫ��
// head: ����ͷָ��
// val: ���������������
void insertNodeHead(LinkList head, int val)
{
    LinkNode *newNode = (LinkNode *)malloc(sizeof(LinkNode)); // �����½����ڴ�
    // ������ʧ��
    if (!newNode)
    {
        printf("Memory is full!!!\n");
        return;
    }

    newNode->data = val;        // ��ֵ
    newNode->next = head->next; // �½���ָ����ָ���һ�����
    head->next = newNode;       // ͷ����ָ����ָ���½��
}

// β�巨����Ԫ��
// head: ����ͷָ��
// val: ���������������
void insertNodeTail(LinkList head, int val)
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

// ��ӡ����
// head: ����ͷָ��
void showList(LinkList head)
{
    LinkNode *node = head->next; // �ҵ���һ�����
    int i = 1;
    printf("----------------\nprint list:\n");
    while (node)
    {
        printf("%d: %d\n", i++, node->data);
        node = node->next; // �ҵ���һ�����
    }
    printf("----------------\n");
}

// ��������
// head: ����ͷָ��
void reverseList(LinkList head)
{
    if (isEmpty(head)) // ������Ϊ��
    {
        printf("List is empty!!!\n");
        return;
    }

    LinkNode *tmpNode1 = head->next; // ָ���һ�����
    LinkNode *tmpNode2 = NULL;       // ����ڶ�����ʱָ��

    while (tmpNode1->next)
    {
        tmpNode2 = tmpNode1->next;       // �ҵ� ԭ��һ��������һ�����
        tmpNode1->next = tmpNode2->next; // ԭ��һ������ָ���� ָ�� ��һ������ָ����
        tmpNode2->next = head->next;     // ��һ������ָ���� ָ�� �ֵ�һ�����
        head->next = tmpNode2;           // ͷ����ָ���� ָ�� tmpNode2(��һ�����)
    }
}

int isEmpty(LinkList head)
{
    return !head->next ? 1 : 0;
}