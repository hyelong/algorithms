#include<iostream>
using namespace std;

struct TreeNode{
	int val;
	TreeNode* left = NULL;
	TreeNode* right = NULL;
	TreeNode(int x):val(x){}
};

void printTree(TreeNode* root){
	if(!root) return;
	printTree(root->left);
	cout<<root->val<<endl;
	printTree(root->right);
}

bool bst_insert(TreeNode** node, int key){
	if(! (*node)){
		TreeNode *newNode = new TreeNode(key);
		*node = newNode;
		return true;
	}
	if((*node)->val==key) return false;
	else if((*node)->val<key){
		bst_insert(&((*node)->right), key);
	}
	else{
		bst_insert(&((*node)->left), key);
	}
}



int main(){
	TreeNode *root = new TreeNode(3);
	bst_insert(&root, 1);
	bst_insert(&root, 2);
	printTree(root);
	return 0;
}
