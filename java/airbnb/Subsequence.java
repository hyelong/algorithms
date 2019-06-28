public class Subsequence{
    private static long countSubsequence3(int[] arr){
        int len = arr.length;
        long res = 0;
        for(int i = 0; i < len; i++){
            int current = i - 1;
            int left = 0;
            int right = 0;
            while (current >= 0) {
                if(arr[current] > arr[i]) left++;
                current--;
            }
            current = i + 1;
            while (current < len) {
                if(arr[current] < arr[i]) right++;
                current++;
            }
            res += left * right;
        }
        return res;
    }

    public static void main(String[] args){
        int[] arr = {5, 3, 3, 1};
        long res = countSubsequence3(arr);
        System.out.println(res);
    }
}