/*
Given two strings s and t, determine if they are isomorphic.
 
Two strings are isomorphic if the characters in s can be replaced to get t.
 
All occurrences of a character must be replaced with another character while preserving the order of characters. 
No two characters may map to the same character but a character may map to itself.
 
For example,
Given "egg", "add", return true.
 
Given "foo", "bar", return false.
 
Given "paper", "title", return true.
 
Group them-> {"paper, title"}, {"egg","add"},{"hello","billy"}
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
private:
    unordered_map<string, int>table;
public:
    vector<vector<string> > GroupIsomorphic(vector<string> & word) {
        vector<vector<string> >res;
        if(word.empty())return res;
        for(auto & str : word){
            string tmp=convert(str);
						cout<<"key:"<<tmp<<endl;
            if(!table.count(tmp)){
                table[tmp]=res.size();
                vector<string>v;
                v.push_back(str);
                res.push_back(v);
            }
            else res[table[tmp]].push_back(str);
 
        }
        return res;
    }
    string convert(string str){
        unordered_map<char, int>map;
        if(str.length() <=1 )return "#";
        string res="";
        int diff=0;
        for(auto ch : str){
            if(!map.count(ch))map[ch]=diff++;
            res+=to_string(map[ch])+'#';
        }
        return res;
 
    }
};
int main(){
    Solution ss;
    string b[]={"egg","add","laa","title","paper","hello","billy","kitten","how","today"};
    vector<string> word(b, b + sizeof(b) / sizeof(b[0]));
    vector<vector<string> >res= ss.GroupIsomorphic(word);
 
    for(auto & data : res){
        for(auto & s : data)cout << s << " ";
        putchar('\n');
    }
    return 0;
}
