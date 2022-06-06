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
    printf("����Բ���ϵ�����:");
    scanf("%d", &n);
    LinkList head = initCyclic(n);
    showList(head);
    printf("�ӵڼ����˿�ʼ����(k>1��k<%d)��", n);
    scanf("%d", &k);
    printf("���������˳��У�");
    scanf("%d", &m);
    findAndOut(head, k, m);
    return 0;
}

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
    while (node != head)
    {
        printf("%d: %d\n", i++, node->data.num);
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

// ��ʼ��Լɪ�򻷣���ͷ��㣩
LinkList initCyclic(int n)
{
    LinkList head = (LinkNode *)malloc(sizeof(LinkNode));
    if (!head) // ������ʧ��
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
        if (!tmpNode1) // ������ʧ��
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

// ���Լɪ������
void findAndOut(LinkList head, int k, int m)
{
    LinkNode *p = head->next;
    LinkNode *tail = NULL; // p�Ľ�����һ����㣬������ɾ������

    // �ҵ�numΪk����
    while (p->data.num != k)
    {
        tail = p; // p�Ľ�����һ����㣬������ɾ������
        p = p->next;
    }

    while (p->next->next != p)
    {
        // ��������
        for (int i = 1; i < m; i++)
        {
            if (p == head)
            {
                // ͷ��㱨������
                i--;
            }
            tail = p; // p�Ľ�����һ����㣬������ɾ������
            p = p->next;
        }

        // �����ͷ��㱨��m������ˣ���ô�൱����ʵ��ͷ������һ���ڵ㱨����m�����
        if (p == head)
        {
            tail = p;
            p = p->next;
        }
        tail->next = p->next;
        printf("�����˵ı��Ϊ:%d\n", p->data.num);
        free(p);
        p = tail->next;
    }
}