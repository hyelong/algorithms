#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    // Initialize your data structure here.
    TrieNode() {

    }
    bool wordEnd = false;
    unordered_map<char, TrieNode*> children;
};

class Trie {
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
    // Returns if the word is in the trie.
    bool search(string word) {
        TrieNode * cur = root;
        int i = 0;
        while(i < word.length() && cur){
            char c = word[i];
            if(cur->children.count(c)==0) return false;
            cur = cur->children[c];
            i++;
        }
        return cur->wordEnd;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix) {
        TrieNode * cur = root;
        int i = 0;
        while(i < prefix.length() && cur){
            char c = prefix[i];
            if(cur->children.count(c)==0) return false;
            cur = cur->children[c];
            i++;
        }
        return true;
    }
    
    vector<string> getCandidates(string prefix){
      vector<string> res;
      TrieNode * cur = root;
      int i = 0;
      while(i < prefix.length() && cur){
          char c = prefix[i];
          if(cur->children.count(c)==0) return res;
          cur = cur->children[c];
          i++;
      }
      dfs(cur,prefix,res);
      return res;
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

private:
    TrieNode* root;
};

int main(){
  Trie trie;
  trie.insert("ab");
  trie.insert("abcd");
  trie.insert("abcde");
  trie.insert("abcdef");
  auto res = trie.getCandidates("abc");
  for(string s : res)
    cout<<s<<endl;
  return 0;
}