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
        if(root->left==NULL){
            root=root->left;
        }
        else{
            root=root->right;   
        }
    }
    return root;
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

struct node* find(int x,int w,vector<unordered_map<int,node*>> &hash){
    if(hash[w].find(x) == hash[w].end()){
      return NULL;
    }
    return hash[w][x];
}

struct node* successor(int x, int w, vector<unordered_map<int,node*>> &hash){
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

struct node* predecessor(int x, int w, vector<unordered_map<int,node*>> &hash){
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

void insert_node(int x, int w, vector<unordered_map<int,node*>> &hash){
    struct node *hash_node = new node() ;
    hash_node->data = x ;
    hash_node->level = w ;   
    
    struct node *p = predecessor(x,w,hash);
    struct node *s = successor(x,w,hash);
    if(p != NULL){
        if(p->level != w){
            cout << "Unexpected level" << "\n" ; //revisit this
        }
        hash_node->right = p->right ;
        p->right = hash_node ;
        hash_node->left = p ;
    }

    if(s != NULL){
        if(s->level != w){
            cout << "Unexpected level" << "\n" ; //revisit this
        }
        hash_node->left = s->left ;
        s->left = hash_node ;
        hash_node->right = s ;
    }
    
    
    int level = 1, pre;
    while(level!=w){
        pre = x / _pow(2,w-level);
        if(hash[level].find(pre) == hash[level].end()){
            struct node *inner = new node();
            inner->level = level;
            hash[level][pre] = inner;
            if(pre & 1){
                hash[level-1][pre/2]->right = inner;
            }
            else{
                hash[level-1][pre/2]->left = inner ;
            }
        }
        ++level;
    }
    hash[w][x] = hash_node;
    // establishing connection between last and second last level
    if(x & 1){
        hash[w-1][x/2]->right = hash_node;
    }
    else{
        hash[w-1][x/2]->left = hash_node;
    }

    //threading
    pre = x ;
    level = w - 1 ;
    // level
    while(level != 0){
        pre = pre/2 ;
        if(hash[level][pre]->left == NULL)
            hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w) ;
        else if(hash[level][pre]->right == NULL)
            hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left,w) ;
        --level ;
    }   

    if(hash[0][0]->left == NULL){
        hash[0][0]->left = get_Leftmost_Node(hash[0][0]->right,w);
    }
    if(hash[0][0]->right == NULL){
        hash[0][0]->right = get_Rightmost_Node(hash[0][0]->left,w);
    }
}

void delete_node(int x,int w, vector<unordered_map<int,node*>> &hash){
    struct node* temp = find(x,w,hash);
    struct node* s = successor(x,w,hash);
    struct node* p = predecessor(x,w,hash);
    p->right = s ;
    s->left = p ;

    int pre = x ;
    int pprev;
    int level = w - 1 ;
    while(level != 0){
        pprev=pre;
        pre = pre/2 ;   
        temp=hash[level+1][pprev];
        if(hash[level][pre]->left->data==2*hash[level][pre]->data && hash[level][pre]->right->data==(2*hash[level][pre]->data) + 1)
        {   
            hash[level+1][pprev]=NULL;
            //you have reached branch node :)
            break;
        }
        else{
            hash[level+1][pprev]=NULL;
        }
        --level ;
    } 
    pre=pprev;
    while(level != 0){
    pre = pre/2 ;
    if(hash[level][pre]->left == NULL)
        hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w) ;
    else if(hash[level][pre]->right == NULL)
        hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left,w) ;
    --level ;
    }   
    
}

int main(){
    int w , u;
    vector<unordered_map<int,node*>> hash;
    cout<<"Enter the size of the universe"<<"\n";
    cin >> u ;
    w= bitCount(u);
    hash.assign(w+1,unordered_map<int,node*>());
    struct node* root = new node();
    root->level=0;
    hash[0][0] = root ;
    
    insert_node(5,w,hash);
    insert_node(11,w,hash);
    insert_node(12,w,hash);
    insert_node(1,w,hash);
    insert_node(6,w,hash);
    insert_node(7,w,hash);

    struct node *temp = successor(2,w,hash);
    if(temp!=NULL){
        cout<<temp->data<<"\n";
    }

    temp = predecessor(2,w,hash);
    if(temp!=NULL){
        cout<<temp->data<<"\n";
    }
    delete_node(5,w,hash);
    temp = predecessor(2,w,hash);
    if(temp!=NULL){
        cout<<temp->data<<"\n";
    }
}