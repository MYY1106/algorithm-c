#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int weight;
    struct node *left;
    struct node *right;
} BTNode; // 二叉树的链表结点

BTNode *createTree(int depth);
void preOrder(BTNode *tree, int depth, void visit(BTNode node, int depth));
void inOrder(BTNode *tree, int depth, void visit(BTNode node, int depth));
void postOrder(BTNode *tree, int depth, void visit(BTNode node, int depth));
void visit(BTNode node, int depth);
void destroyTree(BTNode *tree);

int wpl = 0; // 存储wpl

int main(void)
{
    BTNode *root = createTree(0);

    preOrder(root, 0, visit); // 先序遍历
    printf("先序遍历wpl:%d\n", wpl);

    wpl = 0;
    inOrder(root, 0, visit); //中序遍历
    printf("中序遍历wpl:%d\n", wpl);

    wpl = 0;
    postOrder(root, 0, visit); // 后序遍历
    printf("后序遍历wpl:%d\n", wpl);

    destroyTree(root);

    return 0;
}

// 创建二叉树
// depth 深度
BTNode *createTree(int depth)
{
    int weight;
    if (!depth)
        printf("请输入根节点的权值：");
    scanf("%d", &weight);

    if (weight < 0) // 权值为负，则不创建新结点
        return NULL;

    BTNode *tree = (BTNode *)malloc(sizeof(BTNode));
    tree->weight = weight;
    printf("请输入权值为%d的左子节点的权值：", weight);
    tree->left = createTree(depth + 1); // 创建左子树
    printf("请输入权值为%d的右子节点的权值：", weight);
    tree->right = createTree(depth + 1); // 创建右子树

    return tree;
}

// 销毁二叉树
// *tree 指向二叉树根节点的指针
void destroyTree(BTNode *tree)
{
    if (tree->left != NULL)
    {
        destroyTree(tree->left); // 销毁左子树
    }
    if (tree->right != NULL)
    {
        destroyTree(tree->right); // 销毁右子树
    }
    free(tree);
}

// 先序遍历
// *tree 指向二叉树根节点的指针
// depth 深度
// visit 访问结点函数
void preOrder(BTNode *tree, int depth, void visit(BTNode node, int depth))
{
    if (tree == NULL)
        return;

    visit(*tree, depth);                     // 访问结点
    preOrder(tree->left, depth + 1, visit);  // 先序遍历左子树
    preOrder(tree->right, depth + 1, visit); // 先序遍历右子树
}

// 中序遍历
// *tree 指向二叉树根节点的指针
// depth 深度
// visit 访问结点函数
void inOrder(BTNode *tree, int depth, void visit(BTNode node, int depth))
{
    if (tree == NULL)
        return;

    inOrder(tree->left, depth + 1, visit);  // 中序遍历左子树
    visit(*tree, depth);                    // 访问结点
    inOrder(tree->right, depth + 1, visit); // 中序遍历右子树
}

// 后序遍历
// *tree 指向二叉树根节点的指针
// depth 深度
// visit 访问结点函数
void postOrder(BTNode *tree, int depth, void visit(BTNode node, int depth))
{
    if (tree == NULL)
        return;

    postOrder(tree->left, depth + 1, visit);  // 后序遍历左子树
    postOrder(tree->right, depth + 1, visit); // 后序遍历右子树
    visit(*tree, depth);                      // 访问结点
}

// 访问结点
// node 结点
// depth 深度
void visit(BTNode node, int depth)
{
    if (node.left == NULL && node.right == NULL)
    {
        wpl += node.weight * depth; // 计算
    }
}
