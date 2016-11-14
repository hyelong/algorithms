#include <vector>
#include <map>
#include <set>
#include <iostream>
using namespace std;
/*
题目是手机上的通讯录，每条记录只有(name, number)这种pair,有些记录名字重复，有些记录号码重复，让我返回一个list<list<Record>>，
将所有记录按人分组。比较tricky的点在于(ABC,123), (ABC, 456), (BCD, 456)
三条记录，第一条和第三条也属于同一个人。要求时间复杂度尽量小
*/

class Solution{
public:
    map<string, set<string>> removeDuplicate(vector<pair<string, string>> records){
        for(auto& pr : records){
            g[pr.first].push_back(pr.second);
            g[pr.second].push_back(pr.first);
        }
        for(auto it = g.begin(); it!=g.end(); it++){
            if(!isName(it->first))  continue;
            dfs(it->first, it->first);
        }
        return m;
    }
private:
    map<string, vector<string>>  g;
    map<string, set<string>> m;
    set<string> visited;
    void dfs(string root, string node){
        if(visited.count(node)) return;
        visited.insert(node);
        if(!isName(node))   m[root].insert(node);
        for(auto neighbor : g[node]){
            dfs(root, neighbor);
        }
    }

    bool isName(string s){
        char c = s[0];
        if(c>='0' && c<='9')    return false;
        else return true;
    }

};

int main(){
    Solution sol;
    vector<pair<string, string>> records = {{"ABC", "123"},{"ABC", "456"},{"BCD", "456"}};
    vector<pair<string, string>> records2 = {{"a", "1"}, {"b", "1"},{"a", "2"},{"c", "3"},{"d", "3"},{"e", "4"},{"e", "5"},{"f", "6"},{"g", "7"},{"f", "7"}};
    auto res = sol.removeDuplicate(records);
    for(auto pr : res){
        cout<< pr.first<<" : "<<endl;
        for(auto item : pr.second)
            cout<< "    "<<item<<endl;
    }
    return 0;
}