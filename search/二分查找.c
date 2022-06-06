#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 50

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
void deleteSqList(SqList *L, int pos);
void showSqList(SqList *L);
int BinarySearch(SqList *L, int key);

int main(void)
{
    SqList L;
    initSqList(&L);
    insertSqList(&L, 0, (Item){100});
    insertSqList(&L, 0, (Item){30});
    insertSqList(&L, 0, (Item){25});
    insertSqList(&L, 0, (Item){22});
    insertSqList(&L, 0, (Item){20});
    insertSqList(&L, 0, (Item){18});
    insertSqList(&L, 0, (Item){15});
    insertSqList(&L, 0, (Item){12});
    insertSqList(&L, 0, (Item){9});
    insertSqList(&L, 0, (Item){7});
    insertSqList(&L, 0, (Item){5});
    showSqList(&L);
    printf("pos: %d\n", BinarySearch(&L, 18));
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

// 删除元素
void deleteSqList(SqList *L, int pos)
{
    if (pos >= L->length || pos < 0)
    {
        printf("Illegal delete position!");
        exit(0);
    }
    for (int i = pos; i < L->length - 1; i++)
    {
        L->items[i] = L->items[i + 1];
    }
    L->length--;
}

// 打印线性表
void showSqList(SqList *L)
{
    for (int i = 0; i < L->length; i++)
    {
        printf("第%d个元素: data=%d\n", i, L->items[i].data);
    }
}

// 二分查找
int BinarySearch(SqList *L, int key)
{
    int low = 0, high = L->length - 1;
    while (low <= high)
    {
        int pos = (low + high) / 2;
        if (key == L->items[pos].data)
        {
            printf("find: %d\n", L->items[pos].data);
            return pos;
        }
        else if (key < L->items[pos].data)
            high = pos - 1;
        else
            low = pos + 1;
    }
    printf("not found!!!\n");
    return -1;
}