/*
1, 问题一个走迷宫问题。给了一个矩阵，"1"代表起点，位于左上角；"9"代表重点，位于右下角；"0"代表通路，"5"代表墙。
矩阵长得是这样
[
  [1, 5, 5, 5, 5, 0],
  [0, 5, 0, 5, 5, 0],
  [0, 5, 0, 0, 0, 0],
  [0, 5, 0, 0, 5, 0],
  [0, 0, 0, 5, 0, 9]
]
设计一个算法，看看这个迷宫能不能从起点走到重点。

2, 但是还出了一题， 就是墙可以打穿，问最少打穿多少墙可以到达终点。
*/

#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int nWalls(vector<vector<int>>& grid){
    queue<pair<int, int>> qwall;
    queue<pair<int, int>> qnode;
    vector<pair<int, int>> dirs = {{-1,0},{0,1},{0,-1},{1,0}};
    vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(), false));
    int wallCnt = 0;
    qnode.push({0,0});
    while(!qwall.empty() || !qnode.empty()){
        if(qnode.empty()){
            wallCnt++;
            while(!qwall.empty()){
                qnode.push(qwall.front());
                qwall.pop();
            }
        } 
        while(!qnode.empty()){
            int nx = qnode.front().first;
            int ny = qnode.front().second;
            qnode.pop();
            visited[nx][ny] = true;
            if(grid[nx][ny]==9) return wallCnt;
            for(auto& dir : dirs){
                int x = nx + dir.first;
                int y = ny + dir.second;
                if(x<0 || x>= grid.size() || y<0 || y>=grid[0].size() || visited[x][y]) continue;
                if(grid[x][y]==0 || grid[x][y]==9)   qnode.push({x,y});
                if(grid[x][y]==5)   qwall.push({x,y});
            }
        }
    }
}

vector<pair<int, int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

bool canArrive(vector<vector<int>>& grid, int x, int y, vector<pair<int,int>>& path, 
	vector<vector<int>>& visited){
	if(grid[x][y]==9) {
		return true;
	}

	path.push_back({x,y});
	visited[x][y] = true;
	for(int i=0; i<dirs.size();i++){
		int cur_x = x + dirs[i].first;
		int cur_y = y + dirs[i].second;
		if(cur_x<0 || cur_x>=grid.size() || cur_y<0 || cur_y>=grid[0].size())
			continue;
		
		if(visited[cur_x][cur_y]) continue;
		if(grid[cur_x][cur_y]==5) continue;
		if(canArrive(grid, cur_x, cur_y, path, visited)) return true;
	}
	//visited[x][y] = false;
	path.pop_back();
	return false;
}

int main(){
	vector<vector<int>> grid = {
		  {1, 5, 5, 5, 5, 0},
		  {0, 5, 5, 5, 5, 0},
		  {0, 5, 5, 0, 0, 0},
		  {0, 5, 0, 0, 5, 0},
		  {5, 5, 0, 5, 0, 9}
	};
    int res = nWalls(grid);
    cout<<res<<endl;
    vector<vector<int>> visited(grid.size(), vector<int>(grid[0].size(), false));
    vector<pair<int,int>> path;
    bool b = canArrive(grid, 0, 0, path, visited);
    cout<<b<<endl;
    for(auto pos: path){
    	cout<<pos.first<<","<<pos.second<<"  ";
    }
	return 0;
}
