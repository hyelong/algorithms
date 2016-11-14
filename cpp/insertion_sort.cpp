#include <iostream>
#include <vector>
using namespace std;

void insertion_sort(vector<int>& arr){
    int n = arr.size();
    if(n<2) return;
    for(int i=1;i<n;i++){
        int j = i-1;
        int temp = arr[i];
        while(j>=0 && arr[j]>arr[i]) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

int main(){
    vector<int> arr = {3,1,2,5,4,7,6};
    insertion_sort(arr);
    for(int num : arr){
        cout<<num<<" ";
    }
    cout<<endl;
    return 0;
}
