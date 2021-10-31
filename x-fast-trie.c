#include<stdio.h>
#include <stdlib.h>

struct Node{
    int level;
    int key;
    struct Node *left, *right;
};

struct Node *newNode(int key) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->key = key;
  node->level = -1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Defining the node containing the data, pointer to previous element and pointer to next element
struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

// Implementing the insert function
void insert(struct node* hash[],int value,int size)
{
    //create a new node with value
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    int key;
    //calculating hash key
    if(value<0){
      value=-value-1;
      key = (size-1)-(value%size);
    }
    else{
      key = value % size;
    }

    //check if hash[key] is empty
    if(hash[key] == NULL){
        hash[key] = newNode;
    }
    //collision condition
    else
    {
        struct node *temp = hash[key];
        hash[key]=newNode;
        newNode->next=temp;
        temp->prev = newNode;
    }
}

// Implementing the search function
int search(struct node* hash[],int value,int size){
    int key;
    //calculating hash key
    if(value<0){
      // For negative values
      value=-value-1;
      key = (size-1)-(value%size);
      value=-(value+1);
    }
    else{
      key = value % size;
    }
    struct node *temp = hash[key];
    // Iterating the list for the desired value
    while (temp!=NULL)
    { 
      if(temp->data==value){
        return key;
      }
      temp=temp->next;
    }
    // If element doesn't exist
    return -1;
}

// Implementing the delete function
void delete(struct node* hash[],int value,int size){
  int srhval;
  srhval=search(hash,value,size);
  // Checking if the element exists
  if(srhval>-1){
     struct node* temp=hash[srhval];
     // Get to the point where data value match key
     while(temp->data!=value){
       temp=temp->next;
     }
     // If previous and next pointer are NULL
     if(temp->next==NULL && temp->prev==NULL){
       hash[srhval]=NULL;
       return;
     }
     // If next pointer is NULL
     else if(temp->next==NULL){
       temp=temp->prev;
       temp->next=NULL;
       return;
     }
     // If previous pointer is NULL
     else if(temp->prev==NULL){
       temp=temp->next;
       hash[srhval]=temp;
       temp->prev=NULL;
       return;
     }
     // If both pointers are not NULL
     else{
       temp->prev->next=temp->next;
       temp->next->prev=temp->prev;
       return;
     }
  }
  else{
    printf("The element you entered doesn't exist.\n");
    return;
  }
}

// Implementing the display(print) function
void display(struct node* hash[],int size)
{   
    for(int i = 0; i < size; i++)
    {
        struct node *temp = hash[i];
        printf("index %d: ",i);
        // If that linked list is NULL
        if(temp==NULL){
            printf("NULL\n");
            continue;
        }
        // Printing the entire linked list
        while(temp!=NULL)
        {
            printf("%d ",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int getDigitCount(int x){
    int count = 0;
    for(; x > 0; x >>= 1, ++count);
    return count;
}

int leftChild(int x){
    return (x << 1);
}

int rightChild(int x){
    return ((x << 1) | 1);
}

struct Node *getLeftmostLeaf(struct Node *parent,int w){
    while(parent->level != w){
        if(parent->left != NULL)
            parent = parent->left;
        else
            parent = parent->right;
    }
    return parent;
}

struct Node *getRightmostLeaf(struct Node *parent,int w){
    while(parent->level != w){
        if(parent->right != NULL)
            parent = parent->right;
        else
            parent = parent->left;
        }
    return parent;
}

struct XFastTrie{
    int w;
};


