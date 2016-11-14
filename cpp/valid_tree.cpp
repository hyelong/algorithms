#include <iostream>
#include <vector>
using namespace std;

class UnionFind{
private:
    vector<int> father, rank;
    int nums{0};
public:
    UnionFind(int n):nums(n){
        for(int i=0;i<n;i++){
            father.push_back(i);
            rank.push_back(0);
        }
    }

    int find(int x){
        if(x==father[x]) return x;
        int fx = find(father[x]);
        father[x] = fx;
        return fx;
    }

    void do_union(int x, int y){
        x = find(x);
        y = find(y);
        if(x==y) return;
        if(rank[x]<rank[y]){
            father[x] = y;
        }
        else{
            father[y] = x;
            if(rank[x]==rank[y]){
                rank[x]++;
            }
        }
    }

    int num_sets(){
        int count = 0;
        for(int i=0;i<nums;i++){
            if(i==father[i]) count++;
        }
        return count;
    }
};

bool validTree(int n, vector<vector<int>> edges){
    if(n==0 || edges.empty()) return false;
    UnionFind u(n);
    for(int i=0;i<edges.size();i++){
        int x = u.find(edges[i][0]);
        int y = u.find(edges[i][1]);
        if(x==y) return false;
        u.do_union(x,y);
    }
    return u.num_sets()==1;
}

int main(){
    int n = 3;
    vector<vector<int>> edges;
    vector<int> edge={0,1};
    edges.push_back(edge);
    edge={1,2};
    edges.push_back(edge);
    edge={0,2};
    edges.push_back(edge);
    bool res = validTree(n, edges);
    cout<<res<<endl;
    return 0;
}
