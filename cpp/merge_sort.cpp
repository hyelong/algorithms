#include<iostream>
#include<vector>
using namespace std;

void mergeSort(vector<int>& arr, int start, int end){
    if(end - start <= 1) return;
    int mid = start + (end - start)/2;
    mergeSort(arr, start, mid);
    mergeSort(arr, mid, end);
    //half sorted
    for(int i=mid;i<end;i++) cout<<arr[i]<<" ";
    cout<<endl;
    vector<int> tmp;
    int j = mid;
    for(int i = start; i<mid; i++){
        while(j<end && arr[j] < arr[i]) tmp.push_back(arr[j++]);
        tmp.push_back(arr[i]);
    }
    copy(tmp.begin(),tmp.end(), arr.begin()+start);
}

int main(){
    vector<int> arr = {8,5,6,3,4,2,1,7};
    mergeSort(arr, 0, arr.size());
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}
