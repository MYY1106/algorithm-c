#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 10

typedef struct item
{
    int data;
} Item;

typedef struct list
{
    Item *items; // 指向数据元素的基地址
    int length;  //线性表长度
} SqList;

void initSqList(SqList *L);
void insertSqList(SqList *L, int pos, Item e);
void showSqList(SqList *L);
int SeqSearch(SqList *L, int key);

int main(void)
{
    SqList L;
    initSqList(&L);
    insertSqList(&L, 0, (Item){36});
    insertSqList(&L, 0, (Item){60});
    insertSqList(&L, 0, (Item){89});
    insertSqList(&L, 0, (Item){56});
    insertSqList(&L, 0, (Item){32});
    insertSqList(&L, 0, (Item){45});
    insertSqList(&L, 0, (Item){7});
    insertSqList(&L, 0, (Item){15});
    insertSqList(&L, 0, (Item){13});
    insertSqList(&L, 0, (Item){9});
    showSqList(&L);
    printf("pos: %d\n", SeqSearch(&L, 1));
    return 0;
}

// 初始化线性表
void initSqList(SqList *L)
{
    L->items = (Item *)malloc(sizeof(Item) * MAX_LIST_SIZE);
    if (L->items == NULL)
    {
        printf("List Init Error!\n");
        exit(0);
    }
    else
    {
        L->length = 0;
    }
}

// 插入元素
void insertSqList(SqList *L, int pos, Item e)
{
    if (L->length >= MAX_LIST_SIZE)
    {
        printf("List full, can not insert!\n");
        exit(0);
    }
    else if (pos < 0 || pos > L->length)
    {
        printf("Illegal insert position\n");
    }
    else
    {
        for (int i = L->length; i > pos; i--)
        {
            L->items[i] = L->items[i - 1];
        }
        L->items[pos] = e;
        L->length++;
    }
}

// 打印线性表
void showSqList(SqList *L)
{
    for (int i = 0; i < L->length; i++)
    {
        printf("第%d个元素: data=%d\n", i, L->items[i].data);
    }
}

// 顺序查找
int SeqSearch(SqList *L, int key)
{
    int i = 0;
    while (i < L->length && L->items[i].data != key)
        i++;
    if (i >= L->length)
    {
        printf("not found!!!\n");
        return -1;
    }
    else
    {
        printf("find: %d\n", L->items[i].data);
        return i;
    }
}
