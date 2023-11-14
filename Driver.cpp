#include "RedBlackTree.h"
#include "RedBlackTreeNode.h"
#include <iostream>
using namespace std;

int main() {
	RedBlackTree* tree = new RedBlackTree();
	
	//original tree prints first
	tree->insert(4);
	tree->insert(30);
	tree->insert(13);
	tree->insert(7);
	tree->insert(18);
	tree->insert(1);
	tree->insert(20);
	tree->insert(28);
	tree->insert(29);
	tree->insert(35);
	tree->print();
	cout << endl;
	
	//searches for 20
	tree->search(20);
	cout << endl;

	//deletes 28 and 35 then prints
	tree->del(28);
	tree->del(35);
	tree->print();
	cout << endl;

	//new tree object and prints it
	RedBlackTree* newTree;
	//calls assignment operator overloaded function, copies original tree
	newTree = tree;
	newTree->print();
	cout << endl;

	//creates newnewTree object and sets it equal to newTree
	//calls copy constructor and prints
	RedBlackTree* newnewTree = newTree;
	newnewTree->print();

	//deletes tree, calls destructor
	delete tree;


	return 0;
}