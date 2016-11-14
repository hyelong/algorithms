#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TreeNode{
	int val;
	TreeNode* left=NULL;
	TreeNode* right=NULL;
	TreeNode(int x):val(x){}
};

TreeNode* helper(vector<int> inorder, vector<int> postorder, int is, int ie, 
					int ps, int pe,unordered_map<int, int>& indexes){
	if(is>ie) return NULL;
	TreeNode *root = new TreeNode(postorder[pe]);
	int index = indexes[postorder[pe]];
	root->left = helper(inorder, postorder, is, index-1, ps, ps + index-1-is, indexes);
	root->right = helper(inorder, postorder, index+1, ie, pe-ie+index, pe-1, indexes);
	return root;
}

TreeNode* rebuild(vector<int> inorder, vector<int> postorder){
	int n = inorder.size();
	unordered_map<int, int> indexes;
	for(int i=0;i<n;i++){
		indexes[inorder[i]] = i;
	}
	return helper(inorder, postorder, 0, inorder.size()-1, 0, postorder.size()-1, indexes);
}

void print(TreeNode *root){
	if(!root) return;
	cout<<root->val<<" ";
	print(root->left);
	print(root->right);
}

int main(){
	vector<int> inorder = {2,1,3};
	vector<int> postorder = {2,3,1};
	TreeNode* root = rebuild(inorder, postorder);
	
	print(root);
	return 0;
}