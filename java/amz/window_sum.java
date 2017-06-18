/*
* [4, 2, 73, 11, -5] and window size 2 should return [6, 75, 84, 6]
*/
import java.util.*;

public class window_sum{
    Integer[] windowSum(int[] arr, int size){
        int n = arr.length;
        List<Integer> res = new ArrayList<>();
        int sum = 0;
        for(int i=0;i<n;i++){
            sum += arr[i];
            if(i>=size-1){
                res.add(sum);
                sum -= arr[i-size+1];
            }
        }
        Integer[] ans = new Integer[n-size+1];
        res.toArray(ans);
        return ans;
    }
    public static void main(String[] args){
        int[] arr = {4,2,73,11,-5};
        Integer[] res = new window_sum().windowSum(arr, 2);
        for(int num : res) System.out.println(num);
    }
}
