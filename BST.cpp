#include "BST.h"
#include <iostream>
#include <string>

using namespace std;

// Constructor
BST::BST() {
    root = nullptr;
}

// Destructor
BST::~BST() {
    _destroyTree(root);
}

void BST::insert(const string& key, int hashIndex) {
    root = _insert(root, key, hashIndex);
}

BSTNode* BST::_insert(BSTNode* node, const string& key, int hashIndex) {
    if (node == nullptr) {
        return new BSTNode(key, hashIndex);
    }
    
    else if (node->key > key) {
        node->left = _insert(node->left, key, hashIndex);
    }

    else if (node->key < key) {
        node->right = _insert(node->right, key, hashIndex);
    }
    
    return node;
}

int BST::search(const string& key) const {
    return _search(root, key);
}

int BST::_search(BSTNode* node, const string& key) const {
    if (node == nullptr) {
        return -1;
    }

    if (node->key == key) {
        return node->hashIndex;
    }

    if (node->key > key) {
        return _search(node->left, key);
    }

    return _search(node->right, key);
}

void BST::remove(const string& key) {
    root = _remove(root, key);
}

BSTNode* BST::_remove(BSTNode* node, const string& key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (node->key > key) {
        node->left = _remove(node->left, key);
    }

    else if (node->key < key) {
        node->right = _remove(node->right, key);
    }

    else {
        // no children node
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        // only has 1 right child
        if (node->left == nullptr) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }

        // only has 1 left child
        if (node->right == nullptr) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        // has 2 children
        BSTNode* successor = _findMin(node->right);
        node->key = successor->key;
        node->hashIndex = successor->hashIndex;
        node->right = _remove(node->right, successor->key);
    }
    return node;
}

BSTNode* BST::_findMin(BSTNode* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void BST::inorder() const {
    _inorder(root);
}

void BST::_inorder(BSTNode* node) const {
    if (node == nullptr) {
        return;
    }

    _inorder(node->left);
    cout << node->key << " (" << node->hashIndex << ")" << endl;
    _inorder(node->right);
}

void BST::printIndented() const {
    _printIndented(root, 0);
}

void BST::_printIndented(BSTNode* node, int level) const {
    if (node == nullptr) {
        return;
    }

    _printIndented(node->right, level + 1);

    for (int i = 0; i < level; i++) {
        cout << "    ";
    }
    cout << node->key << endl;
    _printIndented(node->left, level + 1);
}

void BST::clear() {
    _destroyTree(root);
    root = nullptr;
}

bool BST::isEmpty() const {
    return root == nullptr;
}

void BST::_destroyTree(BSTNode* node) {
    if (node == nullptr) {
        return;
    }
    _destroyTree(node->left);
    _destroyTree(node->right);
    delete node;
}
