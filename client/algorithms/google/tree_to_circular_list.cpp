/*
Given a Binary Tree (Bt), convert it to a Doubly Linked List(DLL). 
The left and right pointers in nodes are to be used as previous and 
next pointers respectively in converted DLL. The order of nodes in 
DLL must be same as Inorder of the given Binary Tree. The first node 
of Inorder traversal (left most node in BT) must be head node of the DLL.
*/
#include <iostream>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    TreeNode(int x):val(x){}
};

void tree_to_list(TreeNode *root, TreeNode *&head, TreeNode *&pre){
	if(!root) return;
	tree_to_list(root->left, head, pre);
	if(!pre) head = root;
	else pre->right = root;
	root->left = pre;

	// at this time, we don't know if root is the last node
	// we just assume every root is last node and make its right link to head
	TreeNode *right = root->right;

	root->right = head;
	head->left = root;

	//update pre
	pre = root;

	tree_to_list(right, head, pre);
}

void print_list(TreeNode *head){
	TreeNode *temp = head;
	while(temp){
		cout<<temp->val<<endl;
		temp = temp->right;
		if(temp == head) break;
	}

	cout<<"tail's right: "<<temp->right->val<<endl;
	cout<<"head's left: "<<head->left->val<<endl;
}
int main(){
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	TreeNode *pre = nullptr, *head = nullptr;
	tree_to_list(root, head, pre);
	print_list(head);
	return 0;
}