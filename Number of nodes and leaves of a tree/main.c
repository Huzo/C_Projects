#include <stdio.h>
#include <stdlib.h>

/*This is a program that counts the number of leaves, nodes and full nodes of a tree. */

typedef struct Node {
    int data;
    struct Node *right;
    struct Node *left;
} node;

typedef struct BinarySearchTree {
    struct Node *root;
    int count;
} BST;

node *createNode(int inpdata) {
    node *nodeToAdd;
    nodeToAdd = (node *) malloc(sizeof(node));
    nodeToAdd->data = inpdata;
    return nodeToAdd;
}

void Insert(node **root, int inpdata) {//root of the tree should be passed here
    if (*root == NULL) {//found the place to insert
        *root = createNode(inpdata);
    } else if (inpdata < (*root)->data) {
        Insert(&((*root)->left), inpdata);
    } else {
        Insert(&((*root)->right), inpdata);
    }
}

int leafCount(node *isLeaf) {//root of the tree should be passed.
    if (isLeaf == NULL) {
        return 0;
    }
    if (isLeaf->left == NULL && isLeaf->right == NULL) {
        return 1;//found a leaf.
    } else {
        return leafCount(isLeaf->left) + leafCount(isLeaf->right);//return the total no of leaves of both subtrees.
    }
}

int fullNodeCount(node *isFull) {//root of the tree should be passed.
    if (isFull->left == NULL || isFull->right == NULL) {
        return 0;
    }

    int count = 0;
    if (isFull->left != NULL && isFull->right != NULL) {
        count++;
        count += fullNodeCount(isFull->left) + fullNodeCount(isFull->right);
        return count;//found a full node.
    }

}

int main() {
    BST *tree;
    tree = (BST *) malloc(sizeof(BST));
    tree->root = NULL;
    tree->count = 0;

    FILE *fp;
    int inpdata;
    fp = fopen("DataIn.txt", "r");

    while (fscanf(fp, " %d", &inpdata) == 1) {
        Insert(&(tree->root), inpdata);
        tree->count++;
    }
    printf("The number of nods:%d, ", tree->count);//The number of nodes
    printf("The number of leaves:%d, ", leafCount(tree->root));//The number of leaves
    printf("The number of full nodes:%d", fullNodeCount(tree->root));//The number of full nodes
    fclose(fp);
    return 0;
}
