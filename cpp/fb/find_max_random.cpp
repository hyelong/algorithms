/*
 * problem 2: randomly return the index of maximal elements in the array
 * follow up: 要求linear time 和constant space 
 */
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int find_max_index(vector<int>& arr){
  int n = arr.size();
  int res = -1;
  int max_val = INT_MIN;
  int count=0;
  for(int i=0;i<n;i++){
    if(max_val==arr[i]){
      count++;
      int r = random()%count;
      if(r==0){
        res = i;
      }
    }
    else if(arr[i]>max_val){
      count = 1;
      max_val = arr[i];
      res = i;
    }
  }
  return res;
}

int main(){
  srand(time(0));
  vector<int> arr = {1,2,3,2,3,1,3,2};
  int count2=0, count4=0, count6=0;
  for(int i=0;i<1000;i++){
    int res = find_max_index(arr);
    if(res==2) count2++;
    else if(res == 4) count4++;
    else if(res == 6) count6++;

    cout<<"2:"<<count2<<" 4: "<<count4<<" 6: "<<count6<<endl;
  }
  return 0;
}

