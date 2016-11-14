/*
第一个问题，f(n) = 3n + 1 (if n is odd) or n / 2 (if n is even)，
collapse sequense指每个数按照这个公式递推直到变为1的所有sequence，
求前10000个数中collapse sequense最长的数
*/
#include <iostream>
#include <unordered_map>
using namespace std;

unordered_map<int, int> memoization;
int collapse(int n){
	if(memoization.count(n)) {
		//cout<<n<<" is calcutated: "<< memoization[n]<<endl;
		return memoization[n];
	}
	int res;
	if(n == 2) return 1;
	if(n % 2 == 0){
		res = collapse(n/2) + 1;
	}
	else{
		res = collapse(3*n + 1) + 1;
	}
	memoization[n] = res;
	return res;
}

int main(){
	int count = 1;
	int max_count = 0;
	int res = 0;
	for(int i=1;i<=10000;i++){
		count = collapse(i);
		if(count > max_count){
			max_count = count;
			res = i;
		}
	}
	cout<<res<<endl;
	return 0;
}