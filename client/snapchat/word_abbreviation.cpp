/*
word abbreviation 

题意：  我们通常压缩的时候会把  interval 压缩成 i8l, 即首尾字母加这个word的长度。 
1. 但是研究人员发现， internal 和 interval  如果按上面那种方法就会模糊不清，因为都会压缩成 i8l. 于是研究人员就想到一个办法，就是加长它们的prefix, 直到遇到它们第一个不同的字母，
比如：internal 和 interval 会压缩成： intern8l, interv8l.
          intension 和 intrusion  会变成： inte9n, intr9n

2. 当 压缩完后， 发现压缩后的长度 大于等于 原始长度时， 保留原始长度。比如 intern8l  长度也是 8， 那么就 保留原始： internal.

(例子我自己举的， 大概这意思)
input: 是一个 string
like god  internal me internet interval intension face intrusion

output: l2e god internal me i8t interval inte9n f2e intr9n
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct TrieNode
{
	bool woedEnd = false;
	TrieNode* children[26];
	int count = 0;
	TrieNode(){
		for(int i = 0; i<26;i++)
			children[i] = NULL;
	}
};

struct Trie
{
	void insert(string word, TrieNode* root){
		TrieNode *cur = root;
		int i = 0;
		while(i < word.size()){
			int index = word[i] - 'a';
			if(!cur->children[index])
				cur->children[index] = new TrieNode();

			cur->children[index]->count++;

			cur = cur->children[index];
			i++;
		}
	}

	string unique_prefix(string word, TrieNode* root){
		TrieNode *cur = root;
		int i = 0;
		string prefix;
		while(i < word.size()){
			char c = word[i];
			prefix += c;
			if(cur->children[c-'a']->count == 1) return prefix;

			cur = cur->children[c-'a'];
			i++;
		}
	}
};

vector<string> word_abbre(vector<string> words){
	vector<string> res;
	Trie trie;
	unordered_map<int, TrieNode*> wordTrie;

	for(string word : words){
		int len = word.size();
		if(!wordTrie.count(len)){
			wordTrie[len] = new TrieNode();
		}

		trie.insert(word, wordTrie[len]);
	}

	for(string word : words){
		int len = word.size();
		if(len <= 3) {
			res.push_back(word);
			continue;
		}

		TrieNode *root = wordTrie[len];
		string prefix = trie.unique_prefix(word, root);
		string encoded = prefix + to_string((len - 1 - prefix.size())) + word.back();
		if(encoded.size() < len) res.push_back(encoded);
		else res.push_back(word);
	}

	return res;
}

int main(){
	vector<string> words = {"like","god","internal", "me","internet","interval","intension","face","iiiiiiiiiiiiintrusion"};
	vector<string> res = word_abbre(words);
	for(string s : res){
		cout<<s<<endl;
	}

	return 0;
}



