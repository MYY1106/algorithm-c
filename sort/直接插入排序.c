#include <stdio.h>
#include <stdlib.h>

#define MAX_LIST_SIZE 10

typedef struct student
{
    char name[8];
    int score;
} Item;

typedef struct list
{
    Item *students; // ָ������Ԫ�صĻ���ַ
    int length;     //���Ա���
} SqList;

void initSqList(SqList *L);
void insertSqList(SqList *L, int pos, Item e);
void deleteSqList(SqList *L, int pos);
void showSqList(SqList *L);
void insertSort(SqList *L);

int main(void)
{
    SqList L;
    initSqList(&L);
    insertSqList(&L, 0, (Item){"myy", 7});
    insertSqList(&L, 0, (Item){"ddd", 10});
    insertSqList(&L, 0, (Item){"sdf", 10});
    showSqList(&L);
    insertSort(&L);
    showSqList(&L);
    return 0;
}

// ��ʼ�����Ա�
void initSqList(SqList *L)
{
    L->students = (Item *)malloc(sizeof(Item) * MAX_LIST_SIZE);
    if (L->students == NULL)
    {
        printf("List Init Error!\n");
        exit(0);
    }
    else
    {
        L->length = 0;
    }
}

// ����Ԫ��
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
            L->students[i] = L->students[i - 1];
        }
        L->students[pos] = e;
        L->length++;
    }
}

// ɾ��Ԫ��
void deleteSqList(SqList *L, int pos)
{
    if (pos >= L->length || pos < 0)
    {
        printf("Illegal delete position!");
        exit(0);
    }
    for (int i = pos; i < L->length - 1; i++)
    {
        L->students[i] = L->students[i + 1];
    }
    L->length--;
}

// ��ӡ���Ա�
void showSqList(SqList *L)
{
    printf("-------------------\n");
    int rank = 0;
    int tmpScore = -1;
    for (int i = 0; i < L->length; i++)
    {
        rank = tmpScore == L->students[i].score ? rank : ++rank;
        tmpScore = L->students[i].score;
        printf("��%d����%s-%d\n", rank, L->students[i].name, L->students[i].score);
    }
    printf("-------------------\n");
}

void insertSort(SqList *L)
{
    for (int i = 1; i < L->length; i++)
    {
        Item tmpStu = L->students[i];
        int j;
        for (j = i - 1; j >= 0; j--)
        {
            if (L->students[j].score > tmpStu.score)
                L->students[j + 1] = L->students[j];
            else
                break;
        }
        L->students[j + 1] = tmpStu;
    }
}