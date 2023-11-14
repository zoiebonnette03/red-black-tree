#include "RedBlackTreeNode.h"
#include "RedBlackTree.h"
#include <iostream>
using namespace std;

//left tree rotation
void RedBlackTree::leftRotate(RedBlackTreeNode* parent) {
	RedBlackTreeNode* grandpa = parent->parent;			//initializes grandpa as parent's parent
	RedBlackTreeNode* temp = parent->right;				//newRoot is right child of root
	parent->right = temp->left;							//root's right child is left child of newRoot
	temp->left = parent;								//newRoot's left child is root
	
	/*	I kept getting nullptr handling exceptions
	so this deals with all of that and checks for nullptr	*/
	parent->parent = temp;
	if (parent->left != nullptr)
		parent->left->parent = parent;
	if (parent->right != nullptr)
		parent->right->parent = parent;
	temp->parent = grandpa;

	/*	updates root. sets temp as granpda's child if grandpa is 
	not nullptr if grandpa is nullptr, then temp is root	*/
	if (grandpa != nullptr) {							
		if (parent->isleftChild)						
			grandpa->left = temp;							
		else
			grandpa->right = temp;							
	}
	else
		root = temp;
	
	cfRotate(temp);		//calls color flip function for rotations
}
//right tree rotation
void RedBlackTree::rightRotate(RedBlackTreeNode* parent) {
	RedBlackTreeNode* grandpa = parent->parent;
	RedBlackTreeNode* temp = parent->left;     //newRoot is left child of root
	parent->left = temp->right;                //root's left child is right child of newRoot
	temp->right = parent;                      //newRoot's right child is root
	
	/*	I kept getting nullptr handling exceptions
	so this deals with all of that and checks for nullptr	*/
	parent->parent = temp;
	if (parent->left != nullptr) 
		parent->left->parent = parent;
	if (parent->right != nullptr) 
		parent->right->parent = parent;
	temp->parent = grandpa;
	
	/*	updates root. sets temp as granpda's child if grandpa is 
	not nullptr, if grandpa is nullptr, then temp is root	*/
	if (grandpa != nullptr) {
		if (parent->isleftChild) 
			grandpa->left = temp;
		else 
			grandpa->right = temp;
	}
	else
		root = temp;
	
	cfRotate(temp);		//calls color flip function for rotations
}

//normal color flip
void RedBlackTree::colorFlip(RedBlackTreeNode* parent) {
	/*	if else statements to check for different nullptr cases
		will change parent to red and children to black		*/
	if ((parent->right == nullptr) && (parent->left == nullptr)) {
		parent->isBlack = false;
	}
	else if (parent->right == nullptr) {
		parent->isBlack = false;
		parent->left->isBlack = true;
	}
	else if (parent->left == nullptr) {
		parent->isBlack = false;
		parent->right->isBlack = true;
	}
	else {
		parent->isBlack = false;
		parent->left->isBlack = true;
		parent->right->isBlack = true;
	}
}
//color flip for rotations
void RedBlackTree::cfRotate(RedBlackTreeNode* parent) {
	/*	if else statements to check for different nullptr cases
		will change parent to black and children to red		*/
	if ((parent->right == nullptr) && (parent->left == nullptr)) {
		parent->isBlack = true;
	}
	else if (parent->right == nullptr) {
		parent->isBlack = true;
		parent->left->isBlack = false;
	}
	else if (parent->left == nullptr) {
		parent->isBlack = true;
		parent->right->isBlack = false;
	}
	else {
		parent->isBlack = true;
		parent->left->isBlack = false;
		parent->right->isBlack = false;
	}
}
//decides which rotate function to call
void RedBlackTree::rotateDec(RedBlackTreeNode* parent, RedBlackTreeNode* node) {
	RedBlackTreeNode* newParent = new RedBlackTreeNode();
	RedBlackTreeNode* grandpa = parent->parent;		//initializes grandpa to parent's parent
	if (parent->isBlack == false) {					
		if (parent->isleftChild == false) {			
			if (node->isleftChild == false)			//if parent is red and right child; and node is right child
				leftRotate(parent);					//calls leftRotate with parent as parameter
			else {									//if parent is red and right child; and node is left child
				rightRotate(parent);				//calls rightRotate with parent as parameter
				leftRotate(grandpa);				//calls leftRotate with grandpa as parameter
			}
		}
		else {					
			if (node->isleftChild == false) {		//if parent is red and left child; and node is right child
				leftRotate(parent);					//calls leftRotate with parent as parameter
				rightRotate(grandpa);				//calls rightRotate with grandpa as parameter
			}
			else									//if parent is red and left child; and node is left child
				rightRotate(grandpa);				//calls rightRotate with grandpa as parameter
		}	
	}
	else											//else means parent is black so there is no issue, so return
		return;
}
//checks the color of the inserted node and parent node
void RedBlackTree::checkColor(RedBlackTreeNode* parent, RedBlackTreeNode* node) {
	if (root == parent)			//if root is the parent, then parent is black, so no issues
		return;
	
	RedBlackTreeNode* grandpa = parent->parent;						//initializes grandpa to parent's parent
	if (grandpa == nullptr)		//if grandpa is nullptr, return 
		return;

	RedBlackTreeNode* aunt = new RedBlackTreeNode();				//initializes aunt
	if ((grandpa->right == nullptr) || (grandpa->left == nullptr))	//if either of grandpa's children are nullptr
		aunt->isBlack = true;										//aunt is black
	else if (parent->isleftChild == true)							//if parent is left child of grandpa
		aunt = grandpa->right;										//aunt is right child of grandpa
	else
		aunt = grandpa->left;										//else aunt is left child of grandpa

	if (aunt->isBlack == true)										//if aunt is black, calls rotateDec function
		rotateDec(parent, node);
	else															//else aunt is red, calls colorFlip function
		colorFlip(grandpa);
	
	root->isBlack = true;											//root is always black
}

//insert function
void RedBlackTree::insert(int val) {
	RedBlackTreeNode* newNode = new RedBlackTreeNode(val);	//creates new node with spec. value
	if (root == nullptr) {									//if root has no value, then the newNode is root
		root = newNode;
		root->isBlack = true;
	}
	else													//else call insert helper function with root and newNode
		insert(root, newNode);
}
//insert helper function
void RedBlackTree::insert(RedBlackTreeNode* parent, RedBlackTreeNode* node) {
	if (parent->data < node->data) {						//if parent's data < node's data, travel right down tree
		if (parent->right == nullptr) {						//only add node as parent's right child if parent->right = nullptr
			parent->right = node;
			node->isleftChild = false;
			node->parent = parent;
			node->isBlack = false;
			checkColor(parent, node);						//checkColor of parent and new node
		}
		else
			insert(parent->right, node);					//recursively call insert with parent->right as new parent
	}
	else {													//else parent's data > node's data, travel left down tree
		if (parent->left == nullptr) {						//only add node as parent's left child if parent->left = nullptr
			parent->left = node;
			node->isleftChild = true;
			node->parent = parent;
			node->isBlack = false;
			checkColor(parent, node);						//checkColor of parent and new node
		}
		else
			insert(parent->left, node);						//recursively call insert with parent->left as new parent
	}
}

//delete function
void RedBlackTree::del(int key) {
	if (root == nullptr)
		cout << "Tree is empty." << endl;
	else
		del(root, key);
}
//delete helper function
void RedBlackTree::del(RedBlackTreeNode* parent, int key) {
	//finds the node to delete
	RedBlackTreeNode* nodeDel = nullptr;
	//if key is not found
	if (parent == nullptr) {
		cout << key << " is not in tree." << endl;
		return; 
	}
	//if key < parent data, recursivley call del function 
	else if (key < parent->data) {
		del(parent->left, key);
		return;
	}
	//if key > parent data, recursivley call del function
	else if (key > parent->data) {
		del(parent->right, key);
		return;
	}
	else
		nodeDel = parent;

	//if the node to delete is a leaf
	if (nodeDel->left == nullptr && nodeDel->right == nullptr) {	
		if (nodeDel == root)								//if nodeDel is the root, update root to nullptr
			root = nullptr;
		else if (nodeDel->isleftChild) 						//if nodeDel is left child, 
			nodeDel->parent->left = nullptr;				//parent's left child is nullptr
		else												//if nodeDel is right child 
			nodeDel->parent->right = nullptr;				//parent's right child is nullptr
		delete nodeDel;
	}
	//if the node to delete has only one child
	else if (nodeDel->left == nullptr) {					//if nodeDel doesn't have a left child
		if (nodeDel == root) {								//if the nodeDel is the root
			root = nodeDel->right;							//update root
			root->parent = nullptr;							//root has no parent
		}
		else if (nodeDel->isleftChild) {					//if nodeDel is left child
			nodeDel->parent->left = nodeDel->right;			//parent's left child is nodeDel's right child
			nodeDel->right->parent = nodeDel->parent;		//nodeDel's right child's parent is nodeDel's parent
		}
		else {												//if nodeDel is right child
			nodeDel->parent->right = nodeDel->right;		//parent's right child is nodeDel's right child
			nodeDel->right->parent = nodeDel->parent;		//nodeDel's right child's parent is nodeDel's parent
		}
		delete nodeDel;										
	}
	else if (nodeDel->right == nullptr) {					//if nodeDel doesn't have a right child
		if (nodeDel == root) {								//if nodeDel is the root
			root = nodeDel->left;							//update root
			root->parent = nullptr;							//root has no parent
		}
		else if (nodeDel->isleftChild) {					//if nodeDel is left child
			nodeDel->parent->left = nodeDel->left;			//parent's left child is nodeDel's left child
			nodeDel->left->parent = nodeDel->parent;		//nodeDel's left child's parent is nodeDel's parent
		}
		else {												//if nodeDel is right child
			nodeDel->parent->right = nodeDel->left;			//parent's right child is nodeDel's left child
			nodeDel->left->parent = nodeDel->parent;		//nodeDel's left child's parent is nodeDel's parent
		}
		delete nodeDel;									
	}
	//if the node to delete has two children
	else {
		RedBlackTreeNode* replacement = nodeDel->right;		//replacement node is nodeDel's right child
		while (replacement->left != nullptr) {				//while replacement is not nullptr, travel left
			replacement = replacement->left;
		}
		nodeDel->data = replacement->data;					//nodeDel data replaced by replacement node data
		del(nodeDel->right, replacement->data);				//recursively call delete function
	}
}

//pre, in, post order traversals
void RedBlackTree::inorder(RedBlackTreeNode* root) {
	if (root != nullptr) {
		inorder(root->left);			//L
		cout << root->data << " ";		//V
		inorder(root->right);			//R
	}
}
void RedBlackTree::preorder(RedBlackTreeNode* root) {
	if (root == nullptr)
		return;
	cout << root->data << " ";		//V
	preorder(root->left);			//L
	preorder(root->right);			//R
}
void RedBlackTree::postorder(RedBlackTreeNode* root) {
	if (root != nullptr) {
		postorder(root->left);		//L
		postorder(root->right);		//R
		cout << root->data << " ";  //V
	}
}

//print function calls traversal functions
void RedBlackTree::print() {
	preorder(root);
	cout << endl;
}

//destructor
RedBlackTree::~RedBlackTree() {
	delete root;
}
//copy constructor
RedBlackTreeNode* RedBlackTree::copy(RedBlackTreeNode* node) {
	if (node == nullptr)
		return nullptr;
	RedBlackTreeNode* newNode = new RedBlackTreeNode();
	newNode->data = node->data;
	newNode->left = copy(node->left);		//recursivley calls copy constructor for left chain
	newNode->right = copy(node->right);		//recursivley calls copy constructor for right chain
}
//operator overloading
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other) {
	if (this == &other)			//self-assignment, doesn't copy anything
		return *this;
	
	this->~RedBlackTree();		//delete the current tree
	
	if (other.root != nullptr)	//create a copy of the other tree
		root = new RedBlackTreeNode(*other.root);

	return *this;				//return the reference to this tree

}

//search for item in a tree
void RedBlackTree::search(int key) {
	if (root->data == key)
		cout << key << " exists in the tree." << endl;
	else
		search(root, key);
}
//search helper
void RedBlackTree::search(RedBlackTreeNode* helper, int key) {
	if (helper->data > key)
		search(helper->left, key);
	else if (helper->data < key)
		search(helper->right, key);
	else if (helper->data == key) {
		cout << key << " exists in the tree." << endl;
		return;
	}
	else if (helper == nullptr) {
		cout << key << " does not exist in the tree." << endl;
		return;
	}
		
}
