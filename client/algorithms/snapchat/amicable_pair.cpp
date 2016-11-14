/*
找Amicable Number Pairs
就是 数A 的所有因数(包括1，不包括A) 之和 等于 B。B的所有因数之和又刚好为A。 且 A != B.
求[1, N] 中所有符合条件的pair
*/

#include <iostream>
#include <vector>
using namespace std;

vector<pair<int, int>> amicable(int n){
	vector<pair<int, int>> result;

	vector<int> factorSum(n+1, 1);

	for(int i = 2;i<=n/2;i++ ){
		for(int j = 2*i; j<=n;j+=i){
			factorSum[j] += i;
		}
	}

	for(int i=1;i<=n;i++){
		if(i<factorSum[i] && factorSum[i]<=n && factorSum[factorSum[i]]==i){
			result.push_back({i, factorSum[i]});
		}
	}
	return result;
}

int main(){
	vector<pair<int, int>> res = amicable(100000);
	for(auto p : res){
		cout<<p.first<<", "<<p.second<<endl;
	}
	return 0;
}