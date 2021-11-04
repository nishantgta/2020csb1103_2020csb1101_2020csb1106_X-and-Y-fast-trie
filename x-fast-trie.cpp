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

int _pow(int a, int b)
{
   if(!b)return 1;
   int temp = _pow(a, b/2);
   temp = (temp * temp);
   if(b%2)return (a * temp);
   return temp;
}

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

struct node* find(int x,int w,vector<unordered_map<int,node*>> hash){
    if(hash[w].find(x) == hash[w].end()){
      return NULL;
    }
    return hash[w][x];
}

struct node* successor(int x, int w, vector<unordered_map<int,node*>> hash){
    int l, h, m, pre ;
    l = 0 ;
    h = w + 1 ;
    struct node *temp = NULL ;        
    
    // Binary search of levels
    while( h - l > 1){
        m = (l + h)/2;
        pre = x / _pow(2, w - m);  //this will store common prefix upto mid level, 
        if(hash[m].find(pre) == hash[m].end()){
            h = m ;//common prefix maybe in the upward section of mid
        }
        else{
            l = m ;
            temp = hash[m][pre] ;  //aage jaane ke liye root lena padega             
        }
    }
    
    if( temp == NULL || temp-> level == 0){
        return NULL;
    }

    if(temp->level == w){
        return temp ;
    }

    if((x / _pow(2, w - temp->level -1)) & 1){
        temp = temp->right ;
    }else{
        temp = temp->left ;
    }

    if(temp->data < x){
        return temp->right;
    }
    return temp;
}

struct node* predecessor(int x, int w, vector<unordered_map<int,node*>> hash){
    int l, h, m, pre ;
    l = 0 ;
    h = w + 1 ;
    struct node *temp = NULL ;        
    
    // Binary search of levels
    while( h - l > 1){
        m = (l + h)/2;
        pre = x / _pow(2, w - m);  //this will store common prefix upto mid level, 
        if(hash[m].find(pre) == hash[m].end()){
            h = m ;//common prefix maybe in the upward section of mid
        }
        else{
            l = m ;
            temp = hash[m][pre] ;  //aage jaane ke liye root lena padega             
        }
    }
    
    if( temp == NULL || temp-> level == 0){
        return NULL;
    }

    if(temp->level == w){
        return temp ;
    }

    if((x / _pow(2, w - temp->level -1)) & 1){
        temp = temp->right ;
    }else{
        temp = temp->left ;
    }

    if(temp->data > x){
        return temp->left;
    }
    return temp;
}

int main(){
    int w , u;
    vector<unordered_map<int,node*>> hash;
    cin >> u ;
    w= bitCount(u);
    hash.assign(w+1,unordered_map<int,node*>());
    struct node* root = new node();
    root->level=0;
    hash[0][0] = root ;
}