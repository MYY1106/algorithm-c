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
int ListMerge(SeqList *La, SeqList Lb);

int main(void)
{
    SeqList myList, Listb;
    int i, x;
    ListInitiate(&myList);
    for (i = 0; i < 10; i++)
        ListInsert(&myList, i, i + 1);
    ListDelete(&myList, 4, &x);
    ListDelete(&myList, 3, &x);
    ListShow(myList);
    // for (i = 0; i < ListLength(myList); i++)
    // {
    //     ListGet(myList, i, &x);
    //     printf("%d: %d\n", i, x);
    // }
    ListInitiate(&Listb);
    ListInsert(&Listb, 0, 1);
    ListInsert(&Listb, 1, 4);
    ListInsert(&Listb, 2, 6);
    ListShow(Listb);
    ListMerge(&myList, Listb);
    ListShow(myList);
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
    printf("---------------\n");
    for (i = 0; i < ListLength(L); i++)
    {
        ListGet(L, i, &x);
        printf("%d: %d\n", i, x);
    }
}

/* 合并两个有序表 */
/* 将Lb的元素插入到La */
int ListMerge(SeqList *La, SeqList Lb)
{
    int j = 0;
    for (int i = 0; i < La->size; i++)
    {
        // 1 2 3 6 7
        // 1 6 5
        if (Lb.list[j] < La->list[i])
        {
            ListInsert(La, i, Lb.list[j]);
            if (j != Lb.size - 1)
                j++;
            else
                break;
        }
    }
}