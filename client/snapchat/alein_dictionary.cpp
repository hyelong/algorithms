/*
Problem Description:

There is a new alien language which uses the latin alphabet. However, the order among letters are unknown to you. You receive a list of words from the dictionary, wherewords are sorted lexicographically by the rules of this new language. Derive the order of letters in this language.

For example,
Given the following words in dictionary,

[
  "wrt",
  "wrf",
  "er",
  "ett",
  "rftt"
]
The correct order is: "wertf".

Note:

1, You may assume all letters are in lowercase.
2, If the order is invalid, return an empty string.
3, There may be multiple valid order of letters, return any one of them is fine.
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

string alienOrder(vector<string>& words) {
    unordered_map<char, unordered_set<char>> suc, pre;
    unordered_set<char> chars;
    string s;
    for (string t : words) {
        chars.insert(t.begin(), t.end());
        for (int i=0; i < min(s.size(), t.size()); ++i) {
            char a = s[i], b = t[i];
            if (a != b) {
                suc[a].insert(b);
                pre[b].insert(a);
                break;
            }
        }
        s = t;
    }
    unordered_set<char> free = chars;
    for (auto p : pre)
        free.erase(p.first);
   
    string order;
    while (free.size()) {
        char a = *free.begin();
        free.erase(a);
        order += a;
        for (char b : suc[a]) {
            pre[b].erase(a);
            if (pre[b].empty())
                free.insert(b);
        }
    }
    return order.size() == chars.size() ? order : "";
}

int main(){
    vector<string> words = {"za","zb","ca","cb"};
    string res = alienOrder(words);
    cout<<res<<endl;

    return 0;
}
