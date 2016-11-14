/*
 * Given a string, every step you can add/delete/change one character at any position.
 * Minimize the step number to make it a palindrome. 
 *
 */

#include <iostream>
#include <vector>
using namespace std;

int min_step_palindrome(string& s){
  int n = s.length();
  vector<vector<int>> dp(n, vector<int>(n, 0));
  for(int i=0; i<n;i++){
    for(int j=i;j>=0;j--){
      if(i==j) dp[j][i] = 0;
      else if(i-j==1) dp[j][i] = s[j]==s[i]?0:1; 
      else{
        if(s[j]==s[i]) dp[j][i]=dp[j+1][i-1];
        else dp[j][i] = 1+min(dp[j+1][i-1], min(dp[j+1][i], dp[j][i-1]));
      }
    }
  }
  return dp[0][n-1];
}

int main(){
  string s = "abc";
  int res = min_step_palindrome(s);
  cout<<res<<endl;
  return 0;
}
