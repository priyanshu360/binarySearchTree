/*
 * 
 * 	This file contains an implementation of Binary Search Tree. A a binary search tree (BST), 
 *  also called an ordered or sorted binary tree, is a rooted binary tree whose 
 *  internal nodes each store a key greater than all the keys in the node's left subtree
 *  and less than those in it's right subtree. 
 * 
 * 		@author Priyanshu Rajput, priyanshurajput360@gmail.com
 * 
 */

#ifndef BST_H
#define BST_H
#include <iostream>

template <class T> class Node{
	public:
		Node<T> *left, *right;
		T key;
		void addLeft(T data) 	{ this->l = new Node(data); }
		void addRight(T data) 	{ this->r = new Node(data); }
		
		Node<T>(T data){
			this->left = NULL;
			this->right = NULL;
			this->key = data;
			return;
		}
		
		Node<T>(){
			return;
		}
};



template <class T> class Bst : public Node<T> {
	private:
		Node<T> *root = NULL;
		int nodesCount = 0;
		bool find(Node<T>* node, T key);
		
		Node<T> *getMin(Node<T> *node);
		int height(Node<T> *node);
		
		void inOrderTraversal(Node<T> *node);
		void preOrderTraversal(Node<T> *node);
		void postOrderTraversal(Node<T> *node);
	
	public:
		
		int size()                      {  return nodesCount;       }
		bool isEmpty()                  {  return (!nodesCount);    }
		bool add(T data);
		bool remove(T data);
		
		bool find(T data){
			if(isEmpty()){
				return false;
			}
			return find(root, data);
		}
		
		int height(){
			if(isEmpty()){
				return 0;
			}
			return height(root);
		}
		
		void inOrderTraversal()		    {  return inOrderTraversal(root);	}
		void preOrderTraversal()		{  return preOrderTraversal(root);	}
		void postOrderTraversal()		{  return postOrderTraversal(root);	}
};


//method to find an element in the tree
template <class T> bool Bst<T>::find(Node<T>* temp, T data){
	
	while(temp != NULL && temp->key != data){
		if(temp->key > data){
			
			// Dig into the left subtree because the value we're
			// looking for is smaller than the current value
			temp = temp->left;
		}
		else{
			
			// Dig into the right subtree because the value we're
			// looking for is greater than the current value
			temp = temp->right;
		}
	}
	
	if(temp == NULL){
		
		// value not found
		return false;
	}
	else{
		
		// We found the value we were looking for
		return true;
	}
}





// add a value to this binary tree if it does not exists, O(n)
template <class T> bool Bst<T>::add(T data){
	
	// Check if the value already exists in this
    // binary search tree, if it does ignore adding it
    if(find(data)){
		return false;
	}
	
	// Otherwise add this element to the binary search tree
	else{
		Node<T> *temp = this->root;
		Node<T> *prev = NULL;
		while(temp != NULL){
			prev = temp;
			if(temp->key > data){
				temp = temp->left;
			}
			else{
				temp = temp->right;
			}
		}
		if(this->root == NULL) root = new Node(data);
		else{
			if(prev->key > data){
				prev->left = new Node(data);
			}
			else{
				prev->right = new Node(data);
			}
		}
		nodesCount++;
		return true;
	}
} 



// Remove a value from this binary tree if it exists, O(n)
template <class T> bool Bst<T>::remove(T data){
	
	// Check if the value exists in this
    // binary tree, if it does not return false
    if(find(data) == false){
		return false;
	}
	
	// Otherwise remove this element from the binary search tree
	else{
		
		// search for the node having key equal to node to be removed
		Node<T> *temp = root;
		Node<T> *prev = NULL;
		while(temp->key != data){
			prev = temp;
			if(temp->key > data){
				
				// Dig into left subtree, the value we're looking
				// for is smaller than the current value
				
				temp = temp->left;
			}
			else{
				
				// Dig into right subtree, the value we're looking
				// for is greater than the current value
      
				temp = temp->right;
			}
		}

		// Found the node we wish to remove
		
		
		if(temp->left == NULL){
			

			// This is the case with only a right subtree or
			// no subtree at all. In this situation just
			// swap the node we wish to remove with its right child.
			if(temp == root){
				if(root->right != NULL){
					root = root->right;
				}
				else root = NULL;
			}
			else if(temp->right != NULL){
				if(prev->key > data){
					prev->left = temp->right;
				}
				else{
					prev->right = temp->right;
				}
			}
			else{
				if(prev->key > data){
					prev->left = NULL;
				}
				else{
					prev->right = NULL;
				}
			}
			delete temp;
		}
		
		
		else if(temp->right == NULL){
			
			// This is the case with only a left subtree
			// swap the node we wish to remove with its left child.
			
			if(temp == root){
				root = root->left;
			}
			else{
				if(prev->key > data){
					prev->left = temp->left;
				}
				else{
					prev->right = temp->left;
				}
			}
			delete temp;
		}
		else{
			
			// When removing a node from a binary tree with two links the
			// successor of the node being removed can either be the largest
			// value in the left subtree or the smallest value in the right
			// subtree. In this implementation I have decided to find the
			// smallest value in the right subtree which can be found by
			// traversing as far left as possible in the right subtree.
			
			Node<T> *change = getMin(temp->right);
			T tempkey = change->key;
			change->key = data;
			temp->key = tempkey;
			remove(data);
		}
		nodesCount--;
		return true;
	}
}


// Helper method to find the leftmost node (which has the smallest value)
template <class T> Node<T> *Bst<T>::getMin(Node<T>* node){
	while(node->left != NULL){
		node = node->left;
	}
	return node;
}


// Computes the height of the tree, O(n)
// Recursive helper method to compute the height of the tree
template <class T> int Bst<T>::height(Node<T>* node){
	if(node == NULL){
		return 0;
	}
	return std::max(height(node->left), height(node->right)) + 1;
}




// Recursive function to traverse and print nodes value via inorder traversal in O(n)
template <class T> void Bst<T>::inOrderTraversal(Node<T> *node){
	if(node == NULL) return;
	
	inOrderTraversal(node->left);
	std::cout << node->key << " ";
	inOrderTraversal(node->right);
}

// Recursive function to traverse and print nodes value via preorder traversal in O(n)
template <class T> void Bst<T>::preOrderTraversal(Node<T> *node){
	if(node == NULL) return;
	
	std::cout << node->key << " ";
	preOrderTraversal(node->left);
	preOrderTraversal(node->right);
}

// Recursive function to traverse and print nodes value via postorder traversal in O(n)
template <class T> void Bst<T>::postOrderTraversal(Node<T> *node){
	if(node == NULL) return;
	
	postOrderTraversal(node->left);
	postOrderTraversal(node->right);
	std::cout << node->key << " ";
}



#endif
