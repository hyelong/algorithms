/*Strobogrammatic Number II give us all the strings with length n.*/

#include <iostream>
#include <vector>
using namespace std;
vector<string> findImp(int n, int total){
	if (n == 0) { return vector<string> { "" }; }
    if (n == 1) { return vector<string> { "1", "8", "0" }; }
    vector<string> sub_res = findImp(n-2, total);
    vector<string> res;
    for(auto s : sub_res){
    	if (n != total) {
            res.push_back("0" + s + "0");
        }
        res.push_back("1" + s + "1");
        res.push_back("8" + s + "8");
        res.push_back("6" + s + "9");
        res.push_back("9" + s + "6");
    }
    return res;
}

vector<string> findStrobogrammatic(int n){
	return findImp(n, n);
}

int main(){
	int n = 4;
	auto res = findStrobogrammatic(4);
	for(auto s : res){
		cout<<s<<endl;
	}
	return 0;
}