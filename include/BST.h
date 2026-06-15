/**
 * @file BST.h
 * @brief Declares a binary search tree for mapping flight numbers to hash table indexes.
 */

#ifndef BST_H
#define BST_H

#include <string>
using namespace std;

struct BSTNode
{
    string key;
    int hashIndex;

    BSTNode* left;
    BSTNode* right;

    BSTNode(string k, int idx)
    {
        key = k;
        hashIndex = idx;
        left = nullptr;
        right = nullptr;
    }
};

class BST
{
private:
    BSTNode* root;
    BSTNode* _insert(BSTNode* node, const std::string& key, int hashIndex);
    BSTNode* _remove(BSTNode* node, const std::string& key);
    int _search(BSTNode* node, const std::string& key) const;
    BSTNode* _findMin(BSTNode* node);
    void _inorder(BSTNode* node) const;
    void _printIndented(BSTNode* node, int level) const;
    void _destroyTree(BSTNode* node);

public:
    BST();
    ~BST();

    void insert(const string& key, int hashIndex);
    int search(const string& key) const;
    void remove(const string& key);
    void clear();
    void inorder() const;
    void printIndented() const;
    bool isEmpty() const;
};

#endif
