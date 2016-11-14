/*给一个数组，返回左边之和等于右边之和的那个index， 没有就返回-1，比如{1,2,3,2,1}， 返回2*/
#include <iostream>
#include <vector>
using namespace std;

vector<int> getIndices(vector<int>& nums){
	int total = 0;
	for(int num : nums){
		total += num;
	}
	int left_sum = 0;
	vector<int> res;
	for(auto i=0;i<nums.size();i++){
		if(2*left_sum + nums[i]==total){
			res.push_back(i);
		}
		left_sum += nums[i];
	}
	//if(res.size()==0) return -1;
	return res;
}

int main(){
	vector<int> arr = {1,2,3,2,1};
	arr = {1,1,2};
	vector<int> res = getIndices(arr);
	if(res.size()>0)
		cout<<res[0]<<endl;
	return 0;
}