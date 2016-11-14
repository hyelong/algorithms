#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& arr, int left, int right){
    int j = left;
    int pivot = arr[right];
    for(int i=left; i<right;i++){
        if(arr[i]<pivot) {
            swap(arr[i], arr[j]);
            j++;
        }
    }
    swap(arr[j], arr[right]);
    return j;
}

void quick_sort(vector<int>& arr, int left, int right){
    if(left>=right) return;
    int index = partition(arr, left, right);
    quick_sort(arr, left, index-1);
    quick_sort(arr, index+1, right);
}

int main(){
    vector<int> arr = {4,5,3,2,1,3};
    quick_sort(arr, 0, arr.size()-1);
    for(int i=0;i<arr.size();i++) cout<<arr[i]<<" ";
    cout<<endl;
    return 0;
}
