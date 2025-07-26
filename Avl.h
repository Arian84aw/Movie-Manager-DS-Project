#pragma once
#include "Headers.h"

template <typename T>
class Node {
public:
    T key;
    vector<T> values;
    Node<T>* left;
    Node<T>* right;
    int height;

    Node(const T& k) : key(k), left(nullptr), right(nullptr), height(1) {
        values.push_back(k);
    }
};

template <typename T>
class AVLTree {
private:
    Node<T>* root;
    int _size = 0;
    int height(Node<T>* n) {
        return n ? n->height : 0;
    }

    int balanceFactor(Node<T>* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    void updateHeight(Node<T>* n) {
        if (n)
            n->height = 1 + max(height(n->left), height(n->right));
    }

    Node<T>* rotateRight(Node<T>* y) {
        Node<T>* x = y->left;
        Node<T>* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    Node<T>* rotateLeft(Node<T>* x) {
        Node<T>* y = x->right;
        Node<T>* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    Node<T>* balance(Node<T>* n) {
        if (!n) return n;
        updateHeight(n);
        int bf = balanceFactor(n);

        if (bf > 1) {
            if (balanceFactor(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }

        if (bf < -1) {
            if (balanceFactor(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }

        return n;
    }

    Node<T>* Insert(Node<T>* n, const T& key) {
        if (!n)
            return new Node<T>(key);

        if (key < n->key)
            n->left = Insert(n->left, key);
        else if (key > n->key)
            n->right = Insert(n->right, key);
        else
            n->values.push_back(key);

        return balance(n);
    }

    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->left)
            current = current->left;
        return current;
    }

    Node<T>* DeleteNode(Node<T>* root, const T& key) {

        if (!root) return root;

        if (key < root->key)
            root->left = DeleteNode(root->left, key);
        else if (key > root->key)
            root->right = DeleteNode(root->right, key);
        else {
            if (root->values.size() > 1) {
                root->values.pop_back();
                return root;
            }

            if (!root->left || !root->right) {
                Node<T>* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {
                Node<T>* temp = minValueNode(root->right);
                root->key = temp->key;
                root->values = temp->values;
                root->right = DeleteNode(root->right, temp->key);
            }
        }

        if (!root)
            return root;

        return balance(root);
    }

    void inOrder(Node<T>* node, vector<T>& res) {
        if (!node)
            return;

        inOrder(node->left, res);
        for (const auto& val : node->values) {
            res.push_back(val);
            /*cout << val << endl;*/
            /*if constexpr (is_same<T, pair<float, string>>::value) {
                cout << val.first << " : " << val.second << endl;
            }
            else {
                cout << val << endl;
            }*/
        }
        inOrder(node->right, res);
    }

    bool areNodesEqual(Node<T>* n1, Node<T>* n2) const {
        if (n1 == nullptr && n2 == nullptr)
            return true;
        if (n1 == nullptr || n2 == nullptr)
            return false;
        if (n1->key != n2->key || n1->values != n2->values)
            return false;
        return areNodesEqual(n1->left, n2->left) && areNodesEqual(n1->right, n2->right);
    }



public:
    AVLTree() : root(nullptr) {}

    void insert(const T& key) {
        _size++;
        root = Insert(root, key);
    }

    void deleteKey(const T& key) {
        _size--;
        root = DeleteNode(root, key);
    }

    int size()const {
        return _size;
    }

    vector<T> inOrder() {
        vector<T> res;
        inOrder(root, res);
        reverse(res.begin(), res.end());
        return res;
        //cout << endl;
    }

    bool operator==(const AVLTree<T>& other) const {
        if (_size != other._size)
            return false;
        return areNodesEqual(root, other.root);
    }
};