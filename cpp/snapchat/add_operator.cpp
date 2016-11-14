/*
题目是给一个整数数组，其中所有数字都大于等于1。这些数字可以用加号，乘号和括号连接成一个表达式，求表达式的最大值。
二维DP搞定。给个一个数组[1,1,2,1]，然后用+ * （）三操作求出这个数组的最大值，这个题返回6。
Follow up是考虑0和负数。这时需要维护两个DP表，同时跟踪表达式的最大值和最小值。
*/
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int getMax(int nums[], int n){
	int dp[n][n];
	memset(dp, 0, sizeof(dp));
	for(int i = n-1; i>=0;i--){
		for(int j = i;j<n;j++){
			if(i==j) dp[i][j] = nums[i];
			else if(i+1==j) dp[i][j] = max(nums[i] + nums[j], nums[i]*nums[j]);
			else{
				for(int k = i; k<j;k++){
					dp[i][j] = max(dp[i][j], max(dp[i][k]+dp[k+1][j], dp[i][k]*dp[k+1][j]));
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<dp[i][j]<<" ";
		}
		cout<<endl;
	}
	return dp[0][n-1];
}

int main(){
	int arr[]={1,2,2,1};
	int res = getMax(arr, sizeof(arr)/sizeof(int));
	cout<<res<<endl;

	vector<int> v={1,2,3,4,5};
	vector<int> subv(v.begin(), v.begin()+3);
	for(int num:subv){
		cout<<num<<" ";
	}
	cout<<endl;
	return 0;
}