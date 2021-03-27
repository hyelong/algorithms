#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

bool helper(string& s, size_t index, unordered_set<string>& wordDict, unordered_map<int,bool>& dp){
    if(index==s.length()) return true;
    if(dp.find(index)!=dp.end()) return dp[index];
    for(size_t i = index; i<s.length();i++){
        string sub = s.substr(index, i+1-index);
        if(wordDict.find(sub)!=wordDict.end()){
            bool b = helper(s, i+1, wordDict, dp);
            dp[index]=b;
            if(b) return true;
        }
    }
    return false;
}

bool is_compound(string s, unordered_set<string>& wordDict) {
    if(wordDict.size()==0) return false;
    unordered_map<int,bool> dp;
    return helper(s,0,wordDict,dp);
}

vector<string> simples(string[] words){
    vector<string> res;
    unordered_set<string> wordDict;
    for(string word : words){
        wordDict.insert(word);
    }
    for(string word : words){
        wordDict.erase(word);
        if(!is_compound(word, wordDict)){
            res.push_back(word);
        }
        wordDict.insert(word);
    }    
    return res;
}

int main(){
    string[] words = {"chat", "ever",  "snapchat" ,"snap", "salesperson" ,"per", 
    "person", "sales" ,"son" ,"whatsoever" ,"what", "so"};
    vector<string> res = simples(words);
    for(string s:res)
        cout<<s<<endl;

    return 0;
}
