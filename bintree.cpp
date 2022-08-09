//
// Created by arwal on 2/5/2020.
//Anna Waldron
//2/10/2020
//

#include "bintree.h"


BinTree::BinTree(const BinTree &other) {
   root = treeCopy(other.root);
}
/*
 * creates a deep copy of a tree.
 */
BinTree::Node* BinTree::treeCopy(const BinTree::Node* other){
    if(other == nullptr){
        return nullptr;
    }
    Node* newNode = new Node(new NodeData(*other->data));
    newNode->left = treeCopy(other->left);
    newNode->right = treeCopy(other->right);
    return newNode;
}

void BinTree::displaySideways() const {
    sideways(root, 0);
}
void BinTree::sideways(Node* current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "    ";
        }

        cout << *current->data << endl;        // display information of object
        sideways(current->left, level);
    }
}
/*
 * insert function for NodeData objects into the tree. Uses helper recursive function.
 */
bool BinTree::insert(NodeData *nd) {
    if(nd == nullptr){
        return false;
    }
    else{
        return helperInsert(this->root, nd);
    }
}
/*
 * Helper function for insert method using current node and data as parameters. Returns
 * true if successfully inserted.
 */
bool BinTree::helperInsert(Node *&current, NodeData *nd) {
    if (current == nullptr) {
        current = new Node(nd);
        return true;
    }
    if (*nd == *(current->data)) {
        return false;
    }
    if (*nd < *(current->data)) {
        return helperInsert(current->left, nd);
    } else {
        return helperInsert(current->right, nd);
    }
}

/*
 * Tree destructor that calls a makeEmpty method.
 */
BinTree::~BinTree() {
    makeEmpty();
}
/*
 * Deletion method used by the makeEmpty method that deletes the contents of a tree.
 */
void BinTree::recursiveDelete(Node *current) {
    if (current == nullptr) {
        return;
    }
    Node *left = current->left;
    Node *right = current->right;

    if (left != nullptr) {
        recursiveDelete(left);
        current->left = nullptr;
    }
    if (right != nullptr) {
        recursiveDelete(right);
        current->right = nullptr;
    }

    delete current->data;
    current->data = nullptr;
    delete current;
}
/*
 * method for deleting the contents of a tree using a recursive method.
 */
void BinTree::makeEmpty() {
    recursiveDelete(this->root);
    this->root = nullptr;
}
/*
 * Method which gives the distance of a specified node to the tree leafs. Uses two
 * other functions to perform this task.
 */
int BinTree::getHeight(const NodeData &nd) const {
    if(this->isEmpty()){
        return 0;
    }
    return heightHelper(nd, retrieval(nd, this->root));

}
/*
 * helper method for getHeight that retrieves the node with the specified data.
 */
BinTree::Node* BinTree::retrieval(const NodeData &nd, BinTree::Node * current)const{
    if(current == nullptr){
        return nullptr;
    }
    if (*current->data == nd) {
        return current;
    }
    Node * check = retrieval(nd, current->left);
    if(check == nullptr){
        return retrieval(nd, current->right);
    }else{
        return check;
    }
}
/*
 * Helper method of getHeight that find the height of the node to the leaf nodes.
 */
int BinTree::heightHelper(const NodeData &nd, BinTree::Node * current)const  {
    if(current == nullptr){
        return 0;
    }
    int left = heightHelper(nd, current->left);
    int right = heightHelper(nd, current->right);

    if(left > right){
        return left+1;
    }else{
        return right+1;
    }
}
/*
 * Helper function that recursively builds a string of inordered nodes of a tree.
 */
void BinTree::inorderHelper( std::ostream &stream, BinTree::Node *current) const {
    if(current == nullptr){
        return;
    }
    inorderHelper(stream, current->left);
    stream << *current->data << ", ";
    inorderHelper(stream, current->right);
}
/*
 * overloaded function for cout or printing inordered nodes of a tree.
 */
std::ostream &operator<<(std::ostream &stream, const BinTree &tree) {
    tree.inorderHelper(stream, tree.root);
    return stream;
}
/*
 * Function that changes a BS tree into an array and deletes the tree.
 */
void BinTree::bstreeToArray(NodeData ** list) {
    if(this->isEmpty()){
        return;
    }
    int level;
    level = 0;
    arrayHelper(list, this->root, level);
}
/*
 * helper function for BS tree to array function that recursively builds an array.
 */
void BinTree::arrayHelper(NodeData *list[], BinTree::Node *& current, int &level){
    if(current == nullptr){
        return;
    }
    arrayHelper(list, current->left, level);
    list[level] = current->data;
    level++;
    arrayHelper(list, current->right, level);

    current->data = nullptr;
    delete current;
    current = nullptr;
}
/*
 * function that changes an array into a BS tree and sets the array to nullptrs after.
 */
void BinTree::arrayToBSTree(NodeData * list[]) {
    if(list[0] == nullptr){
        return;
    }
    makeEmpty();
    int length = 0;
    while(list[length] !=nullptr){
        length++;
    }
    treeHelper(list, this->root, 0, length - 1);
}
/*
 * helper function for array to BS tree that recursively builds a tree using the array.
 */
void BinTree::treeHelper(NodeData *list[], BinTree::Node *& current, int low, int high){
    if(low > high){
        return;
    }
    int mid = (low + high)/2;
    current = new Node(list[mid]);
    list[mid] = nullptr;

    treeHelper(list, current->left, low, mid-1);
    treeHelper(list, current->right, mid+1, high);
}
/*
 * Overloaded assignment operator that deep copies a tree to another.
 */
BinTree& BinTree::operator=(const BinTree &other) {
    if (this != &other){
        BinTree temp(other);
        std::swap(temp.root, this->root);
    }
    return *this;
}

/*
 * overloaded equality operator that return whether two trees are the same.
 */
bool BinTree::operator==(const BinTree &other) const {
   return helpEqual(this->root, other.root);
}
/*
 * Helper function to equality operator overload that checks to see if all nodes
 * are the same in two trees.
 */
bool BinTree::helpEqual(Node * current, Node * other) const {
    bool returnBool = false;

    if(current == nullptr && other == nullptr){
        return true;
    }
    if(current == nullptr || other == nullptr){
        return false;
    }
    returnBool = (helpEqual(current->left, other->left) && helpEqual(current->right, other->right));
    if (returnBool == false){
        return false;
    }
    if(*current->data == *other->data){
        return true;
    } else {
        return false;
    }
}
/*
 * Overloaded inequality operator function that determines if two trees are not the same.
 */
bool BinTree::operator!=(const BinTree &other) const {
    return !(*this == other);
}
/*
 * Function that returns true if an data object is found in the tree and assigns a
 * pointer to the node with the specified data.
 */
bool BinTree::retrieve(NodeData &item, NodeData *&found) const {
    if (this->isEmpty()) {
        return false;
    }
    retrieveHelper(this->root, item, found);
    return *found == item;
}


/*
 * helper function for retrieve function that uses recursion to find that node with the
 * specified data.
 */
void BinTree::retrieveHelper(BinTree::Node * current, NodeData &item, NodeData *&found)const{
    if(current == nullptr){
        return;
    }
    if(*current->data == item){
        found = current->data;
        return;
    }else{
        retrieveHelper(current->left, item, found);
        retrieveHelper(current->right, item, found);
        return;
    }
}
/*
 * Function that returns true if a tree is empty.
 */
bool BinTree::isEmpty() const {
    if(this->root == nullptr){
        return true;
    }else{
        return false;
    }

}

