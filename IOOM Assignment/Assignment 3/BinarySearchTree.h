#include <bits/stdc++.h>
using namespace std;



template <class T>
class BST{

	typedef struct node{
	    T key;
	    struct node *left, *right;
	}treeNode;

	treeNode *root;

	public:

		BST();
		
		treeNode *newNode(T item);

		void inorder(treeNode *node);

		void inorder();

		treeNode* insert(treeNode* node, T key);

		void insert(T key);
		
		bool search(treeNode *node, T key);
		
		void search(T key);

		treeNode * minValueNode(treeNode* node);
		
		treeNode* deleteNode(treeNode* node, T key);
		
		void deleteNode(T key);
};


