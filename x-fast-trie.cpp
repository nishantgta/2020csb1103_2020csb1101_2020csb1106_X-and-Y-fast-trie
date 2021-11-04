#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

struct node {
    int data;
    int level;
    struct node * left, *right ;
    
    node(){
        level=-1;
        left=NULL;
        right=NULL;
    }
};

int bitCount(int x){
    int ans=0;
    while(x>0){
        x=x/2;
        ans++;
    }
    return ans;
}

int left_children(int x){
    return 2 * x ;
}

int right_children(int x){
    return 2 * x + 1 ;
}

struct node* get_Leftmost_Node(struct node* root,int w){
    while(root->level!= w){
        if(root->left=NULL){
            root=root->left;
        }
        else{
            root=root->right;   
        }
        return root;
    }
}

struct node* get_Rightmost_Node(struct node* root, int w){
    while(root->level!=w){
        if(root->right != NULL){
            root = root->right ;
        }else{
            root = root->left ;
        }
    }
    return root ;
}



int main(){

}