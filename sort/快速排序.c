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
void showSqList(SqList *L);
void quickSort(SqList *L, int start, int end);

int main(void)
{
    SqList L;
    initSqList(&L);
    insertSqList(&L, 0, (Item){"myy", 7});
    insertSqList(&L, 0, (Item){"dad", 10});
    insertSqList(&L, 0, (Item){"sdf", 9});
    insertSqList(&L, 0, (Item){"dqd", 435});
    insertSqList(&L, 0, (Item){"sdf", 3});
    insertSqList(&L, 0, (Item){"ddd", 10});
    insertSqList(&L, 0, (Item){"sjw", 50});
    insertSqList(&L, 0, (Item){"ddd", 23});
    insertSqList(&L, 0, (Item){"adf", 10});
    quickSort(&L, 0, L.length - 1);
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

// ��ӡ���Ա�
void showSqList(SqList *L)
{
    printf("-------------------\n");
    int rank = 0;
    int tmpScore = -1;
    for (int i = 0; i < L->length; i++)
    {
        rank = tmpScore == L->students[i].score ? rank : i + 1;
        tmpScore = L->students[i].score;
        printf("��%d����%s-%d\n", rank, L->students[i].name, L->students[i].score);
    }
    printf("-------------------\n");
}

// ref: https://blog.csdn.net/zhengqijun_/article/details/53038831 ���ͼ������������
// ��������
// *L ����ָ��
// start ���
// end �յ�
void quickSort(SqList *L, int start, int end)
{
    if (start < end)
    {
        int low = start;
        int high = end;
        Item center = L->students[low]; /* ���������center��������ĵ�һ��Ԫ�� */
        while (low < high)
        {
            /* �ҵ���centerС���������Ѹ���������� */
            while (low < high && L->students[high].score >= center.score)
                high--;
            if (low < high)
                L->students[low++] = L->students[high];

            /* �ҵ���center����������Ѹ��������ұ� */
            while (low < high && L->students[low].score <= center.score)
                low++;
            if (low < high)
                L->students[high--] = L->students[low];
        }

        /* ��center�����м� */
        L->students[low] = center;

        /* �ݹ���� */
        quickSort(L, start, low - 1);
        quickSort(L, low + 1, end);
    }
}