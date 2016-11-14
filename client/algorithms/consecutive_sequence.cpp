#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//https://www.hackerrank.com/contests/w6/challenges/consecutive-subsequences

long long get_count(const vector<int>& vec, int k) {
  //Initialize count array.
  vector<int> cnt_mod(k, 0);
  cnt_mod[0] = 1;
  int pref_sum = 0;
  //Iterate over the input sequence.
  for (int elem : vec) {
    pref_sum += elem;
    //pref_sum %= k;
    cnt_mod[pref_sum%k]++;
  }
  //Compute the answer.
  long long res = 0;
  for (int mod = 0; mod < k; mod++)
    res += (long long)cnt_mod[mod] * (cnt_mod[mod] - 1) / 2;
  return res;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    vector<int> vec = {1,2,3,4,1};
    int k = 3;
    int res = get_count(vec, k);
    cout<<res<<endl;
    return 0;
}
