#include <stdio.h>  /*该文件包含printf()等函数*/
#include <stdlib.h> /*该文件包含exit()等函数*/
#include <malloc.h> /*该文件包含malloc()等函数*/

typedef int DataType; /*定义DataType为int*/

typedef struct Node
{
    DataType data;
    struct Node *next;
} SLNode;

void ListInitiate(SLNode **head) /* 初始化 */
{
    /*如果有内存空间，申请头结点空间并使头指针head指向头结点*/
    if ((*head = (SLNode *)malloc(sizeof(SLNode))) == NULL)
        exit(1);
    (*head)->next = NULL; /*置链尾标记NULL */
}

int ListLength(SLNode *head) /* 单链表的长度*/
{
    SLNode *p = head; /*p指向首元结点*/
    int size = 0;     /*size初始为0*/

    while (p->next != NULL) /*循环计数*/
    {
        p = p->next;
        size++;
    }
    return size;
}

int ListInsert(SLNode *head, int i, DataType x)
/*在带头结点的单链表head的数据元素ai（0 ≤ i ≤ size）结点前*/
/*插入一个存放数据元素x的结点*/
{
    SLNode *p, *q;
    int j;

    p = head; /*p指向首元结点*/
    j = -1;   /*j初始为-1*/
    while (p->next != NULL && j < i - 1)
    /*最终让指针p指向数据元素ai-1结点*/
    {
        p = p->next;
        j++;
    }

    if (j != i - 1)
    {
        printf("插入位置参数错！");
        return 0;
    }

    /*生成新结点由指针q指示*/
    if ((q = (SLNode *)malloc(sizeof(SLNode))) == NULL)
        exit(1);
    q->data = x;

    //此段程序有一处错误
    q->next = p->next; /*给指针q->next赋值*/
    p->next = q;       /*给指针p->next重新赋值*/
    return 1;
}

int ListDelete(SLNode *head, int i, DataType *x)
/*删除带头结点的单链表head的数据元素ai（0 ≤ i ≤ size - 1）结点*/
/*删除结点的数据元素域值由x带回。删除成功时返回1；失败返回0*/
{
    SLNode *p, *s;
    int j;

    p = head; /*p指向首元结点*/
    j = -1;   /*j初始为-1*/
    while (p->next != NULL && p->next->next != NULL && j < i - 1)
    /*最终让指针p指向数据元素ai-1结点*/
    {
        p = p->next;
        j++;
    }

    if (j != i - 1)
    {
        printf("删除位置参数错！");
        return 0;
    }

    //此段程序有一处错误
    s = p->next;       /*指针s指向数据元素ai结点*/
    *x = s->data;      /*把指针s所指结点的数据元素域值赋予x*/
    p->next = s->next; /*把数据元素ai结点从单链表中删除*/
    free(s);           /*释放指针s所指结点的内存空间*/
    return 1;
}

int ListGet(SLNode *head, int i, DataType *x)
/*取数据元素ai和删除函数类同，只是不删除数据元素ai结点*/
{
    SLNode *p;
    int j;

    p = head;
    j = -1;
    while (p->next != NULL && j < i)
    {
        p = p->next;
        j++;
    }

    if (j != i)
    {
        printf("取元素位置参数错！");
        return 0;
    }

    *x = p->data;
    return 1;
}

void Destroy(SLNode **head)
{
    SLNode *p, *p1;

    p = *head;
    while (p != NULL)
    {
        p1 = p;
        p = p->next;
        free(p1);
    }
    *head = NULL;
}

void ListMerge(SLNode *La, SLNode *Lb)
{
    int aItem, bItem;
    int pos = 0;
    for (int i = 0; i < ListLength(La); i++)
    {
        ListGet(La, i, &aItem);
        ListGet(Lb, pos, &bItem);
        if (bItem <= aItem)
        {
            ListInsert(La, i, bItem);
            pos++;
        }
    }
    while (pos < ListLength(Lb))
    {
        ListGet(Lb, pos, &bItem);
        ListInsert(La, ListLength(La), bItem);
        pos++;
    }
}

void main(void)
{
    SLNode *head;
    int i, x;
    ListInitiate(&head); /*初始化*/
    for (i = 0; i < 5; i++)
    {
        if (ListInsert(head, i, i + 1) == 0) /*插入10个数据元素*/
        {
            printf("错误! \n");
            return;
        }
    }

    if (ListDelete(head, 4, &x) == 0) /*删除数据元素5*/
    {
        printf("错误! \n");
        return;
    }

    // for (i = 0; i < ListLength(head); i++)
    // {
    //     if (ListGet(head, i, &x) == 0) /*取元素*/
    //     {
    //         printf("错误! \n");
    //         return;
    //     }
    //     else
    //         printf("%d    ", x); /*显示数据元素*/
    // }

    SLNode *head2;
    ListInitiate(&head2);
    ListInsert(head2, 0, 0);
    ListInsert(head2, 1, 3);
    ListInsert(head2, 2, 5);
    ListInsert(head2, 3, 7);

    // for (i = 0; i < ListLength(head2); i++)
    // {
    //     if (ListGet(head2, i, &x) == 0) /*取元素*/
    //     {
    //         printf("错误! \n");
    //         return;
    //     }
    //     else
    //         printf("%d    ", x); /*显示数据元素*/
    // }

    ListMerge(head, head2);

    for (i = 0; i < ListLength(head); i++)
    {
        if (ListGet(head, i, &x) == 0) /*取元素*/
        {
            printf("错误! \n");
            return;
        }
        else
            printf("%d    ", x); /*显示数据元素*/
    }

    Destroy(&head);
}
