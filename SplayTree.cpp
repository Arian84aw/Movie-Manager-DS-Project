#include "SplayTree.h"


SplayNode* SplayTree::rightRotate(SplayNode* x) {
    SplayNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}


SplayNode* SplayTree::leftRotate(SplayNode* x) {
    SplayNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}


SplayNode* SplayTree::splay(SplayNode* root, const string& targetKey) {
    if (root == nullptr || root->key == targetKey)
        return root;

    
    if (targetKey < root->key) {
        if (root->left == nullptr)
            return root;

      
        if (targetKey < root->left->key) {
            root->left->left = splay(root->left->left, targetKey);
            root = rightRotate(root);
        }
     
        else if (targetKey > root->left->key) {
            root->left->right = splay(root->left->right, targetKey);
            if (root->left->right != nullptr)
                root->left = leftRotate(root->left);
        }

        return (root->left == nullptr) ? root : rightRotate(root);
    }
 
    else {
        if (root->right == nullptr)
            return root;


        if (targetKey < root->right->key) {
            root->right->left = splay(root->right->left, targetKey);
            if (root->right->left != nullptr)
                root->right = rightRotate(root->right);
        }

        else if (targetKey > root->right->key) {
            root->right->right = splay(root->right->right, targetKey);
            root = leftRotate(root);
        }

        return (root->right == nullptr) ? root : leftRotate(root);
    }
}


void SplayTree::insert( string key) {
    if (root == nullptr) {
        root = new SplayNode(key);
        _size++;
        return;
    }


    root = splay(root, key);

    if (root->key == key)
        return;

    SplayNode* newNode = new SplayNode(key);
    _size++;

    
    if (key < root->key) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    }
    else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }

    
    root = newNode;
}


void SplayTree::display() {
    if (root == nullptr) {
        cout << "tree is empty!" << endl;
        return;
    }

    queue<SplayNode*> q;
    q.push(root);

    while (!q.empty()) {
        SplayNode* current = q.front();
        q.pop();

        cout << "movie: " << current->key << endl;

        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}
