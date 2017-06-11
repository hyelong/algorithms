/**
 * Question: Find the missing number in an array of consecutive integers.
 *
 * Example:
 *
 * input:2,3,4,5,6,7,8,9,10,11,12,13,14,15 output: null
 *
 * input:2,3,5,6,7,8,9,10,11,12,13,14,15 output: 4
 *
 * input:2,3,4,5,6,7,8,9,10,11,12,14,15 output: 13
 */

import java.util.*;

public class missing_num{
    private Integer missingNum(int[] nums, int start, int end){
        if(start >= end) return null;
        while(start < end){
            int mid = start + (end - start)/2;
            if(mid - start == nums[mid] - nums[start]){
                if(mid + 1 < nums.length && nums[mid+1]!=nums[mid]+1){
                    return nums[mid] + 1;
                }
                else start = mid + 1;
            }
            else{
                if(mid - 1 >= 0 && nums[mid-1] != nums[mid] - 1){
                    return nums[mid] - 1;
                }
                else end = mid - 1;
            }
        }
        return null;
    }
    public static void main(String[] args){
        //int[] nums = {2,3,5,6,7,8,9,10,11,12,13,14,15};
        int[] nums = {2,3,4,5,6,7,8,9,10,11,12,14,15};
        int res = new missing_num().missingNum(nums, 0, nums.length - 1);
        System.out.println(res);
    }
}
