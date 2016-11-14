/*implement terminal tab function*/

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {

    }
    bool wordEnd = false;
    map<char, TrieNode*> children;
};

class Trie {
	TrieNode *root = NULL;
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string word) {
        TrieNode *cur = root;
        int i = 0;
        while(i < word.length() && cur){
            char c = word[i];
            if(cur->children.count(c)==0){
                cur->children[c] = new TrieNode();
            }
            cur = cur->children[c];
            i++;
        }
        cur->wordEnd = true;
    }

    vector<string> tab(string prefix){
    	vector<string> res;
        TrieNode * cur = root;
        int i = 0;
        while(i < prefix.length() && cur){
            char c = prefix[i];
            if(cur->children.count(c)==0) return res;
            cur = cur->children[c];
            i++;
        }

        tab(cur, prefix, res);
        if(res.size()==0){
        	dfs(cur, prefix, res);
        }
        return res;
    }

    void tab(TrieNode *cur, string& prefix, vector<string>& res){
    	if(!cur) return;
    	if(cur->wordEnd) {
    		res.push_back(prefix);
    		return;
    	}
    	int len = 0;
    	auto it = cur->children.begin();
    	while(it!=cur->children.end()){
    		it++;
    		len++;
    	}
    	if( len > 1 || len==0) return;

    	prefix += (cur->children.begin()->first);

    	tab(cur->children.begin()->second, prefix, res);
    }

	void dfs(TrieNode* cur, string candidate, vector<string>& res){
      if(cur->wordEnd){
        res.push_back(candidate);
        // we don't return here, otherwise only the first result returns.
      }

      for(auto it = cur->children.begin(); it!=cur->children.end(); it++){
        dfs(it->second, candidate + it->first , res);
      }
    }
};

int main(){
	Trie trie;
    trie.insert("ab");
    trie.insert("ac");
    trie.insert("ad");
    trie.insert("abcd");
    trie.insert("abcde");
    trie.insert("abcdef");
    vector<string> res = trie.tab("ab");
    for(string s : res)
    	cout<<s<<endl;
	return 0;
}