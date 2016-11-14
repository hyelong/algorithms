import java.util.*;

public class insertion{
    public static void main(String[] args){
        insertion i = new insertion();
        int[] arr = new int[]{15,9,8,1,4};
        i.sort(arr);
        for(int num: arr)
            System.out.print(num+" ");
        System.out.println();
    }

    void sort(int[] arr){
        int n = arr.length;
        for(int i = 1; i<n; i++){
            int j = i-1;
            int value = arr[i];
            while(j>=0 && arr[j]>value){
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = value;
        }
    }
}
