/*
3d grid，每个点有高度， 给起点和终点，求一个直升机起点到终点高度和最小的路径，注意一点是直升机只能上升不能下降
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <climits>
using namespace std;

void helper(vector<vector<int>>& matrix, unordered_set<int>& visited, int& minSum, int curSum, int end_pos, int cur_pos){
	if(cur_pos == end_pos){
		minSum = min(minSum, curSum);
		return;
	}
	visited.insert(cur_pos);
	
	int m = matrix.size();
	int n = matrix[0].size();
	vector<pair<int, int>> dirs = {{-1,0},{0,-1},{1,0},{0,1}};
	int x = cur_pos/n;
	int y = cur_pos%n;
	int cur_height = matrix[x][y];
	for(auto dir : dirs){
		int next_x = x + dir.first;
		int next_y = y + dir.second;
		if(next_x<0 || next_y<0 || next_x>=m || next_y>=n) continue;
		if(cur_height >= matrix[next_x][next_y]) continue;
		int next = next_x*n+next_y;
		if(visited.count(next)) continue;
		
		helper(matrix, visited, minSum, curSum+matrix[next_x][next_y], end_pos, next);
	}
}

int minHeightsSum(vector<vector<int>>& matrix, pair<int, int> start, pair<int, int> end){
	unordered_set<int> visited;
	int minSum = INT_MAX;
	int curSum = matrix[start.first][start.second];
	int end_pos = end.first*matrix[0].size() + end.second;
	int cur_pos = start.first*matrix[0].size() + start.second;
	helper(matrix, visited, minSum, curSum, end_pos, cur_pos);
	return minSum;
}

int main(){
	vector<vector<int>> matrix = {
		{1,2,3,4,5},
		{6,7,4,4,5},
		{7,8,9,4,5},
		{7,4,3,5,8},
	};
	int res = minHeightsSum(matrix, {0,0}, {2,2});
	cout<<res<<endl;
	return 0;
}
