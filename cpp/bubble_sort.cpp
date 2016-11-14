#include <vector>
#include <iostream>
using namespace std;

void bubble_sort(vector<int>& arr){
    int n = arr.size();
    if(n<2) return;
    bool swaped = true;
    while(swaped){
        swaped = false;
        for(int i=1;i<n;i++){
            if(arr[i-1]>arr[i]) {
                swap(arr[i-1], arr[i]);
                swaped = true;
            }
        }
    }
}

int main(){
    vector<int> arr = {3,1,2,4,7,6,5};
    bubble_sort(arr);
    for(int num : arr){
        cout<<num<<" ";
    }
    cout<<endl;
}
