/*
第一道 check if there is a subarray sum equals x,
题不难结果最后边界条件出了问题,改了一下 出问题了,
结果三哥直接说下一题,我 强行改了一下当时也不知道对不对。
然后第二题就很慌一直心神不宁,第二题是 leetcode 的那道 search in 2d matrix,
这题我没做过不过 刷题的时候印象中有类似的名字的题
第二题搞错了,不是 search in 2d matrix。
其实有点像第一题的 follow up,把 search sum 从一维变到 二维,subarray 变成 sub rectangle
*/
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

bool subarray_sum(vector<int>& arr, int sum){
  int n = arr.size();
  vector<int> partialSum(n);
  int total = 0;
  for(int i=0;i<n;i++){
    total += arr[i];
    partialSum[i] = total;
  }
  unordered_set<int> visited;
  visited.insert(0);
  for(int subSum : partialSum){
    if(visited.count(subSum - sum)) return true;
    visited.insert(subSum);
  }
  return false;
}
bool submatrix_sum(vector<vector<int>>& matrix, int sum){
  int m = matrix.size();
  if(m==0) return false;
  int n = matrix[0].size();
  for(int i=1;i<m;i++){
    for(int j=0;j<n;j++){
      matrix[i][j] = matrix[i][j]+matrix[i-1][j];
    }
  }
  vector<int> first_row(n,0);
  matrix.insert(matrix.begin(), first_row);

  for(int i=0;i<=m;i++){
    for(int j=0; j<i;j++){
      vector<int> arr(n,0);
      for(int k=0;k<n;k++){
        arr[k] = matrix[i][k]-matrix[j][k];
      }
      if(subarray_sum(arr, sum)) return true;
    }
  }
  return false;
}
int main(){
  vector<int> arr = {9,8,5,7,6};
  int sum = 9;
  bool res = subarray_sum(arr, sum);
  cout<<res<<endl;
  vector<vector<int>> matrix = {{1,2,3},{4,5,6},{7,8,9}};
  sum = 1;
  res = submatrix_sum(matrix, sum);
  cout<<res<<endl;
}
