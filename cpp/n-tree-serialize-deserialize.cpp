#include <vector>
#include <iostream>
#include <string>
#include <stack>
using namespace std;

struct Node{
    char val;
    vector<Node*> children;
    Node(char value):val(value){}
};


void serialize(Node *root, string& res){
    if(!root) return;
    res.append(1,root->val).append(1,' ');
    for(int i=0;i<root->children.size();i++){
        serialize(root->children[i], res);
    }
    res += ") ";
}

Node* deSerialize(string& data){
    stack<Node*> st;
    for(int i=0;i<data.length();i++){
        if(data[i]!=')' && data[i]!=' '){
            Node* node = new Node(data[i]);
            st.push(node);
        }
        else if(data[i]==')'){
            if(st.size()>1){
                Node* curr = st.top();
                st.pop();
                st.top()->children.push_back(curr);
            }
        }
    }
    return st.top();
}
int main(){
    Node *root = new Node('A');
    root->children.push_back(new Node('B'));
    root->children.push_back(new Node('C'));
    root->children[1]->children.push_back(new Node('D'));
    string res=""; 
    serialize(root,res);
    cout<<res<<endl;
    root = deSerialize(res);
    cout<<root->children[1]->children[0]->val<<endl;
    return 0;
}
