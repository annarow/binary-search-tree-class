//
// Created by arwal on 2/5/2020.
//Anna Waldron
//2/10/2020

#ifndef BINARY_SEARCH_TREE_CLASS_BINTREE_H
#define BINARY_SEARCH_TREE_CLASS_BINTREE_H
#include "nodedata.h"

class BinTree {

    struct Node{
        NodeData * data;
        Node * left;
        Node * right;

        Node() = delete;

        Node(NodeData *nd) {
            data = nd;
            left = nullptr;
            right = nullptr;
        }

        Node(const Node &other) {
            data = new NodeData(*other.data);
            left = new Node(*other.left);
            right = new Node(*other.right);
        }
    };
    Node * root;
public:
    BinTree(){root = nullptr;}
    BinTree(const string &s) {
        this->root = new Node(new NodeData(s));
    }
    ~BinTree();
    void recursiveDelete(Node *current);
    bool isEmpty() const;
    void makeEmpty();
    BinTree& operator=(const BinTree &other);
    bool operator==(const BinTree &other) const;
    bool operator!=(const BinTree &other) const;
    bool insert(NodeData* other);
    bool helperInsert(Node *&current, NodeData *nd);
    bool retrieve(NodeData &item, NodeData *&found) const;
    void displaySideways() const;
    int getHeight(const NodeData &) const;
    void sideways(Node*, int) const;
    BinTree(const BinTree &other);
    void bstreeToArray(NodeData* []);   //need this
    void arrayToBSTree(NodeData* []);   //need this
    Node* treeCopy(const Node* other);

    void inorderHelper(std::ostream &stream, Node *current) const;
    friend std::ostream &operator <<(std::ostream &stream, const BinTree &tree);


    bool helpEqual(Node *current, Node *other) const;

    void arrayHelper(NodeData *list[], BinTree::Node *& current, int &level);

    int heightHelper(const NodeData &nd, Node *current)const;

    void retrieveHelper(Node *current, NodeData &item, NodeData *&found) const;

    void treeHelper(NodeData **list, Node *&current, int low, int high);

    Node *retrieval(const NodeData &nd, Node *current)const;
};


#endif //BINARY_SEARCH_TREE_CLASS_BINTREE_H
/*
* string line;
* string stream stream(line);
* stream >> start >> end >> distance;
*
*/