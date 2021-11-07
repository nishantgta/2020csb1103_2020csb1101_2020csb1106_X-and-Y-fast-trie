#include <iostream>

int MAX(int x, int y) {
    return (x > y) ? x : y;
}

//Declaring a structure for node of binary tree
struct thnode {
    int key;
    struct thnode* left;
    struct thnode* right;
};
typedef struct thnode* tnode;

// tnode root = NULL;

//Function to allocate new node for binary tree
tnode getnode(int data) {
    tnode temp = (tnode)malloc(sizeof(struct thnode));
    temp->key = data;
    temp->left = NULL;
    temp->right = NULL;
}

//Function to get height of the subtree t
int height(tnode t) {
    if (t == NULL)
        return -1;

    return MAX(height(t->left), height(t->right)) + 1;
}

//Funcion for RR rotation
tnode rrRotate(tnode a) {
    tnode b = a->right;
    a->right = b->left;
    b->left = a;
    return b;
}

//Funcion for LL rotation
tnode llRotate(tnode a) {
    tnode b = a->left;
    a->left = b->right;
    b->right = a;
    return b;
}

//Function to get balance factor of a subtree
int getBalance(tnode x){
    return height(x->left) - height(x->right);
}

//Function to add an element to the AVL tree and balance it accordingly
tnode addToTree(tnode p, int data) {
    if (p == NULL) {
        return getnode(data);
    }
    if (data < p->key) {
        p->left = addToTree(p->left, data);
    }
    else if (data > p->key) {
        p->right = addToTree(p->right, data);
    }
    else
        return p;

    int balance = getBalance(p);

    // LL Imbalance
    if (balance > 1 && data < p->left->key)
        return llRotate(p);

    // RR Imbalance
    if (balance < -1 && data > p->right->key)
        return rrRotate(p);

    // LR Imbalance
    if (balance > 1 && data > p->left->key) {
        p->left = rrRotate(p->left);
        return llRotate(p);
    }

    // RL Imbalance
    if (balance < -1 && data < p->right->key) {
        p->right = llRotate(p->right);
        return rrRotate(p);
    }

    return p;
}

//Funtion to search an element in the AVL tree
tnode search(tnode p, int data) {
    if (p == NULL || p->key == data)
        return p;
    if (data < p->key)
        return search(p->left, data);
    else
        return search(p->right, data);
}

//Function for pre-order traverse
void preOrder(tnode t) {
    if (t != NULL) {
        printf("%d ", t->key);
        preOrder(t->left);
        preOrder(t->right);
    }
}

//Function for in order traverse
void inOrder(tnode t) {
    if (t != NULL) {
        inOrder(t->left);
        printf("%d ", t->key);
        inOrder(t->right);
    }
}

int main(int argc, char const* argv[]) {
    //Adding 0 to 24 elements
    tnode root = NULL;
    for (int i = 0; i < 25; i++) {
        root = addToTree(root, i);
    }

    //Asking the user for input and printing desired output
    printf("AVL tree constructed by inserting 0 to 24 elements\n");
    char c = '\0';
    while (c!='q'){
        printf("Enter i to insert, s to search, p to print, q to quit: ");
        fflush(stdin);
        scanf("%c", &c);
        int n;
        switch (c) {
            case 'i':
                printf("Enter a data to insert: ");
                scanf("%d", &n);
                root = addToTree(root, n);
                break;
            case 's':
                printf("Enter data you want to search: ");
                scanf("%d", &n);
                tnode s = search(root, n);
                if (s==NULL){
                    printf("Not Present\n");
                }
                else {
                    printf("Present\n");
                    printf("Balance Factor of %d is %d\n", n, getBalance(s));
                    printf("Height of %d in the AVL tree is %d\n", n, height(s));
                }
                break;
            case 'p':
                printf("Preorder sequence: ");
                preOrder(root);
                printf("\n");
                printf("Inorder sequence: ");
                inOrder(root);
                printf("\n");
                break;
            case 'q':
                break;
        }
    }

    return 0;
}
