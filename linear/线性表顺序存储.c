#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 10

const int N = 5e5 + 7;

typedef struct item
{
    double coef; //项数
    int exp;     // 系数
} Item;

typedef struct list
{
    Item *items; // 指向数据元素的基地址
    int length;  //线性表长度
} SqList;

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
        printf("第%d个元素：coef=%lf exp=%d\n", i, L->items[i].coef, L->items[i].exp);
    }
}

// 按位序查找
Item *getElement(SqList *L, int pos)
{
    if (pos >= L->length || pos < 0)
    {
        printf("Illegal get element position!");
        exit(0);
    }
    return &(L->items[pos]);
}

int main(void)
{
    SqList L;
    initSqList(&L);
    insertSqList(&L, 0, (Item){1.2, 3});
    insertSqList(&L, 1, (Item){1.3, 3});
    insertSqList(&L, 2, (Item){11, 9});
    insertSqList(&L, 2, (Item){24, 4});
    insertSqList(&L, 2, (Item){32, 7});
    insertSqList(&L, 2, (Item){32.5, 9});
    showSqList(&L);
    Item *item = getElement(&L, -1);
    printf("%lf, %d", item->coef, item->exp);
    return 0;
}