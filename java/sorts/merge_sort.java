import java.util.*;

public class merge_sort{
    public static void main(String[] args){
        int[] arr = new int[]{13,8,9,5,1,4};
        merge_sort m = new merge_sort();
        m.mergeSort(arr);
        for(int i=0;i<arr.length;i++)
            System.out.print(arr[i]+" ");
        System.out.println();
    }

    void mergeSort(int[] arr){
        mergeSortHelper(arr, 0, arr.length);
    }

    void mergeSortHelper(int[] arr, int start, int end){
        if(start >= end-1) return;
        int mid = start + (end - start)/2;
        mergeSortHelper(arr, start, mid);
        mergeSortHelper(arr, mid, end);
        merge(arr, start, mid, end);
    }

    void merge(int[] arr, int start, int mid, int end){
        int[] temp = new int[end-start];
        int i = start;
        int j = mid;
        int k = 0;
        while(i<mid && j<end){
            if(arr[i]<arr[j]){
                temp[k++] = arr[i++];
            }
            else temp[k++] = arr[j++];
        }

        while(i < mid) temp[k++] = arr[i++];
        while(j < end) temp[k++] = arr[j++];
        
        for(int index = 0; index<temp.length; index++) 
            arr[start+index] = temp[index];
    }
}
