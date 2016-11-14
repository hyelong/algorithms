/*
 *Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), 
 *prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.)
 *
 * 1, You must not modify the array (assume the array is read only).
 * 2, You must use only constant, O(1) extra space.
 * 3, Your runtime complexity should be less than O(n2).
 * 4, There is only one duplicate number in the array, but it could be repeated more than once.
 */

public class FindDuplicateNumber{
    private int findDuplicate(int[] nums){
        if(nums == null) return -1;
        int n = nums.length;
        if(n == 0) return -1;
        int low = 1, high = n-1, mid, count = 0;
        while(low < high){
            count = 0;
            mid = low + (high - low)/2;
            for(int i=0; i<n; i++){
                if(nums[i] <= mid) count++; 
            }
            if(count > mid) high = mid;
            else low = mid + 1;
        }
        return low;
    }

    private int findDup(int[] nums){
        if(nums == null) return -1;
        int n = nums.length;
        if(n == 0) return -1;
        int a = 0, b = 0;
        do{
            a = nums[nums[a]];
            b = nums[b];
        }while(a != b);

        a = 0;
        while(a != b){
            a = nums[a];
            b = nums[b];
        }
        return a;
    }

    public static void main(String[] args){
      FindDuplicateNumber find = new FindDuplicateNumber();
      int[] nums = {1,2,3,4,5,2};
      System.out.println(find.findDuplicate(nums));
    }
}
