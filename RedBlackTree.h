#pragma once
#include "RedBlackTreeNode.h"
#include <iostream>
using namespace std;

class RedBlackTree {
private:
    RedBlackTreeNode* root;
public:
    RedBlackTree() {
        root = nullptr;
    }
    ~RedBlackTree();
    RedBlackTree& operator=(const RedBlackTree& other);
    RedBlackTreeNode* copy(RedBlackTreeNode* node);
    void search(int key);
    void search(RedBlackTreeNode* helper, int key);

    void checkColor(RedBlackTreeNode* parent, RedBlackTreeNode* node);  //check color using parent
    void rotateDec(RedBlackTreeNode* parent, RedBlackTreeNode* node);   //decides which rotation to call

    void leftRotate(RedBlackTreeNode* root);    //left rotate --> needs parent node
    void rightRotate(RedBlackTreeNode* root);   //right rotate --> needs parent node

    void colorFlip(RedBlackTreeNode* root);     //color flip --> changes parent to red and its children to black
    void cfRotate(RedBlackTreeNode* grandpa);   //color flip for rotations --> changes parent to black, children to red

    void inorder(RedBlackTreeNode* root);       //inorder traversal
    void preorder(RedBlackTreeNode* root);      //preorder traversal
    void postorder(RedBlackTreeNode* root);     //postorder traversal
    void print();   //calls preorder
   
	void insert(int val);   //inserts node into tree
	void insert(RedBlackTreeNode* parent, RedBlackTreeNode* node);  //connects node to other nodes to make tree
    void del(int key);  //deletes node
    void del(RedBlackTreeNode* root, int key);  //delete helper function

};