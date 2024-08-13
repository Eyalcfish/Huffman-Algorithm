#include <stdio.h>
#include <malloc.h>

struct Root {
    int value;
    struct Root* left;
    struct Root* right;
} typedef root;

root *makeTree(int val) {
    root *ret = (root*) malloc(sizeof(root));
    ret->right = NULL;
    ret->left = NULL;
    ret->value = val;
    return ret;
}

root *inputTree(root* head,int value) {
    if(value > head->value) {
        if(head->right != NULL){
            return inputTree(head->right,value);
        }
        head->right = makeTree(value);
        return head->right;
    }
    if(head->left != NULL){
        return inputTree(head->left,value);
    }
    head->left = makeTree(value);
    return head->left;
}

void printTree(root *head) {
    if(head->left != NULL) {
        printTree(head->left);
    }
    printf("%d\n",head->value);
    if(head->right != NULL) {
        printTree(head->right);
    }
}