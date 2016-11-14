#include <iostream>
#include <vector>
using namespace std;

void selection_sort(vector<int>& arr){
    int n = arr.size();
    if(n<2) return;
    for(int j=0;j<n-1;j++){
        int iMin = j;
        for(int i=j+1;i<n;i++){
            if(arr[iMin]>arr[i]) iMin = i;
        }
        if(iMin!=j) swap(arr[iMin], arr[j]);
    }
}

int main(){
    vector<int> arr = {3,1,2,5,4,7,6};
    selection_sort(arr);
    for(int num : arr){
        cout<<num<<" ";
    }
    cout<<endl;
    return 0;
}
