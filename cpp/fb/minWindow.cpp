/*
 * 问了一道题,minimum-window-substring。 写完了,老印没看懂,口述了一个 test case, 老印懂了。
 * 说 cool,cool
 * 之后老印就问了一个问题,我的这个 T 里面的字符都是 unique 的,你为什么要记录 T 里面的字符出现的
 * 次数?
 */
#include <iostream>
#include <unordered_set>
#include <climits>
using namespace std;
//all the characters in t are different
string minWindow(string& s, string& t){
  int len = t.length();
  if(len>s.length()) return "";
  unordered_set<char> chars;
  for(char c : t) chars.insert(c);
  int start = 0, end = 0, count=0;
  int min_window = INT_MAX;
  string res;
  for(int i=0;i<s.length(); i++){
    if(chars.count(s[i])) count++;
    end = i;
    while(start<=end && count==len){
      if(end-start+1<min_window){
        min_window = end-start+1;
        res = s.substr(start, min_window);
      }
      if(chars.count(s[start])) count--;
      start++;
    }
  }
  return res;
}

int main(){
  string s = "ADOBECODEBANC";
  string t = "ABC";
  string res = minWindow(s, t);
  cout<<res<<endl;
}
