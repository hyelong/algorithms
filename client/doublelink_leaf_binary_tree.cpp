/*double link leaf nodes*/

#include <iostream>
using namespace std;

struct TreeNode{
	int val;
	TreeNode *left = NULL;
	TreeNode *right = NULL;
	TreeNode(int x):val(x){}
};

struct DoubleLinkedList
{
	int val;
	DoubleLinkedList *pre = NULL;
	DoubleLinkedList *next = NULL;
	DoubleLinkedList(int x):val(x){}
};

void link_leaves(TreeNode *root, DoubleLinkedList *&head, DoubleLinkedList*& cur, DoubleLinkedList *&pre){
	if(!root) return;
	if(!root->left && !root->right){
		if(!head){
			head = new DoubleLinkedList(root->val);
			cur = head;
		}
		else{
			cur = new DoubleLinkedList(root->val);
		}
		if(pre) pre->next = cur;
		cur->pre = pre;
		pre = cur;
	}

	link_leaves(root->left, head, cur, pre);
	link_leaves(root->right, head, cur, pre);

}

void print_list(DoubleLinkedList *head){
	DoubleLinkedList *temp = head;
	while(temp){
		cout<<temp->val<< " ";
		temp = temp->next;
		if(temp == head) break;
	}
}
int main(){
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = new TreeNode(4);
	root->left->right = new TreeNode(5);
	DoubleLinkedList *head = NULL;
	DoubleLinkedList *cur = NULL;
	DoubleLinkedList *pre = NULL;
	link_leaves(root, head,cur, pre);
	cur->next = head;
	head->pre = cur;
	print_list(head);
	return 0;
}