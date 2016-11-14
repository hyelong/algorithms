/*vertical traverse a binary tree*/
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left = NULL;
    TreeNode *right = NULL;
    TreeNode(int x):val(x){}
};

vector<vector<int>> verticalOrder(TreeNode* root) {
    map<int, vector<int>> mp;
    queue<pair<int, TreeNode*>> q;
    vector<vector<int>> ret;
    if(root) q.push({0, root});
    while(!q.empty()){
        auto p = q.front();
        q.pop();
        mp[p.first].push_back(p.second->val);
        if(p.second->left) q.push({p.first-1, p.second->left});
        if(p.second->right) q.push({p.first+1, p.second->right});
    }
    for(auto it=mp.begin(); it!=mp.end(); ++it)
        ret.push_back(it->second);
    return ret;
}

int main(){
    return 0;
}