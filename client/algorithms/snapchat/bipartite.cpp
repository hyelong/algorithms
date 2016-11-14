#include <vector>
#include <unordered_map>
#include <iostream>
#include <typeinfo>
using namespace std;

bool is_bipartite(vector<pair<int, int>>& edges){
	int n = edges.size();
	unordered_map<int, int> visited;
	for(int i=0; i<n; i++){
		int from = edges[i].first;
		int to = edges[i].second;
		if(!visited.count(from) && !visited.count(to)){
			visited[from] = 0;
			visited[to] = 1;
		}else if(visited.count(from)) {
			if(!visited.count(to)) visited[to] = 1- visited[from];
			else if(visited[from] == visited[to]) return false;
		}else if(visited.count(to)){
			if(!visited.count(from)) visited[from] = 1 - visited[to];
			else if(visited[from] == visited[to]) return false;
		}
	}
	return true;
}

int main(){
	vector<pair<int, int>> edges = {{1,2}, {2,3}, {1,3}};
	bool res = is_bipartite(edges);
	cout<<res<<endl;

	return 0;
}