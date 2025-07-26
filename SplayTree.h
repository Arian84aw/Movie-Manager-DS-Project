#pragma once
#include "HashTable.h"

class SplayNode {
public:
    string key;  
    SplayNode* left;
    SplayNode* right;

    SplayNode(string k) : key(k), left(nullptr), right(nullptr) {}
};

class SplayTree {

    SplayNode* root;
    SplayNode* rightRotate(SplayNode* x);
    SplayNode* leftRotate(SplayNode* x);
    SplayNode* splay(SplayNode* root, const string& targetKey);
    size_t _size;
    void printNearRoot(SplayNode* node, int depth, int maxDepth) {
        if (!node || depth > maxDepth)
            return;
        cout << node->key << endl;
        printNearRoot(node->left, depth + 1, maxDepth);
        printNearRoot(node->right, depth + 1, maxDepth);
    }
    void getNearRoot(SplayNode* node, int depth, int maxDepth, HashTable<string, bool>& s) {
        if (!node || depth > maxDepth)
            return;
        //cout << node->key << endl;
        if(! s.exists(node->key))
            s.insert(node->key, true);
        getNearRoot(node->left, depth + 1, maxDepth, s);
        getNearRoot(node->right, depth + 1, maxDepth, s);
    }

public:
    SplayTree() : root(nullptr), _size(0) {}

    void insert(string key);

    void display();

    void printNearRoot(int maxDepth) {
        printNearRoot(root, 0, maxDepth);
    }
    void getNearRoot(int maxDepth, HashTable<string, bool>& s) {
        getNearRoot(root, 0, maxDepth, s);
    }
    string getMostRecent() {
        if (root)
            return root->key;
        return "";
    }

    bool empty() const {
        return _size == 0;
    }

    SplayNode* find(string key) {
        root = splay(root, key);
        if (root && root->key == key)
            return root;
        return nullptr;
    }

    void erase(string key) {
        if (!root)
            return;

        root = splay(root, key);
        if (root->key != key)
            return;
        _size--;
        SplayNode* temp;
        if (!root->left) {
            temp = root;
            root = root->right;
        }
        else {
            temp = root;
            root = splay(root->left, key);
            root->right = temp->right;
        }
        delete temp;
    }
};