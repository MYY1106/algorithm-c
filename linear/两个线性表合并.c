#include <stdio.h>
#define MaxSize 100

typedef int DataType;
typedef struct
{
    DataType list[MaxSize];
    int size;
} SeqList;

void ListInitiate(SeqList *L);
int ListLength(SeqList L);
int ListInsert(SeqList *L, int i, DataType x);
int ListDelete(SeqList *L, int i, DataType *x);
int ListGet(SeqList L, int i, DataType *x);
void ListShow(SeqList L);
void ListMerge(SeqList *La, SeqList Lb);

int main(void)
{
    SeqList listA, listB;
    int i, x;
    ListInitiate(&listA);
    for (i = 0; i < 10; i++)
        ListInsert(&listA, i, i + 1);
    ListDelete(&listA, 4, &x);
    ListDelete(&listA, 3, &x);
    printf("List A: \n");
    ListShow(listA);
    ListInitiate(&listB);
    ListInsert(&listB, 0, 1);
    ListInsert(&listB, 1, 4);
    ListInsert(&listB, 2, 6);
    printf("List B: \n");
    ListShow(listB);
    ListMerge(&listA, listB);
    printf("after merge, List A: \n");
    ListShow(listA);
}

/* 初始化顺序表L */
void ListInitiate(SeqList *L)
{
    L->size = 0; /* 定义初始数据元素个数 */
}

/* 返回顺序表L的当前数据元素个数 */
int ListLength(SeqList L)
{
    return L.size;
}

/* 在顺序表L的位置i（0 ≤ i ≤ size）前插入数据元素值x */
/* 插入成功返回1，插入失败返回0 */
int ListInsert(SeqList *L, int i, DataType x)
{
    int j;
    if (L->size >= MaxSize)
    {
        printf("顺序表已满无法插入! \n");
        return 0;
    }
    else if (i < 0 || i > L->size)
    {
        printf("参数i不合法! \n");
        return 0;
    }
    else
    {
        for (j = L->size - 1; j >= i; j--)
            L->list[j + 1] = L->list[j]; /* 为插入做准备 */
        L->list[i] = x;                  /* 插入 */
        L->size++;                       /* 元素个数加1 */
        return 1;
    }
}

/* 删除顺序表L中位置i（0 ≤ i ≤ size - 1）的数据元素值并存放到参数x中 */
/* 删除成功返回1，删除失败返回0 */
int ListDelete(SeqList *L, int i, DataType *x)
{
    int j;
    if (L->size <= 0)
    {
        printf("顺序表已空无数据元素可删! \n");
        return 0;
    }
    else if (i < 0 || i > L->size - 1)
    {
        printf("参数i不合法");
        return 0;
    }
    else
    {
        *x = L->list[i]; /* 保存删除的元素到参数x中 */
        for (j = i + 1; j <= L->size - 1; j++)
            L->list[j - 1] = L->list[j]; /* 依次前移 */
        L->size--;                       /* 数据元素个数减1 */
        return 1;
    }
}

/*取顺序表L中第i个数据元素的值存于x中，成功则返回1，失败返回0*/
int ListGet(SeqList L, int i, DataType *x)
{
    if (i < 0 || i > L.size - 1)
    {
        printf("参数i不合法! \n");
        return 0;
    }
    else
    {
        *x = L.list[i];
        return 1;
    }
}

/* 打印顺序表 */
void ListShow(SeqList L)
{
    int i, x;
    for (i = 0; i < ListLength(L); i++)
    {
        ListGet(L, i, &x);
        printf("%d: %d\n", i, x);
    }
    printf("---------------\n");
}

/*
    将Lb合并到La中
    La 线性表结构体的指针
    Lb 线性表结构体
*/
void ListMerge(SeqList *La, SeqList Lb)
{
    int j = 0;
    for (int i = 0; i < La->size; i++)
    {
        // 1 2 3 6 7
        // 1 4 6
        if (Lb.list[j] < La->list[i]) // 当 Lb.list[j] 小于 La->list[i]
        {
            ListInsert(La, i, Lb.list[j]); // 说明此时Lb.list[j]可以插入到La中了，不然就不能有序
            if (j != Lb.size - 1)          // 如果此时还没遍历到Lb的末尾
                j++;                       // 则继续遍历
            else
                break; // 否则退出循环
        }
    }
    while (j < Lb.size - 1)
    {
        ListInsert(La, La->size, Lb.list[j]);
        j++;
    }
}