#include <iostream>
#include <queue>
using namespace std;
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

void levelorder(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->data << " ";

        if (current->left)
            q.push(current->left);

        if (current->right)
            q.push(current->right);
    }
}
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int val) {
        key = val;
        left = right = NULL;
        height = 1;
    }
};

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

int maxVal(int a, int b) {
    return (a > b) ? a : b;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxVal(height(y->left), height(y->right)) + 1;
    x->height = maxVal(height(x->left), height(x->right)) + 1;

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxVal(height(x->left), height(x->right)) + 1;
    y->height = maxVal(height(y->left), height(y->right)) + 1;

    return y;
}

AVLNode* insertAVL(AVLNode* node, int key) {
    if (!node)
        return new AVLNode(key);

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node;

    node->height = 1 + maxVal(height(node->left), height(node->right));

    int balance = getBalance(node);

    // LL Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

AVLNode* deleteAVL(AVLNode* root, int key) {
    if (!root)
        return root;

    if (key < root->key)
        root->left = deleteAVL(root->left, key);

    else if (key > root->key)
        root->right = deleteAVL(root->right, key);

    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }

            delete temp;
        } else {
            AVLNode* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + maxVal(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool searchAVL(AVLNode* root, int key) {
    if (!root)
        return false;

    if (root->key == key)
        return true;

    if (key < root->key)
        return searchAVL(root->left, key);

    return searchAVL(root->right, key);
}

void inorderAVL(AVLNode* root) {
    if (!root) return;
    inorderAVL(root->left);
    cout << root->key << " ";
    inorderAVL(root->right);
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

ThreadedNode* insertThreaded(ThreadedNode* root, int key) {
    ThreadedNode* ptr = root;
    ThreadedNode* parent = NULL;

    while (ptr != NULL) {
        if (key == ptr->data)
            return root;

        parent = ptr;

        if (key < ptr->data) {
            if (!ptr->leftThread)
                ptr = ptr->left;
            else
                break;
        } else {
            if (!ptr->rightThread)
                ptr = ptr->right;
            else
                break;
        }
    }

    ThreadedNode* newNode = new ThreadedNode(key);

    if (parent == NULL) {
        root = newNode;
    } 
    else if (key < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;

        parent->leftThread = false;
        parent->left = newNode;
    } 
    else {
        newNode->left = parent;
        newNode->right = parent->right;

        parent->rightThread = false;
        parent->right = newNode;
    }

    return root;
}

ThreadedNode* leftMost(ThreadedNode* root) {
    if (!root)
        return NULL;

    while (!root->leftThread)
        root = root->left;

    return root;
}

void inorderThreaded(ThreadedNode* root) {
    ThreadedNode* current = leftMost(root);

    while (current != NULL) {
        cout << current->data << " ";

        if (current->rightThread)
            current = current->right;
        else
            current = leftMost(current->right);
    }
}

void displayThreadedLinks(ThreadedNode* root) {
    ThreadedNode* current = leftMost(root);

    while (current != NULL) {
        cout << "Node " << current->data << ": ";

        if (current->leftThread && current->left != NULL)
            cout << "Left Thread -> " << current->left->data << " ";

        if (current->rightThread && current->right != NULL)
            cout << "Right Thread -> " << current->right->data << " ";

        cout << endl;

        if (current->rightThread)
            current = current->right;
        else
            current = leftMost(current->right);
    }
}
int main() {
    cout << "===== TREE TRAVERSALS =====\n";

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Inorder Traversal: ";
    inorder(root);
    cout << endl;

    cout << "Preorder Traversal: ";
    preorder(root);
    cout << endl;

    cout << "Postorder Traversal: ";
    postorder(root);
    cout << endl;

    cout << "Level-order Traversal: ";
    levelorder(root);
    cout << endl;


    cout << "\n===== AVL SEARCH AND DELETE WITH BALANCE =====\n";

    AVLNode* avl = NULL;

    int values[] = {30, 20, 40, 10, 25, 50, 5};

    for (int x : values)
        avl = insertAVL(avl, x);

    cout << "AVL Inorder before deletion: ";
    inorderAVL(avl);
    cout << endl;

    cout << "Search 25: ";
    cout << (searchAVL(avl, 25) ? "Found" : "Not Found") << endl;

    cout << "Search 100: ";
    cout << (searchAVL(avl, 100) ? "Found" : "Not Found") << endl;

    avl = deleteAVL(avl, 40);

    cout << "AVL Inorder after deleting 40: ";
    inorderAVL(avl);
    cout << endl;

    cout << "Balance Factor of root after deletion: ";
    cout << getBalance(avl) << endl;


    cout << "\n===== THREADED BINARY TREE =====\n";

    ThreadedNode* threadedRoot = NULL;

    int tvalues[] = {20, 10, 30, 5, 16, 14, 17};

    for (int x : tvalues)
        threadedRoot = insertThreaded(threadedRoot, x);

    cout << "Threaded Inorder Traversal: ";
    inorderThreaded(threadedRoot);
    cout << endl;

    cout << "\nThreaded Links:\n";
    displayThreadedLinks(threadedRoot);

    return 0;
}