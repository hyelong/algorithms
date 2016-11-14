/*
题目是给一个整数数组，其中所有数字都大于等于1。这些数字可以用加号，乘号和括号连接成一个表达式，求表达式的最大值。
二维DP搞定。给个一个数组[1,1,2,1]，然后用+ * （）三操作求出这个数组的最大值，这个题返回6。
Follow up是考虑0和负数。这时需要维护两个DP表，同时跟踪表达式的最大值和最小值。
*/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

vector<string> get_expression(vector<vector<int>> &dp, int start, int end, int target){
	vector<string> res;
	if(start==end) {
		res.push_back(to_string(dp[start][end]));
		return res;
	}
	
	for(int i=start; i<end;i++){
		if(dp[start][i]*dp[i+1][end]==target){
			vector<string> left = get_expression(dp, start,i, dp[start][i]);
			vector<string> right = get_expression(dp, i+1,end, dp[i+1][end]);
			for(string ls : left)
				for(string rs : right){
					string exp = "(" + ls + ") * (" + rs +")";
					res.push_back(exp);
				}
			 
		}

		if(dp[start][i] + dp[i+1][end]==target){
			vector<string> left = get_expression(dp, start,i, dp[start][i]);
			vector<string> right = get_expression(dp, i+1,end, dp[i+1][end]);
			for(string ls : left)
				for(string rs : right){
					string exp = "(" + ls + ") + (" + rs +")";
					res.push_back(exp);
				}
		}

	}
	return res;
}

vector<string>  getMax(int nums[], int n){
	vector<vector<int>> dp(n, vector<int>(n,0));
	for(int i = n-1; i>=0;i--){
		for(int j = i;j<n;j++){
			if(i==j) dp[i][j] = nums[i];
			else if(i+1==j) dp[i][j] = max(nums[i] + nums[j], nums[i]*nums[j]);
			else{
				for(int k = i; k<j;k++){ //here k must be smaller than j, otherwise K+1 will be bigger than j
					dp[i][j] = max(dp[i][j], max(dp[i][k]+dp[k+1][j], dp[i][k]*dp[k+1][j]));
				}
			}
		}
	}
	
	vector<string> res = get_expression(dp,0,n-1,dp[0][n-1]);

	return res;
}

int main(){
	int arr[]={1,1,2};
	vector<string> res = getMax(arr, sizeof(arr)/sizeof(int));
	for(string s : res)
	cout<<s<<endl;


	return 0;
}
