#include <stdlib.h>
#include <stdio.h>

typedef char DataType;

typedef struct Node
{
    DataType data;           /*������*/
    struct Node *leftChild;  /*������ָ��*/
    struct Node *rightChild; /*������ָ��*/
} BiTreeNode;                /*���Ľṹ�嶨��*/

typedef struct stackNode
{
    BiTreeNode *val;
    struct stackNode *prev;
    struct stackNode *next;
} StackNode; // ˫������

typedef struct stack
{
    StackNode *front;
    StackNode *rear;
} Stack;

/*��ʼ��������������ͷ���*/
void Initiate(BiTreeNode **root)
{
    *root = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    (*root)->leftChild = NULL;
    (*root)->rightChild = NULL;
}

void Destroy(BiTreeNode **root)
{
    if ((*root) != NULL && (*root)->leftChild != NULL)
        Destroy(&(*root)->leftChild);

    if ((*root) != NULL && (*root)->rightChild != NULL)
        Destroy(&(*root)->rightChild);

    free(*root);
}

/*����ǰ���curr�ǿգ���curr������������Ԫ��ֵΪx���½��*/
/*ԭcurr��ָ������������Ϊ�²������������*/
/*������ɹ������²������ָ�룬���򷵻ؿ�ָ��*/
BiTreeNode *InsertLeftNode(BiTreeNode *curr, DataType x)
{
    BiTreeNode *s, *t;
    if (curr == NULL)
        return NULL;

    t = curr->leftChild; /*����ԭcurr��ָ����������ָ��*/
    s = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    s->data = x;
    s->leftChild = t; /*�²������������Ϊԭcurr��������*/
    s->rightChild = NULL;

    curr->leftChild = s;    /*�½���Ϊcurr��������*/
    return curr->leftChild; /*�����²������ָ��*/
}

/*����ǰ���curr�ǿգ���curr������������Ԫ��ֵΪx���½��*/
/*ԭcurr��ָ������������Ϊ�²������������*/
/*������ɹ������²������ָ�룬���򷵻ؿ�ָ��*/
BiTreeNode *InsertRightNode(BiTreeNode *curr, DataType x)
{
    BiTreeNode *s, *t;

    if (curr == NULL)
        return NULL;

    t = curr->rightChild; /*����ԭcurr��ָ����������ָ��*/
    s = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    s->data = x;
    s->rightChild = t; /*�²������������Ϊԭcurr��������*/
    s->leftChild = NULL;

    curr->rightChild = s;    /*�½���Ϊcurr��������*/
    return curr->rightChild; /*�����²������ָ��*/
}

//ʹ��visit(item)����ǰ�����������t
void PreOrder(BiTreeNode *t, void visit(DataType item))
{
    if (t != NULL)
    { //��С����һ������
        visit(t->data);
        PreOrder(t->leftChild, visit);
        PreOrder(t->rightChild, visit);
    }
}

//ʹ��visit(item)�����������������t
void InOrder(BiTreeNode *t, void visit(DataType item))
{
    if (t != NULL)
    { //��С����һ������
        InOrder(t->leftChild, visit);
        visit(t->data);
        InOrder(t->rightChild, visit);
    }
}

//ʹ��visit(item)�����������������t
void PostOrder(BiTreeNode *t, void visit(DataType item))
{
    if (t != NULL)
    { //��С����һ������
        PostOrder(t->leftChild, visit);
        PostOrder(t->rightChild, visit);
        visit(t->data);
    }
}

void Visit(DataType item)
{
    printf("%c ", item);
}

BiTreeNode *Search(BiTreeNode *root, DataType x) //����Ԫ��x�Ƿ��ڶ�������
{
    BiTreeNode *find = NULL;
    if (root != NULL)
    {
        if (root->data == x)
            find = root;
        else
        {
            find = Search(root->leftChild, x);
            if (find == NULL)
                find = Search(root->rightChild, x);
        }
    }
    return find;
}

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->front = NULL;
    stack->rear = NULL;
    return stack;
}

StackNode *nodeInit(BiTreeNode *data)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->val = data;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void pushStack(Stack *stack, BiTreeNode *data)
{
    // printf("���%c��ջ\n", data->data);
    StackNode *node = nodeInit(data);
    if (stack->front == NULL)
    {
        stack->front = node;
        stack->rear = node;
    }
    else
    {
        stack->rear->next = node;
        node->prev = stack->rear;
        stack->rear = node;
    }
}

void showStack(Stack *stack)
{
    StackNode *p = stack->front;
    int i = 1;
    while (p != NULL)
    {
        printf("%d: %c\n", i++, p->val->data);
        p = p->next;
    }
}

void popStack(Stack *stack)
{
    // printf("%c��ջ\n", stack->rear->val->data);
    StackNode *node = stack->rear;
    if (node->prev == NULL) //ֻʣ��һ��Ԫ��
    {
        stack->front = NULL;
        stack->rear = NULL;
    }
    else
    {
        stack->rear = node->prev;
        node->prev->next = NULL;
    }
    free(node);
}

int isStackEmpty(Stack *stack)
{
    return stack->front == NULL && stack->rear == NULL;
}

// �ǵݹ��������
void preOrderTraverse(BiTreeNode *t, void visit(DataType item))
{
    Stack *stack = createStack();
    BiTreeNode *tmpNode;
    pushStack(stack, t);
    while (!isStackEmpty(stack))
    {
        tmpNode = stack->rear->val;
        popStack(stack);
        while (tmpNode != NULL)
        {
            visit(tmpNode->data);
            if (tmpNode->rightChild != NULL)
                pushStack(stack, tmpNode->rightChild);
            tmpNode = tmpNode->leftChild;
        }
    }
}

void main(void)
{
    BiTreeNode *root, *p, *pp, *find;
    char x = 'E';

    Initiate(&root);
    p = InsertLeftNode(root, 'A');
    p = InsertLeftNode(p, 'B');
    p = InsertLeftNode(p, 'D');
    p = InsertRightNode(p, 'G');
    p = InsertRightNode(root->leftChild, 'C');
    pp = p;
    InsertLeftNode(p, 'E');
    InsertRightNode(pp, 'F');

    printf("ǰ�������");
    PreOrder(root->leftChild, Visit);
    printf("\n�ǵݹ�ǰ�������");
    preOrderTraverse(root->leftChild, Visit);
    printf("\n���������");
    InOrder(root->leftChild, Visit);
    printf("\n���������");
    PostOrder(root->leftChild, Visit);

    find = Search(root, x);
    if (find != NULL)
        printf("\n����Ԫ��%c�ڶ������� \n", x);
    else
        printf("\n����Ԫ��%c���ڶ������� \n", x);

    Destroy(&root);
}
