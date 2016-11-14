/*
 * 给一棵树，给一个target node和k值，要求得到所有跟target的距离等于k的treeNode
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x), left(NULL), right(NULL){}
};

void k_down(TreeNode* root, int k, vector<int>& res){
    if(!root || k<0) return;
    if(k==0){
        res.push_back(root->val);
        return;
    }
    k_down(root->left, k-1, res);
    k_down(root->right,k-1, res);
}
// distance between root and target
int distance(TreeNode* root, TreeNode* target, int k, vector<int>& res){
    if(!root) return -1;
    if(root==target){
        k_down(root, k, res);
        return 0;
    }

    int left = distance(root->left, target, k, res);
    int right = distance(root->right, target, k, res);

    if(left != -1){
        if(left == k-1) res.push_back(root->val);
        else k_down(root->right, k-1- left -1, res);
        return 1 + left;
    }

    if(right != -1){
        if(right == k-1) res.push_back(root->val);
        else k_down(root->left, k-1-right-1, res);
        return 1 + right;
    }

    return -1;
}

int main(){
    
}
