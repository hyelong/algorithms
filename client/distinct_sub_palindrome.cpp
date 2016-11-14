/*Return the number of distinct palindromic substrings for a given string*/

#include <unordered_set>
#include <iostream>
using namespace std;


int distinct_sub_palindrome(string& s){
	unordered_set<string> res;
	for(char c : s){
		res.insert(string(1,c));
	}

	for(int i=0;i<s.length();i++){
		int start = i-1, end = i+1;
		if(start>=0 && end<s.length() && s[start]==s[end]){
			res.insert(s.substr(start, end - start + 1));
			start--;
			end++;
		}

		start = i, end = i+1;
		if(start>=0 && end<s.length() && s[start]==s[end]){
			res.insert(s.substr(start, end - start + 1));
			start--;
			end++;
		}
	}

	return res.size();
}

int main(){
	string s = "geek";
	cout<<distinct_sub_palindrome(s)<<endl;
	return 0;
}