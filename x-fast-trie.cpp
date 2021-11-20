// Including libraries
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// Defining the node for x-fast trie containing data, level
// and a left pointer and a right pointer. It also has a default
// constructor
struct node {  //node of struct type will represent the node in our trie data structure
    int data;
    int level;
    struct node *left, *right;

    //initialising node with default values
    node() {
        level = -1;
        left = NULL;
        right = NULL;
    }
};

// Implementing power function
int _pow(int a, int b) {
    if (!b)
        return 1;
    int temp = _pow(a, b / 2);
    temp = (temp * temp);
    if (b % 2)
        return (a * temp);
    return temp;
}

// This function will find the bitcount for given size of universe
int bitCount(int x) {
    int ans = 0;
    while (x > 0) {
        x = x / 2;
        ans++;
    }
    return ans;
}

// This function will return the left child corresponding to a node
int left_children(int x) {
    return 2 * x;
}

// This function will return the right child corresponding to a node
int right_children(int x) {
    return 2 * x + 1;
}

// This will return the leftmost node of the given node
struct node* get_Leftmost_Node(struct node* root, int w) {
    // The function will keep traversing till it reaches the level w
    while (root->level != w) {
        // If left is not NULL, it will go to the left child, else right child
        if (root->left != NULL) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return root;
}

// This will return the rightmost node of the given node
struct node* get_Rightmost_Node(struct node* root, int w) {
    // The function will keep traversing till it reaches the level w
    while (root->level != w) {
        // If right is not NULL, it will go to the right child, else left child
        if (root->right != NULL) {
            root = root->right;
        }
        else {
            root = root->left;
        }
    }
    return root;
}

// This function find the key in the x-fast trie
struct node* find(int x, int w, vector<unordered_map<int, node*>>& hash) {
    if (hash[w].find(x) == hash[w].end()) {
        return NULL;
    }
    return hash[w][x];
}

// This function will return successor node in our trie corresponding to a given value
struct node* successor(int x, int w, vector<unordered_map<int, node*>>& hash) {
    int l, h, m, pre;
    l = 0;
    h = w + 1;
    struct node* temp = NULL;

    // Binary search of levels
    while (h - l > 1) {
        m = (l + h) / 2;
        pre = x / _pow(2, w - m);  //this will store common prefix upto mid level,
        if (hash[m].find(pre) == hash[m].end()) {
            h = m;  //common prefix maybe in the upward section of mid
        }
        else {
            l = m;
            temp = hash[m][pre];  //if the common prefix is in the downward section of mid,
                                  // we will change the root to the mid
        }
    }

    if (temp == NULL || temp->level == 0) {  //this means we have not yet created our trie
        return NULL;
    }

    if (temp->level == w) {  //reached at the end of our hash table
        return temp;
    }

    if ((x / _pow(2, w - temp->level - 1)) & 1) {  //choosing path after the common prefix
        temp = temp->right;
    }
    else {
        temp = temp->left;
    }

    if (temp->data < x) {  //if x is greater than temp, return the right node in our last level of hash
        return temp->right;
    }
    return temp;  //else return temp itself
}

// This function will return successor node in our trie corresponding to a given value
struct node* predecessor(int x, int w, vector<unordered_map<int, node*>>& hash) {
    int l, h, m, pre;
    l = 0;
    h = w + 1;
    struct node* temp = NULL;

    // Binary search of levels
    while (h - l > 1) {
        m = (l + h) / 2;
        pre = x / _pow(2, w - m);  //this will store common prefix upto mid level,
        if (hash[m].find(pre) == hash[m].end()) {
            h = m;  //common prefix maybe in the upward section of mid
        }
        else {
            l = m;
            temp = hash[m][pre];  //if the common prefix is in the downward section of mid,
                                  // we will change the root to the mid
        }
    }

    //this means we have not yet created our trie
    if (temp == NULL || temp->level == 0) {
        return NULL;
    }

    //reached at the last level of our x-fast
    if (temp->level == w) {
        return temp;
    }

    //choosing path after the common prefix
    if ((x / _pow(2, w - temp->level - 1)) & 1) {
        temp = temp->right;
    }
    else {
        temp = temp->left;
    }

    //if x is less than temp, return the left node in our last level of x-fast
    if (temp->data > x) {
        return temp->left;
    }
    //else return temp itself
    return temp;
}

// This function adds a key to the x-fast trie
// It will create a new node, find a suitable place for it in the existing trie and links other nodes to it.
void insert_node(int x, int w, vector<unordered_map<int, node*>>& hash) {
    struct node* hash_node = new node();  //hash node will represent the node to be inserted
    hash_node->data = x;
    hash_node->level = w;

    struct node* p = predecessor(x, w, hash);  //p will have predecessor
    struct node* s = successor(x, w, hash);    //s will have successor
    if (p != NULL) {
        if (p->level != w) {
            cout << "Unexpected level"
                 << "\n";
        }
        //To make links so that hash node can be inserted in the last level of hash, here we are attaching hash node to predecessor
        hash_node->right = p->right;
        p->right = hash_node;
        hash_node->left = p;
    }

    if (s != NULL) {
        if (s->level != w) {
            cout << "Unexpected level"
                 << "\n";
        }
        //here we are attaching hash node to successor
        hash_node->left = s->left;
        s->left = hash_node;
        hash_node->right = s;
    }

    //Starting from root and traverse down to the leaf while creating missing internal nodes
    int level = 1, pre;
    while (level != w) {
        pre = x / _pow(2, w - level);
        if (hash[level].find(pre) == hash[level].end()) {
            struct node* inner = new node();
            inner->level = level;
            inner->data = pre;
            hash[level][pre] = inner;
            if (pre & 1) {
                hash[level - 1][pre / 2]->right = inner;
            }
            else {
                hash[level - 1][pre / 2]->left = inner;
            }
        }
        ++level;
    }
    hash[w][x] = hash_node;
    // establishing connection between last and second last level
    if (x & 1) {
        hash[w - 1][x / 2]->right = hash_node;
    }
    else {
        hash[w - 1][x / 2]->left = hash_node;
    }

    //threading
    pre = x;
    level = w - 1;
    // we are creating descendent pointers, if a node has a missing left or right child
    while (level != 0) {
        pre = pre / 2;
        if (hash[level][pre]->left == NULL)
            hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w);
        //if a node has a missing left child, then it will point to the left most leaf of its right child
        if (hash[level][pre]->right == NULL)
            hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left, w);
        //if a node has a missing right child, then it will point to the right most leaf of its left child
        if (hash[level][pre]->left->level != hash[level][pre]->level + 1) {
            hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w);
        }
        if (hash[level][pre]->right->level != hash[level][pre]->level + 1) {
            hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left, w);
        }
        --level;
    }

    if (hash[0][0]->left == NULL) {
        hash[0][0]->left = get_Leftmost_Node(hash[0][0]->right, w);
    }
    if (hash[0][0]->right == NULL) {
        hash[0][0]->right = get_Rightmost_Node(hash[0][0]->left, w);
    }
    if (hash[0][0]->left->level != hash[0][0]->level + 1) {
        hash[0][0]->left = get_Leftmost_Node(hash[0][0]->right, w);
    }
    if (hash[0][0]->right->level != hash[0][0]->level + 1) {
        hash[0][0]->right = get_Rightmost_Node(hash[0][0]->left, w);
    }
}

void delete_node(int x, int w, vector<unordered_map<int, node*>>& hash) {
    struct node* temp = find(x, w, hash);
    struct node* s = temp->right;
    struct node* p = temp->left;
    if (p != NULL) {
        if (s != NULL) {
            p->right = s;
            s->left = p;
        }
        else {
            p->right = NULL;
        }
    }
    else {
        if (s != NULL) {
            s->left = NULL;
        }
    }

    int pre = x;
    int pprev;
    int level = w - 1;
    while (level >= 0) {
        pprev = pre;
        pre = pre / 2;
        temp = hash[level + 1][pprev];
        // if (hash[level][pre]->left->data == 2 * hash[level][pre]->data && hash[level][pre]->right->data == (2 * hash[level][pre]->data) + 1) {
        //     int a = 0;
        // }
        if (hash[level][pre]->left->level == (hash[level][pre]->level + 1) && hash[level][pre]->right->level == (hash[level][pre]->level + 1) &&
                (hash[level][pre]->left->data == 2 * hash[level][pre]->data && hash[level][pre]->right->data == (2 * hash[level][pre]->data) + 1)) {
            temp = hash[level + 1][pprev];
            if(pprev & 1)
                hash[level][pre]->right = NULL;
            else
                hash[level][pre]->left = NULL;
            hash[level + 1].erase(pprev);
            free(temp);
            //you have reached branch node :)
            break;
        }
        else {
            temp = hash[level + 1][pprev];
            if(pprev & 1)
                hash[level][pre]->right = NULL;
            else
                hash[level][pre]->left = NULL;
            hash[level + 1].erase(pprev);
            free(temp);
        }
        --level;
    }
    pre = pprev;
    while (level > 0) {
        pre = pre / 2;
        if (hash[level][pre]->left == NULL)
            hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w);
        if (hash[level][pre]->right == NULL)
            hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left, w);
        if (hash[level][pre]->left->level != hash[level][pre]->level + 1 && (hash[level][pre]->left->data != (hash[level][pre]->data*2))) {
            hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w);
        }
        if (hash[level][pre]->right->level != hash[level][pre]->level + 1 && (hash[level][pre]->right->data != (hash[level][pre]->data*2 + 1))) {
            hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left, w);
        }
        --level;
    }
    if (s != NULL) {
        pre = s->data;
        level = w - 1;
        while (level != 0) {
            pre = pre / 2;
            if (hash[level][pre]->left == NULL)
                hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w);
            if (hash[level][pre]->right == NULL)
                hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left, w);
            if (hash[level][pre]->left->level != hash[level][pre]->level + 1 && (hash[level][pre]->left->data != (hash[level][pre]->data*2))) {
                hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w);
            }
            if (hash[level][pre]->right->level != hash[level][pre]->level + 1 && (hash[level][pre]->right->data != (hash[level][pre]->data*2 + 1))) {
                hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left, w);
            }
            --level;
        }
    }
    if (p != NULL) {
        pre = p->data;
        level = w - 1;
        while (level != 0) {
            pre = pre / 2;
            if (hash[level][pre]->left == NULL)
                hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w);
            if (hash[level][pre]->right == NULL)
                hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left, w);
            if (hash[level][pre]->left->level != hash[level][pre]->level + 1 && (hash[level][pre]->left->data != (hash[level][pre]->data*2))) {
                hash[level][pre]->left = get_Leftmost_Node(hash[level][pre]->right, w);
            }
            if (hash[level][pre]->right->level != hash[level][pre]->level + 1 && (hash[level][pre]->right->data != (hash[level][pre]->data*2 + 1))) {
                hash[level][pre]->right = get_Rightmost_Node(hash[level][pre]->left, w);
            }
            --level;
        }
    }
}

int main() {
    // u is the universe size
    // w is the bit count of u, no of of bits in u
    int w, u;

    // Creating the x-fast trie
    vector<unordered_map<int, node*>> xfast;

    // Taking input from user regarding size of universe
    cout << "Enter the size of the universe: ";
    cin >> u;

    // Initialising x-fast trie
    w = bitCount(u);
    xfast.assign(w + 1, unordered_map<int, node*>());
    struct node* root = new node();
    root->level = 0;
    root->data = 0;
    xfast[0][0] = root;
    int n, c;
    while (true) {
        cout << "---MENU---" << "\n";
        cout << "Press 1 to insert\n";
        cout << "Press 2 to print predecessor\n";
        cout << "Press 3 to print successor\n";
        cout << "Press 4 to search for a given element\n";
        cout << "Press 5 to delete a given element\n";
        cout << "Press 6 to Exit\n";
        cout << "Enter your choice: ";
        cin >> c;
        if (c == 1) {
            cout << "Enter element to insert: ";
            cin >> n;
            if (n > u) {
                cout << "Enter element less than " << u << "\n";
            }
            else {
                insert_node(n, w, xfast);
            }
        }
        else if (c == 2) {
            cout << "Enter the value: ";
            cin >> n;
            cout << "Predecessor of the key " << n << ":";
            struct node* key = predecessor(n, w, xfast);
            if (key == NULL) {
                cout << " Predecessor of the key " << n << " is not present\n";
            }
            else {
                cout << " Predecessor of the key " << n << " is " << key->data << "\n";
            }
        }
        else if (c == 3) {
            cout << "Enter the value: ";
            cin >> n;
            cout << "Successor of the key " << n << ":";
            struct node* key = successor(n, w, xfast);
            if (key == NULL) {
                cout << " Successor of the key " << n << " is not present\n";
            }
            else {
                cout << " Successor of the key " << n << " is " << key->data << "\n";
            }
        }
        else if (c == 4) {
            cout << "Enter the element to be searched: ";
            cin >> n;
            if (find(n, w, xfast) != NULL) {
                cout << "Element is present\n";
            }
            else {
                cout << "Element not present\n";
            }
        }
        else if (c == 5) {
            cout << "Enter element to be deleted: ";
            cin >> n;
            if (find(n, w, xfast) == NULL) {
                cout << "Element is not present\n";
            }
            else {
                delete_node(n, w, xfast);
            }
        }
        else if (c == 6) {
            break;
        }
        else {
            cout << "Invalid Input";
        }
    }
}