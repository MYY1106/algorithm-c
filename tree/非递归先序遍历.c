#include <stdlib.h>
#include <stdio.h>

typedef char DataType;

typedef struct Node
{
    DataType data;           /*数据域*/
    struct Node *leftChild;  /*左子树指针*/
    struct Node *rightChild; /*右子树指针*/
} BiTreeNode;                /*结点的结构体定义*/

typedef struct stackNode
{
    BiTreeNode *val;
    struct stackNode *prev;
    struct stackNode *next;
} StackNode; // 双向链表

typedef struct stack
{
    StackNode *front;
    StackNode *rear;
} Stack;

/*初始化创建二叉树的头结点*/
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

/*若当前结点curr非空，在curr的左子树插入元素值为x的新结点*/
/*原curr所指结点的左子树成为新插入结点的左子树*/
/*若插入成功返回新插入结点的指针，否则返回空指针*/
BiTreeNode *InsertLeftNode(BiTreeNode *curr, DataType x)
{
    BiTreeNode *s, *t;
    if (curr == NULL)
        return NULL;

    t = curr->leftChild; /*保存原curr所指结点的左子树指针*/
    s = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    s->data = x;
    s->leftChild = t; /*新插入结点的左子树为原curr的左子树*/
    s->rightChild = NULL;

    curr->leftChild = s;    /*新结点成为curr的左子树*/
    return curr->leftChild; /*返回新插入结点的指针*/
}

/*若当前结点curr非空，在curr的右子树插入元素值为x的新结点*/
/*原curr所指结点的右子树成为新插入结点的右子树*/
/*若插入成功返回新插入结点的指针，否则返回空指针*/
BiTreeNode *InsertRightNode(BiTreeNode *curr, DataType x)
{
    BiTreeNode *s, *t;

    if (curr == NULL)
        return NULL;

    t = curr->rightChild; /*保存原curr所指结点的右子树指针*/
    s = (BiTreeNode *)malloc(sizeof(BiTreeNode));
    s->data = x;
    s->rightChild = t; /*新插入结点的右子树为原curr的右子树*/
    s->leftChild = NULL;

    curr->rightChild = s;    /*新结点成为curr的右子树*/
    return curr->rightChild; /*返回新插入结点的指针*/
}

//使用visit(item)函数前序遍历二叉树t
void PreOrder(BiTreeNode *t, void visit(DataType item))
{
    if (t != NULL)
    { //此小段有一处错误
        visit(t->data);
        PreOrder(t->leftChild, visit);
        PreOrder(t->rightChild, visit);
    }
}

//使用visit(item)函数中序遍历二叉树t
void InOrder(BiTreeNode *t, void visit(DataType item))
{
    if (t != NULL)
    { //此小段有一处错误
        InOrder(t->leftChild, visit);
        visit(t->data);
        InOrder(t->rightChild, visit);
    }
}

//使用visit(item)函数后序遍历二叉树t
void PostOrder(BiTreeNode *t, void visit(DataType item))
{
    if (t != NULL)
    { //此小段有一处错误
        PostOrder(t->leftChild, visit);
        PostOrder(t->rightChild, visit);
        visit(t->data);
    }
}

void Visit(DataType item)
{
    printf("%c ", item);
}

BiTreeNode *Search(BiTreeNode *root, DataType x) //需找元素x是否在二叉树中
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
    // printf("结点%c入栈\n", data->data);
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
    // printf("%c出栈\n", stack->rear->val->data);
    StackNode *node = stack->rear;
    if (node->prev == NULL) //只剩下一个元素
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

// 非递归先序遍历
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

    printf("前序遍历：");
    PreOrder(root->leftChild, Visit);
    printf("\n非递归前序遍历：");
    preOrderTraverse(root->leftChild, Visit);
    printf("\n中序遍历：");
    InOrder(root->leftChild, Visit);
    printf("\n后序遍历：");
    PostOrder(root->leftChild, Visit);

    find = Search(root, x);
    if (find != NULL)
        printf("\n数据元素%c在二叉树中 \n", x);
    else
        printf("\n数据元素%c不在二叉树中 \n", x);

    Destroy(&root);
}
