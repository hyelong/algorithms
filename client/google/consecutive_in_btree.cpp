/*
Given a binary tree, find the length of the longest consecutive sequence path.

The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse).

For example,

全选复制放进笔记   
   1
    \
     3
    / \
   2   4
        \
         5 
Longest consecutive sequence path is 3-4-5, so return 3.

   2
    \
     3
    / 
   2    
  / 
 1 
Longest consecutive sequence path is 2-3,not3-2-1, so return 2.
*/
#include <iostream>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left = NULL;
    TreeNode *right = NULL;
    TreeNode(int x):val(x){}
};

int dfs(TreeNode* root, int count, int val){
    if(!root) return count;
    count = (root->val - val == 1)?count+1:1;
    int left = dfs(root->left, count, root->val);
    int right = dfs(root->right, count, root->val);
    return max(max(left, right), count);
}

int longestConsecutive(TreeNode* root) {
	if(!root) return 0;
	return max(dfs(root->left, 1, root->val), dfs(root->right, 1, root->val));
}


int main(){
	TreeNode *root = new TreeNode(2);
	root->right = new TreeNode(3);
	root->right->left = new TreeNode(2);
	root->right->left->left = new TreeNode(1);
	int res = longestConsecutive(root);
	cout<<res<<endl;

	return 0;
}