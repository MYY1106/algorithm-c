#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int weight;
    struct node *left;
    struct node *right;
} BTNode; // ��������������

BTNode *createTree(int depth);
void preOrder(BTNode *tree, int depth, void visit(BTNode node, int depth));
void inOrder(BTNode *tree, int depth, void visit(BTNode node, int depth));
void postOrder(BTNode *tree, int depth, void visit(BTNode node, int depth));
void visit(BTNode node, int depth);
void destroyTree(BTNode *tree);

int wpl = 0; // �洢wpl

int main(void)
{
    BTNode *root = createTree(0);

    preOrder(root, 0, visit); // �������
    printf("�������wpl:%d\n", wpl);

    wpl = 0;
    inOrder(root, 0, visit); //�������
    printf("�������wpl:%d\n", wpl);

    wpl = 0;
    postOrder(root, 0, visit); // �������
    printf("�������wpl:%d\n", wpl);

    destroyTree(root);

    return 0;
}

// ����������
// depth ���
BTNode *createTree(int depth)
{
    int weight;
    if (!depth)
        printf("��������ڵ��Ȩֵ��");
    scanf("%d", &weight);

    if (weight < 0) // ȨֵΪ�����򲻴����½��
        return NULL;

    BTNode *tree = (BTNode *)malloc(sizeof(BTNode));
    tree->weight = weight;
    printf("������ȨֵΪ%d�����ӽڵ��Ȩֵ��", weight);
    tree->left = createTree(depth + 1); // ����������
    printf("������ȨֵΪ%d�����ӽڵ��Ȩֵ��", weight);
    tree->right = createTree(depth + 1); // ����������

    return tree;
}

// ���ٶ�����
// *tree ָ����������ڵ��ָ��
void destroyTree(BTNode *tree)
{
    if (tree->left != NULL)
    {
        destroyTree(tree->left); // ����������
    }
    if (tree->right != NULL)
    {
        destroyTree(tree->right); // ����������
    }
    free(tree);
}

// �������
// *tree ָ����������ڵ��ָ��
// depth ���
// visit ���ʽ�㺯��
void preOrder(BTNode *tree, int depth, void visit(BTNode node, int depth))
{
    if (tree == NULL)
        return;

    visit(*tree, depth);                     // ���ʽ��
    preOrder(tree->left, depth + 1, visit);  // �������������
    preOrder(tree->right, depth + 1, visit); // �������������
}

// �������
// *tree ָ����������ڵ��ָ��
// depth ���
// visit ���ʽ�㺯��
void inOrder(BTNode *tree, int depth, void visit(BTNode node, int depth))
{
    if (tree == NULL)
        return;

    inOrder(tree->left, depth + 1, visit);  // �������������
    visit(*tree, depth);                    // ���ʽ��
    inOrder(tree->right, depth + 1, visit); // �������������
}

// �������
// *tree ָ����������ڵ��ָ��
// depth ���
// visit ���ʽ�㺯��
void postOrder(BTNode *tree, int depth, void visit(BTNode node, int depth))
{
    if (tree == NULL)
        return;

    postOrder(tree->left, depth + 1, visit);  // �������������
    postOrder(tree->right, depth + 1, visit); // �������������
    visit(*tree, depth);                      // ���ʽ��
}

// ���ʽ��
// node ���
// depth ���
void visit(BTNode node, int depth)
{
    if (node.left == NULL && node.right == NULL)
    {
        wpl += node.weight * depth; // ����
    }
}
