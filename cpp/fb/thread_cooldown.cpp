/*
 * 二面 :之后上题(运气挺好的这次还是只有一道)。给了一串 task,不同的 task 可能属于不同 type。 这些 task 要放到 CPU 里运行,运行同一种 type 是要考虑一个冷却时间。。。弄了半天,过了好几个例子 才搞明白,就类似于一个 OS。给你一个单线程的 scheduler,和 eg. 4 种 thread:1,2,3,4, 冷却时 间: 3,在 multithreading 的时候同类型的 thread 要等上一个 thread 跑完冷却时间之后才能运行,求最 后 scheduler 用了多少 time slot。 举个例子,thread: 1, 2, 1, 1, 3, 4; 冷却时间: 2 time slot, scheduler 应该是这样的:1, 2, _, 1, _, _, 1,3, 4,最后返回 9.)
 */
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <utility>
using namespace std;

int cooldown(vector<int>& threads, int slot){
  int n = threads.size();
  int total = 0;
  unordered_map<int, int> visited;
  for(int i=0;i<n;i++){
    if(visited.count(threads[i])){
      while(visited[threads[i]]+slot>=total){
        total++;
      }
    }
    visited[threads[i]] = total;
    total++;
  }
  return total;
}

int cooldown2(vector<char>& threads, int slot){
  unordered_map<char, int> char_fres;
  int n = threads.size();
  for(int i=0;i<n;i++){
    char_fres[threads[i]]++;
  }
  priority_queue<pair<int, char>> pq;
  for(auto item:char_fres){
    pq.push({item.second, item.first});
  }
  string res;
  while(!pq.empty()){
    int size = pq.size();
    vector<pair<int,char>> v;
    while(size--){
      auto cur = pq.top();
      int len = res.length();
      if(len-slot>=0 && res[len-slot]==cur.second) {
        res += ' ';
        continue;
      }
      else {
        res += cur.second;
        pq.pop();
      }
      cur.first--;
      if(cur.first) v.push_back(cur);
    }
    for(auto item : v) pq.push(item);
  }
  cout<<res<<endl;
  return res.size();
}

int main(){
  vector<int> threads = {1, 2, 3 ,4, 5, 6, 2, 4, 6, 1, 2, 4};
  int time_slot = 6;
  int res = cooldown(threads, time_slot);
  cout<<res<<endl;

  vector<char> chars = {'A','A','B','C'};
  res = cooldown2(chars, 2);
  cout<<res<<endl;
  return 0;
}
