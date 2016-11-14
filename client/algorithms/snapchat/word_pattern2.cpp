/*
Problem Description:

Given a pattern and a string str, find if str follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

Examples:

pattern = "abab", str = "redblueredblue" should return true.
pattern = "aaaa", str = "asdasdasdasd" should return true.
pattern = "aabb", str = "xyzabcxzyabc" should return false. 
Notes:
You may assume both pattern and str contains only lowercase letters.
*/

#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    bool wordPatternMatch( string& pattern,  string& str) {
        unordered_set<string> visited;
        unordered_map<char, string> mp;
        return match(str, 0, pattern, 0, visited, mp);
    }
private:
    bool match(string& str, int i, string& pat, int j, unordered_set<string>& visited,
    	 unordered_map<char, string>& mp) {
        int m = str.length(), n = pat.length();
        if (i == m && j == n) return true;
        if (i == m || j == n) return false;
        char c = pat[j];
        if (mp.find(c) != mp.end()) {
            string s = mp[c];
            int l = s.length();
            if (s != str.substr(i, l)) return false;
            return match(str, i + l, pat, j + 1, visited, mp);
        } 
        for (int k = i; k < m; k++) {
            string s = str.substr(i, k - i + 1);
            if (visited.find(s) != visited.end()) continue;
            visited.insert(s);
            mp[c] = s;
            if (match(str, k + 1, pat, j + 1, visited, mp)) return true;
            visited.erase(s);
            mp.erase(c);
        }
        return false;
    }
};

int main(){
	Solution sol;
	string pattern = "abab";
	string s = "redblueredblue";
	bool res = sol.wordPatternMatch(pattern, s);
	cout<<res<<endl;
	return 0;
}