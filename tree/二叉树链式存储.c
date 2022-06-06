#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int boolean;
typedef struct TNode
{
    struct TNode *left;
    struct TNode *right;
    int data;
} TNode; // ��������������

TNode *createTree(boolean isRoot);
void preOrder(TNode *tree, boolean isRoot, void visit(TNode node));
void inOrder(TNode *tree, boolean isRoot, void visit(TNode node));
void postOrder(TNode *tree, boolean isRoot, void visit(TNode node));
void visit(TNode node);
void destroyTree(BTNode *tree);

int main(void)
{
    TNode *root = createTree(TRUE);
    preOrder(root, TRUE, visit);
    inOrder(root, TRUE, visit);
    postOrder(root, TRUE, visit);
    destroyTree(root);
}

TNode *createTree(boolean isRoot)
{
    int data;
    if (isRoot)
        printf("��������ڵ��ֵ��");
    scanf("%d", &data);

    if (data < 0)
        return NULL;

    TNode *tree = malloc(sizeof(TNode));
    tree->data = data;
    printf("������%d�����ӽڵ��ֵ��", data);
    tree->left = createTree(FALSE);
    printf("������%d�����ӽڵ��ֵ��", data);
    tree->right = createTree(FALSE);

    return tree;
}

void destroyTree(BTNode *tree)
{
    if (tree->left != NULL)
    {
        destroyTree(tree->left);
    }
    if (tree->right != NULL)
    {
        destroyTree(tree->right);
    }
    free(tree);
}

void preOrder(TNode *tree, boolean isRoot, void visit(TNode node))
{
    if (tree == NULL)
        return;

    if (isRoot)
        printf("���������");
    visit(*tree);
    preOrder(tree->left, FALSE, visit);
    preOrder(tree->right, FALSE, visit);
    if (isRoot)
        printf("\n");
}

void inOrder(TNode *tree, boolean isRoot, void visit(TNode node))
{
    if (tree == NULL)
        return;

    if (isRoot)
        printf("���������");
    inOrder(tree->left, FALSE, visit);
    visit(*tree);
    inOrder(tree->right, FALSE, visit);
    if (isRoot)
        printf("\n");
}

void postOrder(TNode *tree, boolean isRoot, void visit(TNode node))
{
    if (tree == NULL)
        return;

    if (isRoot)
        printf("���������");
    postOrder(tree->left, FALSE, visit);
    postOrder(tree->right, FALSE, visit);
    visit(*tree);
    if (isRoot)
        printf("\n");
}

void visit(TNode node)
{
    printf("%d ", node.data);
}