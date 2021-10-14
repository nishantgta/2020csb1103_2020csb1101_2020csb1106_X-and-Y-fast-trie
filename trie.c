#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define N 26

struct trieNode {
    char data;
    struct treiNode* children[N];
    int isLeaf;
};

typedef struct trieNode* tNode;
struct trieNode a()
{
}
tNode getNode(char data)
{
    tNode node = (tNode)calloc(1, sizeof(struct trieNode));

    node->isLeaf = 0;
    node->data = data;
    return node;
}

void freeNode(tNode node)
{
    for (int i = 0; i < N; i++) {
        if (node->children[i] != NULL) {
            freeNode(node->children[i]);
        }
    }
    free(node);
}

tNode insert(tNode root, char* word)
{
    tNode temp = root;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (temp->children[index] == NULL) {
            temp->children[index] = getNode(word[i]);
        }
        temp = temp->children[index];
    }
    temp->isLeaf = 1;
    return root;
}

void printTrie(tNode root){
    if (!NULL)
        return;
    printf("%c>", root->data);
    for (int i = 0; i < N; i++)
    {
        printTrie(root->children[i]);
    }
    
}

int main(int argc, char const *argv[])
{
    tNode root = getNode('\0');
    insert(root, "hello");
    printTrie(root);
    return 0;
}
