/*
给一个string,可以add/delete/change，还可以combine几种来使他变为合法的palindrome,问最少需要几步。
比如：ebabc可以把c改成e
*/
#include <iostream>
#include <vector>
using namespace std;

int toPalidrome(string s){
	vector<vector<int>>  dp(s.size(), vector<int>(s.size()));
	for(int i=0; i<s.size(); i++){
		for(int j=i; j>=0; j--){
			if(i-j==0)	dp[j][i] = 0;
			else if(i-j==1)	dp[j][i] = s[j]==s[i] ? 0 : 1;
			else{
				if(s[j]==s[i])	dp[j][i] = dp[j+1][i-1];
				else dp[j][i] = min(dp[j+1][i-1], min(dp[j+1][i], dp[j][i-1])) + 1;
			}
		}
	}
	return dp[0][s.size()-1];
}

int main(){
	string s = "debabcd";
	int res = toPalidrome(s);
	cout<<res<<endl;
	return 0;
}