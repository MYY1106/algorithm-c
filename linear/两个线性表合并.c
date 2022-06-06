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

/* ��ʼ��˳���L */
void ListInitiate(SeqList *L)
{
    L->size = 0; /* �����ʼ����Ԫ�ظ��� */
}

/* ����˳���L�ĵ�ǰ����Ԫ�ظ��� */
int ListLength(SeqList L)
{
    return L.size;
}

/* ��˳���L��λ��i��0 �� i �� size��ǰ��������Ԫ��ֵx */
/* ����ɹ�����1������ʧ�ܷ���0 */
int ListInsert(SeqList *L, int i, DataType x)
{
    int j;
    if (L->size >= MaxSize)
    {
        printf("˳��������޷�����! \n");
        return 0;
    }
    else if (i < 0 || i > L->size)
    {
        printf("����i���Ϸ�! \n");
        return 0;
    }
    else
    {
        for (j = L->size - 1; j >= i; j--)
            L->list[j + 1] = L->list[j]; /* Ϊ������׼�� */
        L->list[i] = x;                  /* ���� */
        L->size++;                       /* Ԫ�ظ�����1 */
        return 1;
    }
}

/* ɾ��˳���L��λ��i��0 �� i �� size - 1��������Ԫ��ֵ����ŵ�����x�� */
/* ɾ���ɹ�����1��ɾ��ʧ�ܷ���0 */
int ListDelete(SeqList *L, int i, DataType *x)
{
    int j;
    if (L->size <= 0)
    {
        printf("˳����ѿ�������Ԫ�ؿ�ɾ! \n");
        return 0;
    }
    else if (i < 0 || i > L->size - 1)
    {
        printf("����i���Ϸ�");
        return 0;
    }
    else
    {
        *x = L->list[i]; /* ����ɾ����Ԫ�ص�����x�� */
        for (j = i + 1; j <= L->size - 1; j++)
            L->list[j - 1] = L->list[j]; /* ����ǰ�� */
        L->size--;                       /* ����Ԫ�ظ�����1 */
        return 1;
    }
}

/*ȡ˳���L�е�i������Ԫ�ص�ֵ����x�У��ɹ��򷵻�1��ʧ�ܷ���0*/
int ListGet(SeqList L, int i, DataType *x)
{
    if (i < 0 || i > L.size - 1)
    {
        printf("����i���Ϸ�! \n");
        return 0;
    }
    else
    {
        *x = L.list[i];
        return 1;
    }
}

/* ��ӡ˳��� */
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

/* �ϲ���������� */
/* ��Lb��Ԫ�ز��뵽La */
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