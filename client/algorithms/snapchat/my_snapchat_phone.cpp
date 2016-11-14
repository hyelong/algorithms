// Find triplets in array that sum up to a given number.

// Given an array of integers, and a target integer S,
// write a program that prints all the triplets of numbers from the array
// (A, B, C) such that A+B+C=S.
// The array can contain any positive or negative integers, but CAN NOT contain duplicates.
// The elements in a triplet can happen at any position within the array.
// Do not output duplicate triplets.
// Print triplets in any order.

// Example:
// [1, 5, 6, 4, 2, 7, 3], S = 8 

// Answer: 
// [1, 2, 5]
// [1, 3, 4]
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums, int target){
  vector<vector<int>> res;
  int n = nums.size();
  if(n<3) return res;
  
  sort(nums.begin(), nums.end());
  
  int k = 0;
  while(k<n){
    int i = k+1;
    int j = n-1;
    while(i<j){
      long long sum = nums[i] + nums[j] + nums[k];
      if(sum == target){
        res.push_back({nums[k], nums[i], nums[j]});
        i++;
        while(i<j && nums[i] == nums[i-1]) i++;
        j--;
        while(i<j && nums[j] == nums[j+1]) j--;
      }
      else if(sum < target){
        i++;
        while(i<j && nums[i] == nums[i-1]) i++;
      }else{
        j--;
        while(i<j && nums[j] == nums[j+1]) j--;
      }
    }
    k++;
    while(k<i && nums[k] == nums[k-1]) k++;
  }
  return res;
}
// To execute C++, please define "int main()"
int main() {
  cout<<"test case1:"<<endl;
  vector<int> nums = {1, 5, 6, 4, 2, 7, 3};
  int s = 8;
  vector<vector<int>> res = threeSum(nums, s);
  for(auto nums : res){
    for(int num : nums){
      cout<< num << ",";
    }
    cout<<endl;
  }
   cout<<"test case2:"<<endl;
  nums = {1, 5};
  s = 8;
  res = threeSum(nums, s);
  for(auto nums : res){
    for(int num : nums){
      cout<< num << ",";
    }
    cout<<endl;
  }
  
  cout<<"test case3:"<<endl;
  nums = {};
  s = 8;
  res = threeSum(nums, s);
  for(auto nums : res){
    for(int num : nums){
      cout<< num << ",";
    }
    cout<<endl;
  }
  
  cout<<"test case4:"<<endl;
  nums = {-1, 1,8 ,9};
  s = 8;
  res = threeSum(nums, s);
  for(auto nums : res){
    for(int num : nums){
      cout<< num << ",";
    }
    cout<<endl;
  }
  
  cout<<"test case5:"<<endl;
  nums = {-1, -1, 1, 8,8 ,9, 9};
  s = 8;
  res = threeSum(nums, s);
  for(auto nums : res){
    for(int num : nums){
      cout<< num << ",";
    }
    cout<<endl;
  }
  
   cout<<"test case6:"<<endl;
  nums = {-1, -1, INT_MAX, INT_MAX ,8 ,9, 9, 1};
  s = INT_MAX;
  res = threeSum(nums, s);
  for(auto nums : res){
    for(int num : nums){
      cout<< num << ",";
    }
    cout<<endl;
  }
  
  cout<<"test case7:"<<endl;
  nums = {-1, -1, INT_MIN, INT_MAX ,8 ,9, 9, 1};
  s = INT_MIN;
  res = threeSum(nums, s);
  for(auto nums : res){
    for(int num : nums){
      cout<< num << ",";
    }
    cout<<endl;
  }
  
  
  return 0;
}
