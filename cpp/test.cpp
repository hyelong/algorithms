#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include <list>
#include <unordered_set>
using namespace std;

struct SimpleHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return p.first*101 + p.second;
    }
};
       
int main(){
    set<int> set={1,3,5,6,7,9};
    auto it = set.upper_bound(6);
    cout<<(*it)<<endl;
    it = set.lower_bound(6);
    cout<<(*it)<<endl;
    for(int i : set){
        if(i==1) set.insert(2);
       // cout<<i<<endl;
    }
    vector<int> v;
    v.push_back(1);
    for(int i:v){
        if(i==1) v.push_back(2);
        cout<<i<<endl;
    }
    cout<<v.size()<<endl;
    cout<<"-----test sstream------"<<endl;
    string s = "12,123";
    int number;
    istringstream iss(s);
    iss>>number;
    iss>>number;
    //iss.clear();
    cout<<iss.tellg()<<endl;
    cout<<number<<endl;
    int myints[]= {17,89,7,14,89};
    std::list<int> mylist (myints,myints+5);
    mylist.remove(89);
    cout<<mylist.size()<<endl;

    pair<int, int> p = {1,2};
    unordered_set<pair<int, int>, SimpleHash> pset;
    pset.insert(p);
    pair<int, int> p1 = {1,2};
    if(pset.find(p1)!=pset.end()) cout<<"good"<<endl;
    else cout<<"not good"<<endl;
    char c = 'a';
    cout<<to_string(c)<<endl;
    return 0;
}
