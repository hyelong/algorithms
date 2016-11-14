/* Given an array of integers, print out the longest sequence of positive integers. */
/* For example, given {-1, 2, 3, -4, 6, 12, 8, 9, -3, -5}, print out {6, 12, 8, 9} */

#include <vector>
#include <iostream>
using namespace std;

void print_longest_positive_sequence(vector<int>& nums){
  int n = nums.size();
  if(n==0) return;
  int start = 0, long_start = 0, longest = 0, len = 0;
  for(int i=0;i<n;i++){
    if(nums[i]>0) len++;
    else{
      if(len>longest){
        longest = len;
        long_start = start;
      }
      len = 0;
      start = i+1;
    }
  }
  if(len>longest) {
    longest = len;
    long_start = start;
  }
  for(int i=long_start; i<long_start+longest; i++){
    cout<< nums[i];
    if(i!=long_start+longest-1) cout<<", ";
  }
  cout<<endl;
}

int main(){
  vector<int> nums = {-1, 2, 3, -4, 6, 12, 8, 9, -3, -5};
  print_longest_positive_sequence(nums);
  return 0;
}
