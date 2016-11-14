/*
第一轮，ABC小哥，给两个string的数组和一个pattern数组，判断将两个string数组分别和pattern转化后的结果是否相同。
例如s1={“abc”, “a”, “ccc”}, s2={“bc”, “aa”, “d”}, pattern={1, 0}，
则s1和p的转化结果是“aabc”，s2和p的转化结果也是是“aabc”，则返回true。如果pattern是{0, 1}，
则转化结果分别是“abca”, “bcaa”，则返回false。followup是，如果给定s1和s2，
判断是否存在一个pattern使得转化结果一致。 过程中要求分析算法复杂度。
*/
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

bool find_pattern(vector<string>& s1, vector<string>& s2, int curr_index, 
	string curr_s, vector<int>& res, unordered_set<int>& visited, bool in_s1){
	res.push_back(curr_index);
	visited.insert(curr_index);

	if(in_s1){
		if(s2[curr_index].find(curr_s) == 0 ){
			if(s2[curr_index] == curr_s && !res.empty()) 
				return true;
			else{
				string sub = s2[curr_index].substr(curr_s.length());
				for(auto i=0;i<s1.size();i++){
					if(visited.count(i)) continue;
					if(s1[i].find(sub)==0)
						if(find_pattern(s1, s2, i, s1[i].substr(sub.length()), res, visited, in_s1)) return true;
				}
			}
		}
	}
	else{
		if(s1[curr_index].find(curr_s) == 0 ){
			if(s1[curr_index] == curr_s && !res.empty()) 
				return true;
			else{
				string sub = s1[curr_index].substr(curr_s.length());
				for(auto i=0;i<s2.size();i++){
					if(visited.count(i)) continue;
					if(s2[i].find(sub)==0)
						if(find_pattern(s1, s2, i, s2[i].substr(sub.length()), res, visited, in_s1)) return true;
				}
			}
		}
	}
	
	
	res.pop_back();
	visited.erase(curr_index);
	
	return false;
}

vector<int> find_pattern(vector<string>& s1, vector<string>& s2){
	vector<int> res;
	unordered_set<int> visited;
	for(auto i=0;i<s1.size();i++){
		find_pattern(s1, s2, i, s1[i], res, visited, true);
	}
	if(!res.empty()) return res;
	cout<<"empty"<<endl;
	for(auto i=0;i<s2.size();i++){
		find_pattern(s1, s2, i,s2[i], res, visited, false);
	}
	return res;
}

int main(){
	vector<string> s2 = {"abc", "a", "ccc"};
	vector<string> s1 = {"bc", "aa", "d"};
	auto res = find_pattern(s1, s2);
	for(int i : res) cout<<i<<endl;
	return 0;
}

