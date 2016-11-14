#include <iostream>
using namespace std;

void heapify(int a[], int i, int n){
    int l = 2*i+1;
    int r = 2*i+2;
    int largest = i;
    if(l<n && a[l]>a[largest])
        largest = l;
    if(r<n && a[r]>a[largest])
        largest = r;
    if(largest!=i){
        swap(a[largest],a[i]);
        heapify(a, largest, n);
    }
}

void build_max_heap(int a[], int n){
    for(int i=n/2; i>=0; i--){
        heapify(a, i, n);
    }
}

void heap_sort(int a[], int n){
    build_max_heap(a, n);
    for(int i=n-1;i>=1;i--){
        swap(a[i],a[0]);
        heapify(a, 0, i);
    }
}

int main(){
    int a[]={3,4,1,5,8,6};
    int n = sizeof(a)/sizeof(a[0]);
    heap_sort(a, n);
    for(int i : a) cout<<i<<" ";
    cout<<endl;
    return 0;
}
