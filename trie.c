#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct trienode{   //this is my trie node
    char data ;
    struct trienode *child[26] ;
    int isleaf ;
};

//to create my new trie node
struct trienode *getnode(char data){
    struct trienode *node = (struct trienode *)malloc(sizeof(struct trienode)) ;
    int i ;
    for(i = 0; i<26; i++){
        node->child[i] = NULL ;
    }
    node->isleaf = 0 ;
    node->data = data ;
    return node ;
}

//to delete a whole a trie node(gayab hi karna hai usko to)
void free_trienode(struct trienode *node)
{
    for(int i = 0; i < 26; i++){
        if(node->child[i] != NULL){
            free_trienode(node->child[i]) ;
        }
        else{
            continue ;
        }
    }
    free(node) ;
}

//insert trie will take pointer to the root node, 
struct trienode *insert_trie(struct trienode *root, char *word){
    struct trienode *temp = root ;
    int i, index ;
    for(i = 0; word[i]!='\0'; i++){
        index = (int)word[i] - 'a' ;
        if(temp->child[index] == NULL){
            temp->child[index] = getnode(word[i]) ;
        }else{/*do nothing, the given key is already present*/}
        temp = temp->child[index] ;
    }
    temp->isleaf = 1 ;
    return root ;
}

int search_trie(struct trienode *root, char *word){
    struct trienode *temp = root ;
    int i, index ;
    for(i = 0; word[i] != '\0' ; i++){
        index = word[i] - 'a' ;
        if(temp->child[index] == NULL){
            return 0 ;
        }
        temp = temp->child[index] ;        
    }
    if(temp != NULL && temp->isleaf == 1) return 1 ;  //you have found the complete word
    return 0 ;
}

void print_trie(struct trienode *root){
    if(root == NULL) return ;
    struct trienode *temp = root ;
    printf("%c->", temp->data) ;
    for(int i = 0; i<26; i++){
        print_trie(temp->child[i]) ;
    }
}

void print_search(struct trienode *root, char *word) {
    if(search_trie(root, word) == 0){
        printf("Not Found\n") ;
    }else{
        printf("Found\n") ;
    }
}

//this is to check whether the node to be deleted ends in a leaf node or not
//we are deleting only the words which ends in a leaf node

int is_leaf_node(struct trienode *root, char *word){
    struct trienode *temp = root ;
    int i, index ;
    for (i = 0; word[i]; i++){    //(word[i] != '\0')
        index = (int)word[i] - 'a' ;
        if(temp->child[index]){
            temp = temp->child[index] ;
        }
    }
    return temp->isleaf ;
}

int check_divergence(struct trienode *root, char *common_prefix) {
    //returns the largest position in the word where branching occurs
    struct trienode *temp = root  ;
    int l = strlen(common_prefix) ;
    if(l == 0) return 0 ;

    int branch = 0, i, j ; //largest index where branching occurs

    for(i = 0; i < l ; i++){
        int index = common_prefix[i] - 'a' ;
        if(temp->child[index]){
            //if a child exists here, we will check if there is another child
            //if yes, the branch has started :)
            for(j = 0; j < 26; j++){
                if(temp->child[j] && j != index) branch = i + 1 ;                    
            }
        }
        temp = temp->child[index] ;
    }
    return branch ;
}


char *find_common_prefix(struct trienode *root, char *word){
    if(!word || word[0]=='\0')  //don't fool, you are trying to delete a non existent word
    { return NULL ;}
    int len = strlen(word) , i;
    char *common_prefix = (char *)calloc(len+1, sizeof(char)) ;
    for(i = 0; word[i] != '\0' ; i++){
        common_prefix[i] = word[i] ;
    }
    common_prefix[len] = '\0' ;
    //the common prefix is set to the word itself
    //we will go back from the deepest position, until we reach a point of branching
    //like in navroopbhai and navroopbhen, b is the point of branching

    //but if there is no branching till, bc it means that we are matching same string
    int index_branch = check_divergence(root, common_prefix) - 1 ;
    if(index_branch >= 0){
        //there is a branch and a common prefix, 
        common_prefix[index_branch] = '\0' ;
        common_prefix = (char *)realloc(common_prefix, (index_branch + 1) * sizeof(char)) ;
    }
    return common_prefix ;  //now we are returning the string with common prefix only
}

struct trienode *delete(struct trienode *root, char *word){
    if(!root){
        return NULL ;
    }
    if(!word || word[0]=='\0'){
        return root ;   //we don't need this
    }
    if(!is_leaf_node(root, word)){
        return root ;
    }
    struct trienode *temp = root ;
    char *common_prefix = find_common_prefix(root, word) ;  //we are finding common prefix 
    if(common_prefix[0] == '\0'){
        free(common_prefix) ;
        return root ;
    }
    int i ;
    for(i = 0; common_prefix[i] != '\0' ; i++){
        int index = common_prefix[i] - 'a' ;
        if(temp->child[index] != NULL){  //keep moving to the deepest point of the common prefix
            temp = temp->child[index] ;
        }
        else{
            free(common_prefix) ;
            return root ;
        }        
    }
    int len = strlen(word) ;
    //we have reached the deepest point of common prefix, delete that one which one which is in our word
    for(; i<len; i++){
        int index = word[i] - 'a' ;
        if(temp->child[index]){
            struct trienode *remaining = temp->child[index] ;
            temp->child[index] = NULL ;
            free(remaining) ;
        }
    }
    free(common_prefix) ;
    return root ;
 }



int main(){
    struct trienode *root = getnode('\0') ;
    root = insert_trie(root, "hello") ;
    root = insert_trie(root, "hi") ;
    root = insert_trie(root, "teabag") ;
    root = insert_trie(root, "teacan") ;
    print_search(root, "tea");
    print_search(root, "teabag");
    print_search(root, "teacan");
    print_search(root, "hi");
    print_search(root, "hey");
    print_search(root, "hello");
    print_trie(root);
    printf("\n");
    root = delete(root, "hello");
    printf("After deleting 'hello'...\n");
    print_search(root, "hello");
    print_trie(root) ;
    return 0 ;
}

