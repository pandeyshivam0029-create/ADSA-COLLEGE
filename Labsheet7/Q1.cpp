#include <iostream>
#include <vector>
using namespace std;
struct GeneralNode {
    char data;
    GeneralNode* leftChild;
    GeneralNode* rightSibling;

    GeneralNode(char val) {
        data = val;
        leftChild = rightSibling = NULL;
    }
};

void generalPreorder(GeneralNode* root) {
    if (!root) return;
    cout << root->data << " ";
    generalPreorder(root->leftChild);
    generalPreorder(root->rightSibling);
}

struct BinaryNode {
    int data;
    BinaryNode* left;
    BinaryNode* right;

    BinaryNode(int val) {
        data = val;
        left = right = NULL;
    }
};

void inorder(BinaryNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

BinaryNode* insertBST(BinaryNode* root, int key) {
    if (!root) return new BinaryNode(key);

    if (key < root->data)
        root->left = insertBST(root->left, key);
    else
        root->right = insertBST(root->right, key);

    return root;
}

struct ThreadedNode {
    int data;
    ThreadedNode* left;
    ThreadedNode* right;
    bool leftThread;
    bool rightThread;

    ThreadedNode(int val) {
        data = val;
        left = right = NULL;
        leftThread = rightThread = true;
    }
};

struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int val) {
        data = val;
        left = right = NULL;
        height = 1;
    }
};

int height(AVLNode* root) {
    return root ? root->height : 0;
}

int balanceFactor(AVLNode* root) {
    return root ? height(root->left) - height(root->right) : 0;
}

enum Color { RED, BLACK };

struct RBNode {
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int val) {
        data = val;
        color = RED;
        left = right = parent = NULL;
    }
};

class BTreeNode {
public:
    vector<int> keys;
    vector<BTreeNode*> children;
    bool leaf;

    BTreeNode(bool isLeaf) {
        leaf = isLeaf;
    }
};

int main() {
    cout << "1. General Tree / Forest using Left-Child Right-Sibling\n";

    GeneralNode* A = new GeneralNode('A');
    GeneralNode* B = new GeneralNode('B');
    GeneralNode* C = new GeneralNode('C');
    GeneralNode* D = new GeneralNode('D');

    A->leftChild = B;
    B->rightSibling = C;
    C->rightSibling = D;

    cout << "General Tree Preorder: ";
    generalPreorder(A);
    cout << "\n\n";

    cout << "2. Binary Tree Array Representation\n";
    int arrTree[] = {1, 2, 3, 4, 5, 6, 7};

    cout << "Array Tree: ";
    for (int x : arrTree)
        cout << x << " ";
    cout << "\n";
    cout << "For index i: left child = 2*i+1, right child = 2*i+2\n\n";

    cout << "3. Binary Tree Linked Representation\n";
    BinaryNode* root = new BinaryNode(1);
    root->left = new BinaryNode(2);
    root->right = new BinaryNode(3);
    root->left->left = new BinaryNode(4);
    root->left->right = new BinaryNode(5);

    cout << "Binary Tree Inorder: ";
    inorder(root);
    cout << "\n\n";

    cout << "4. Binary Search Tree Representation\n";
    BinaryNode* bst = NULL;
    bst = insertBST(bst, 50);
    bst = insertBST(bst, 30);
    bst = insertBST(bst, 70);
    bst = insertBST(bst, 20);
    bst = insertBST(bst, 40);

    cout << "BST Inorder: ";
    inorder(bst);
    cout << "\n\n";

    cout << "5. Threaded Binary Tree Node Representation\n";
    ThreadedNode* tnode = new ThreadedNode(10);
    cout << "Threaded Node Created: " << tnode->data << endl;
    cout << "leftThread = true, rightThread = true\n\n";

    cout << "6. AVL Tree Node Representation\n";
    AVLNode* avl = new AVLNode(30);
    avl->left = new AVLNode(20);
    avl->right = new AVLNode(40);

    cout << "AVL Root: " << avl->data << endl;
    cout << "Balance Factor of root: " << balanceFactor(avl) << "\n\n";

    cout << "7. Red-Black Tree Node Representation\n";
    RBNode* rb = new RBNode(100);
    rb->color = BLACK;

    cout << "Red-Black Root: " << rb->data << endl;
    cout << "Root color: BLACK\n\n";

    cout << "8. B-Tree Node Representation\n";
    BTreeNode* btree = new BTreeNode(true);
    btree->keys.push_back(10);
    btree->keys.push_back(20);
    btree->keys.push_back(30);

    cout << "B-Tree Node Keys: ";
    for (int key : btree->keys)
        cout << key << " ";
    cout << endl;

    return 0;
}