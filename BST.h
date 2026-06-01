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
    BSTNode* _findMin(BSTNode* node);
    void _inorder(BSTNode* node) const;
    void _printIndented(BSTNode* node, int level) const;
    void _destroyTree(BSTNode* node);

public:
    BST();
    ~BST();

    void insert(const string& key, int hashIndex);
    void remove(const string& key);
    void inorder() const;
    void printIndented() const;
    bool isEmpty() const;
};

#endif