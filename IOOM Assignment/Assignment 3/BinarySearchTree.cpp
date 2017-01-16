#include <bits/stdc++.h>
#include "BinarySearchTree.h"
using namespace std;
#define type char

template <size_t T>
struct{
	typedef struct node{
	    T key;
	    struct node *left, *right;
	}treeNode;
};

template <class T>
BST<T>::BST(){
	root=NULL;
}

template <class T>
treeNode* BST<T>::newNode(T item){
	treeNode *temp =  (treeNode *)malloc(sizeof(treeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
template <class T>
void BST<T>::inorder(treeNode *node){
	if (node != NULL){
		inorder(node->left);
		cout<<node->key<<"\t";
		inorder(node->right);
	}
}
template <class T>
void BST<T>::inorder(){
			
	if(root!=NULL){
		cout<<"The elements in the tree are: \n";
		inorder(root);
	}
	else{
		cout<<"The tree is empty!";
	}
	cout<<endl;
}
template <class T>
treeNode* BST<T>::insert(treeNode* node, T key){

	if (node == NULL) 
		return newNode(key);
		 
	if (key < node->key)
		node->left  = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);   
		 
    return node;
}

template <class T>
void BST<T>::insert(T key){
		    root=insert(root,key);
}		

template <class T>
bool BST<T>::search(treeNode *node, T key){
	if(node==NULL)
		return false;

	if(node->key==key)
		return true;

	if(node->right!=NULL && key>node->key){
		return search(node->right,key);
	}
	else if(node->left!=NULL){
		return search(node->left,key);
	}
	else{
		return false;
	}
}
		template <class T>
		void BST<T>::search(T key){
			if(search(root,key)){
				cout<<"The given key exists in the tree!\n";
			}
			else{
				cout<<"The given key does not exist in the tree!\n";
			}
		}

		treeNode * BST<T>::minValueNode(treeNode* node){

		    treeNode* current = node;
		 
		    /* loop down to find the leftmost leaf */
		    while (current->left != NULL)
		        current = current->left;
		 
		    return current;
		}
		
		template <class T>
		treeNode* BST<T>::deleteNode(treeNode* node, T key){

		    if (node == NULL) return node;
		 
		    if (key < node->key)
		        node->left = deleteNode(node->left, key);

		    else if (key > node->key)
		        node->right = deleteNode(node->right, key);
		 
		    else{
		        if (node->left == NULL)
		        {
		            treeNode *temp = node->right;
		            free(node);
		            return temp;
		        }
		        else if (node->right == NULL)
		        {
		            treeNode *temp = node->left;
		            free(node);
		            return temp;
		        }
		 
		        treeNode* temp = minValueNode(node->right);
		 
		        node->key = temp->key;
		 
		        node->right = deleteNode(node->right, temp->key);
		    }
		    return node;
		}
		template <class T>
		void BST<T>::deleteNode(T key){
			if(search(root, key)){
				treeNode *node=deleteNode(root,key);
				if(node!=NULL){
					root=node;
					cout<<"The key was deleted successfully!\n";
				}
				else{
					root=NULL;
					cout<<"The key was deleted successfully!\n";
					cout<<"Tree has become empty.\n";
				}
			}
			else{
				cout<<"The given key does not exist in the tree!\n";
			}
		}

int main(int argc, char const *argv[])
{
	int exit=0;
	BST<type> b;

	while(!exit){
		cout<<"1.Insert\n2.Delete\n3.Search\n4.Print\n5.Exit\n";
		int choice;
		type value;
		cin>>choice;
		
		switch(choice){
			case 1: cout<<"Enter the value you want to insert : "; 
					cin>>value;
					b.insert(value);
					break;
			case 2: cout<<"Enter the value you want to delete : ";
					cin>>value;
					b.deleteNode(value);
					break;
			case 3: cout<<"Enter the value to be searched : ";
					cin>>value;
					b.search(value);
					break;
			case 4: b.inorder();
					break;
			case 5: exit=1;
					break;	
		}
	}
	return 0;
}
