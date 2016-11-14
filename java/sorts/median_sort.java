import java.util.*;

public class median_sort{
    public static void main(String[] args){
        median_sort m = new median_sort();
        int[] arr = new int[]{16,8,15,9,1,4,7};
        m.medianSort(arr, 0, arr.length-1);
        for(int num : arr) System.out.print(num+" ");
        System.out.println();
    }
    
    void medianSort(int[] arr, int left, int right){
        if(left>=right) return;

        int median = find_kth(arr, left, right, (right-left)/2+1);
        //System.out.println("median:" + median);
       // if(median>0) return;
       /*
        int mid = (right-left)/2;
        swap(arr, median-1, mid);
        for(int i=left, j = right; i<mid;){
            while(arr[i]<arr[mid])i++;
            while(arr[j]>=arr[mid])j--;
            swap(arr, i, j);
            i++;
            j--;
        }*/
        medianSort(arr, left, median-1);
        medianSort(arr, median+1, right);
    }

    int find_kth(int[] arr, int l, int r, int k){
        if(k>0 && k<=r-l+1){
            int p = partition(arr, l, r);
            if(p-l+1==k) return p;
            if(p-l+1<k) return find_kth(arr, p+1, r, k-p+l-1);
            return find_kth(arr, l, p-1, k);
        }
        return -1;
    }

    int partition(int[] arr, int l, int r){
        int p = arr[r];
        int i = l;
        for(int j=l;j<=r-1;j++){
            if(arr[j]<p){
                swap(arr, i, j);
                i++;
            }
        }
        swap(arr, i, r);
        return i;
    }

    void swap(int[] arr, int i, int j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
