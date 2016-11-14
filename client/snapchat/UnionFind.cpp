#include <vector>
using namespace std;

class UnionFind {
    vector<int> father, ranks;
    int nums{ 0 };
public:
    UnionFind(int num_nodes) : nums(num_nodes) {
        for (int i = 0; i < num_nodes; i++) {
            father.push_back(i);
            ranks.push_back(0);
        }
    }
    int find(int x) {
        if (x == father[x]) return x;
        return father[x] = find(father[x]);
    }
    void do_union(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (ranks[x] < ranks[y]) {
            father[x] = y;
        } else {
            father[y] = x;
            if (ranks[x] == ranks[y]) {
                ranks[x]++;
            }
        }
    }
    int num_sets() {
        int count = 0;
        for(int i = 0; i < nums; ++i) {
            if(father[i] == i) count++;
        }
        return count;
    }
};

int main(){
    return 0;
}