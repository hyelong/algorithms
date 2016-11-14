/*
AB两个人轮流取 都只能从头或者尾里选一个取， A 先。 B采用的是GREEDY方法 也就是B一定是取头、
尾里面最大的那一个。问A能取到的最大值。
比如说2 4 7 3，A可以先取3， B肯定取7，A再取4，B取2， 这样A取到的和是7。 
另外就是A先取2， B只能在3和4里面选  B因为是GREEDY 所以肯定选4， 那么A就能取7，这样A取到的和是9。 9>7所以返回9.
*/

#include <iostream>
#include <cstring>
#include <cstring>
using namespace std;

int helper(int arr[], int start, int end, int** dp){
	if(dp[start][end]) {
		cout<<"calculated"<<endl;
		return dp[start][end];
	}
	if(start==end) return arr[start];
	if(end-start==1) return max(arr[start], arr[end]);
	int option1 = arr[start];
	if(arr[start+1]>arr[end]){
		option1 += helper(arr, start+2, end, dp);
	}
	else{
		option1 += helper(arr, start+1, end-1, dp);
	}

	int option2 = arr[end];
	if(arr[start]>arr[end-1]){
		option2 += helper(arr, start+1, end-1, dp);
	}
	else{
		option2 += helper(arr, start, end-2, dp);
	}
	int res = max(option1, option2);
	dp[start][end] = res;
	return res;
}
int max_sum(int arr[], int length){
	if(length==0) return 0;
	int **dp = new int* [length];
	for(int i=0;i<length;i++){
		dp[i] = new int[length];
		memset(dp[i], 0, sizeof(dp[i]));
	}
	return helper(arr, 0, length-1, dp);
}

int main(){
	int arr[]={2,4,7,3,8,10,5,17};
	int res = max_sum(arr, sizeof(arr)/sizeof(int));
	cout<<res<<endl;
	return 0;
}