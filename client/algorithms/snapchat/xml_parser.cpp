/*
题目问了XML parser, LZ不熟悉XML，就改成了HTML Parser, 本质上一样
输入是一个tokenizer对象，可以调用其getNextToken()函数获得下一个token, 
token结构包括name和tag，name就是具体的文字，tag有open,close,text三种，让把所有的token建成一棵树
比如：
       <html>
            <user>
                <id>aa</id>
                <meta>bb</meta>
            </user>
       </html>

得到的token就是
("html","open")
("user","open")
("id","open")
("aa","text")
("id","close")
("meta","open")
("bb","text")
("meta","close")
("user","close")
("html","close")

LZ的方法是用stack来存parent, 遇到open和text建新node, 并把新node加到stack顶部node的child list里面，如果是open就把新node压栈，遇到close就pop掉stack顶端的node. 涓€浜�-涓夊垎-鍦帮紝鐙鍙戝竷
写完以后小哥的follow up是如果输入的token有问题，比如close tag和open tag不匹配，如何做verification。LZ加了几行判断的code以后，小哥说他木有follow up了
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct XMLNode{
	string value;
	string tag;
	vector<XMLNode*> children;
	XMLNode(string v, string t):value(v), tag(t){}
};

XMLNode buildTree(vector<pair<string, string>>& input){
	int n = input.size();
	stack<XMLNode*> st;
	XMLNode *root = NULL;
	for(auto item : input){
		if(item.second == "open"){
			XMLNode *node = new XMLNode(item.first, item.second);
			if(!root) root = node;
			if(!st.empty()){
				st.top()->children.push_back(node);
			}
			st.push(node);
		}
		else if(item.second=="close"){
			if(!st.empty()){
				if(st.top()->value == item.first){
					st.pop();
				}
			}
		}else if(item.second=="text"){
			XMLNode *node = new XMLNode(item.first, item.second);
			if(!st.empty()){
				st.top()->children.push_back(node);
			}
		}
	}
	if(st.size()==0) cout<<"no open left"<<endl;
	return *root;
}

int main(){
	vector<pair<string, string>> input = {{"html", "open"},{"user","open"},{"id","open"},{"aa","text"},
	{"id","close"},{"meta","open"},{"bb","text"},{"meta","close"},{"user","close"},{"html","close"}};
	XMLNode root = buildTree(input);
	cout<<root.children[0]->children[1]->children[0]->value<<endl;
	return 0;
}
