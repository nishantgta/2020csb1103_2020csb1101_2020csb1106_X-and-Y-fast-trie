// Including libraries
#include <iostream>
#include <iterator>
#include <map>
#include <unordered_map>
#include <vector>
#define INT_MAX 2147483647
using namespace std;

// Defining the node for x-fast trie containing data, level
// and a left pointer and a right pointer. It also has a default constructor.
struct node {  //node of struct type will represent the node in our trie data structure.
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
struct node* find(int x, int w, vector<unordered_map<int, node*>>& xfast) {
    if (xfast[w].find(x) == xfast[w].end()) {
        return NULL;
    }
    return xfast[w][x];
}

// This function will return successor node in our trie corresponding to a given value
struct node* successor(int x, int w, vector<unordered_map<int, node*>>& xfast) {
    int l, h, m, pre;
    l = 0;
    h = w + 1;
    struct node* temp = NULL;

    // Binary search of levels
    while (h - l > 1) {
        m = (l + h) / 2;
        pre = x / _pow(2, w - m);  //this will store common prefix upto mid level,
        if (xfast[m].find(pre) == xfast[m].end()) {
            h = m;  //common prefix maybe in the upward section of mid
        }
        else {
            l = m;
            temp = xfast[m][pre];  //if the common prefix is in the downward section of mid,
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
struct node* predecessor(int x, int w, vector<unordered_map<int, node*>>& xfast) {
    int l, h, m, pre;
    l = 0;
    h = w + 1;
    struct node* temp = NULL;

    // Binary search of levels
    while (h - l > 1) {
        m = (l + h) / 2;
        pre = x / _pow(2, w - m);  //this will store common prefix upto mid level,
        if (xfast[m].find(pre) == xfast[m].end()) {
            h = m;  //common prefix maybe in the upward section of mid
        }
        else {
            l = m;
            temp = xfast[m][pre];  //if the common prefix is in the downward section of mid,
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
void insert_node(int x, int w, vector<unordered_map<int, node*>>& xfast) {
    struct node* hash_node = new node();  //hash node will represent the node to be inserted
    hash_node->data = x;
    hash_node->level = w;

    struct node* p = predecessor(x, w, xfast);  //p will have predecessor
    struct node* s = successor(x, w, xfast);    //s will have successor
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
        if (xfast[level].find(pre) == xfast[level].end()) {
            struct node* inner = new node();
            inner->level = level;
            inner->data = pre;
            xfast[level][pre] = inner;
            if (pre & 1) {
                xfast[level - 1][pre / 2]->right = inner;
            }
            else {
                xfast[level - 1][pre / 2]->left = inner;
            }
        }
        ++level;
    }
    xfast[w][x] = hash_node;
    // establishing connection between last and second last level
    if (x & 1) {
        xfast[w - 1][x / 2]->right = hash_node;
    }
    else {
        xfast[w - 1][x / 2]->left = hash_node;
    }

    //threading
    pre = x;
    level = w - 1;
    // we are creating descendent pointers, if a node has a missing left or right child
    while (level != 0) {
        pre = pre / 2;
        if (xfast[level][pre]->left == NULL)
            xfast[level][pre]->left = get_Leftmost_Node(xfast[level][pre]->right, w);
        //if a node has a missing left child, then it will point to the left most leaf of its right child
        if (xfast[level][pre]->right == NULL)
            xfast[level][pre]->right = get_Rightmost_Node(xfast[level][pre]->left, w);
        //if a node has a missing right child, then it will point to the right most leaf of its left child
        if (xfast[level][pre]->left->level != xfast[level][pre]->level + 1) {
            xfast[level][pre]->left = get_Leftmost_Node(xfast[level][pre]->right, w);
        }
        if (xfast[level][pre]->right->level != xfast[level][pre]->level + 1) {
            xfast[level][pre]->right = get_Rightmost_Node(xfast[level][pre]->left, w);
        }
        --level;
    }

    if (xfast[0][0]->left == NULL) {
        xfast[0][0]->left = get_Leftmost_Node(xfast[0][0]->right, w);
    }
    if (xfast[0][0]->right == NULL) {
        xfast[0][0]->right = get_Rightmost_Node(xfast[0][0]->left, w);
    }
    if (xfast[0][0]->left->level != xfast[0][0]->level + 1) {
        xfast[0][0]->left = get_Leftmost_Node(xfast[0][0]->right, w);
    }
    if (xfast[0][0]->right->level != xfast[0][0]->level + 1) {
        xfast[0][0]->right = get_Rightmost_Node(xfast[0][0]->left, w);
    }
}

// This function inserts the value into the bst
void insert_bst(int x, int val, map<int, int> bst) {
    bst[x] = val;
}

// Implementing the successor functionality for the bst
int successor_bst(int x, map<int, int> bst) {
    map<int, int>::iterator temp = bst.lower_bound(x);
    // If we reach the end of bst, it means successor of element is not present
    if (temp == bst.end()) {
        return INT_MAX;
    }
    else {
        return temp->first;
    }
}

// Implementing the pre functionality for the bst
int predecessor_bst(int x, map<int, int> bst) {
    map<int, int>::iterator temp = bst.upper_bound(x);
    // If we reach the front of bst, it means predecessor of element is not present
    if (temp == bst.begin()) {
        return -1;
    }
    temp = prev(temp);
    return temp->first;
}

// This will find the element the specified element in our trie, and return whether its present or not
int find_y_trie(int w, int x, unordered_map<int, map<int, int>>& bst, vector<unordered_map<int, node*>>& x_fast) {
    struct node* suc = successor(x, w, x_fast);
    struct node* pre = predecessor(x, w, x_fast);
    //finding element in the bst's of successor representative
    if (bst[suc->data].find(x) != bst[suc->data].end()) {
        return bst[suc->data][x];
    }
    if (bst[pre->data].find(x) != bst[pre->data].end()) {
        return bst[pre->data][x];
    }
    return -1;
}

// This will find the successor in the y-fast-trie
int successor_y_fast(int w, int x, unordered_map<int, map<int, int>>& bst, vector<unordered_map<int, node*>>& x_fast) {
    // This will find the successor and predecessor in the x-fast trie
    // and find the successor in both the binary search trees
    // and return the smaller value from both of them.
    struct node* suc = successor(x, w, x_fast);
    struct node* pre = predecessor(x, w, x_fast);
    int a = INT_MAX;
    int b = INT_MAX;
    if (suc != NULL)
        a = successor_bst(x, bst[suc->data]);
    if (pre != NULL)
        b = successor_bst(x, bst[pre->data]);
    return (a < b) ? a : b;
}

// This will find the predecessor in the y-fast-trie
int predecessor_y_fast(int w, int x, unordered_map<int, map<int, int>>& bst, vector<unordered_map<int, node*>>& x_fast) {
    // This will find the successor and predecessor in the x-fast trie
    // and find the predecessor in both the binary search trees
    // and return the larger value from both of them.
    struct node* suc = successor(x, w, x_fast);
    struct node* pre = predecessor(x, w, x_fast);
    int a = -1;
    int b = -1;
    if (suc != NULL)
        a = predecessor_bst(x, bst[suc->data]);
    if (pre != NULL)
        b = predecessor_bst(x, bst[pre->data]);
    return (a > b) ? a : b;
}

// This function will add the key to y-fast trie.
void insert_y_fast(int w, int x, unordered_map<int, map<int, int>>& bst, vector<unordered_map<int, node*>>& x_fast) {
    struct node* suc = successor(x, w, x_fast);
    if (suc == NULL) {              //if any element is not having successor, i.e. it is largest at a given time, then we will make it as representative
        insert_node(x, w, x_fast);  //this will make the given value as representative of the BST
        (bst[x])[x] = x;
    }
    else {  //if it has a representative then insert it in the appropriate BST.
        int s = suc->data;
        bst[s][x] = x;
    }
}

int main() {
    int w, u, c, n;
    vector<unordered_map<int, node*>> xfast;
    cout << "Enter the size of the universe: ";
    cin >> u;
    w = bitCount(u);
    xfast.assign(w + 1, unordered_map<int, node*>());
    struct node* root = new node();
    root->level = 0;
    root->data = 0;
    xfast[0][0] = root;

    unordered_map<int, map<int, int>> ytrie;

    while (true) {
        cout << "---MENU---" << "\n";
        cout << "Press 1 to insert\n";
        cout << "Press 2 to print predecessor\n";
        cout << "Press 3 to print successor\n";
        cout << "Press 4 to search for a given element\n";
        cout << "Press 5 to Exit\n";
        cout << "Enter your choice: ";
        cin >> c;
        if (c == 1) {
            cout << "Enter element to insert: ";
            cin >> n;
            if (n > u) {
                cout << "Enter element less than " << u << "\n";
            }
            else {
                insert_y_fast(w, n, ytrie, xfast);
            }
        }
        else if (c == 2) {
            cout << "Enter the value: ";
            cin >> n;
            cout << "Predecessor of the key " << n << ": ";
            int key = predecessor_y_fast(w, n, ytrie, xfast);
            if (key != -1) {
                cout << key << "\n";
            }
            else {
                cout << " Predecessor of the key " << n << " is not present\n";
            }
        }
        else if (c == 3) {
            cout << "Enter the value: ";
            cin >> n;
            cout << "Successor of the key " << n << ": ";
            int key = successor_y_fast(w, n, ytrie, xfast);
            if (key != INT_MAX) {
                cout << key << "\n";
            }
            else {
                cout << " Successor of the key " << n << " is not present\n";
            }
        }
        else if (c == 4) {
            cout << "Enter the element to be searched: ";
            cin >> n;
            if (find_y_trie(w, n, ytrie, xfast) != -1) {
                cout << "Element is present\n";
            }
            else {
                cout << "Element not present\n";
            }
        }
        else if (c == 5) {
            break;
        }
        else {
            cout << "Invalid Input\n";
        }
    }
    return 0;
}
