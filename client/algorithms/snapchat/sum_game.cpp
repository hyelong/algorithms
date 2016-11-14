/*两人轮流从1~n取数加到sum里，先使sum>target的赢，问先手赢不赢*/

#include <iostream>
#include <vector>
using namespace std;


class Solution{
public:
    bool canWin(int n, int target){
        vector<int> v = vector<int>(n);
        for(int i=1; i<=n; i++) v[i-1]=i;
        int curSum = 0;
        vector<bool> picked(n, false);
        return dfs(v, curSum, target, picked);
    }

private:
    bool dfs(vector<int>& v, int& curSum, int target, vector<bool>& picked){

        for(int i=0; i<v.size(); i++){
        	if(picked[i]) continue;
          if(v[i]>0 && v[i]+curSum > target)    return true;
          curSum += v[i];
          picked[i] = true;
          //对手pick
          if(!dfs(v, curSum, target, picked)) return true;
          picked[i] = false;
          curSum -= v[i];
        }
        return false;
    }
};

int main(){
	Solution sol;
	bool res = sol.canWin(5, 8);
	cout<<res<<endl;
	return 0;
}
