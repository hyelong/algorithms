/*
给了我一个放水版的word ladder II。只要任意返回一个path就行，
不用最短path，也不用返回所有的，随便一个就行
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool backtrace(string& cur, string& end, unordered_set<string>& dict, 
		vector<string>& path, unordered_set<string>& visited){
	if(cur==end){
		return true;
	}

	for(int index = 0; index < cur.length(); index++){
		string temp = cur;
		for(char c = 'a'; c <= 'z'; c++){
			temp[index] = c;
			if(visited.count(temp)>0 || dict.count(temp)==0 || temp == cur) continue;

			visited.insert(temp);
			path.push_back(temp);
			if(backtrace(temp, end, dict, path, visited)) return true;
			path.pop_back();
			visited.erase(temp);
		}
	}

	return false;
}

vector<string> find_path(string& start, string& end, unordered_set<string>& dict){
	vector<string> path;
	unordered_set<string> visited;
	backtrace(start, end, dict, path, visited);
	return path;
}

int main(){
	string start = "hit";
	string end = "cog";
	unordered_set<string> dict={"hot","dot","dog","lot","log"};
	dict.insert(end);
	vector<string> res = find_path(start, end, dict);
	for(string s : res){
		cout<< s << " ";
	}
	cout<<endl;
	return 0;
}