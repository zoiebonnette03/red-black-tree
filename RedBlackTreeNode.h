#pragma once
class RedBlackTree; 

class RedBlackTreeNode {
	friend class RedBlackTree;
private:
	int data;
	int size = 0;
	RedBlackTreeNode* right;
	RedBlackTreeNode* left;
	RedBlackTreeNode* parent;
	bool isBlack;
	bool isleftChild;

public:
	RedBlackTreeNode() {
		data = 0;
		left = right = parent = nullptr;
		isBlack = false;
		isleftChild = false;
		size++;
	}
	RedBlackTreeNode(int val) {
		data = val;
		left = right = parent = nullptr;
		isBlack = false;
		isleftChild = false;
		size++;
	}
};
