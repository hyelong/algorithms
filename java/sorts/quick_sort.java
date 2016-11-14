import java.util.*;

public class quick_sort{
    public static void main(String[] args){
        quick_sort quick = new quick_sort();
        int[] arr = new int[]{15,13, 14, 1, 4};
        quick.sort(arr);
        for(int i=0;i<arr.length;i++) System.out.print(arr[i]+" ");
        System.out.println();
    }

    void sort(int[] arr){
        sortHelper(arr, 0, arr.length-1);
    }

    void sortHelper(int[] arr, int start, int end){
        if(start >= end) return;
        int pivot = partition(arr, start, end);
        sortHelper(arr, start, pivot-1);
        sortHelper(arr, pivot+1, end);
    }

    int partition(int[] arr, int start, int end){
        int pivot = arr[end];
        int i = start;
        int j = end-1;
        while(i<=j){
            while(i<=j && arr[i] < pivot) i++;
            while(i<=j && arr[j] >= pivot) j--;
            if(i<j) {
                swap(arr, i, j);
                i++;
                j--;
            }
        }
        arr[end] = arr[i];
        arr[i] = pivot;
        return i;
    }

    void swap(int[] arr, int i, int j){
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
