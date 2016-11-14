import java.util.*;

public class is24{
    public static void main(String[] args){
        is24 is = new is24();
        int[] nums = new int[]{2,3,4,6};
        boolean res = is.is_24(nums, 0 , 0);
        System.out.println(res);
        nums = new int[]{2,2,2,2};
        res = is.is_24(nums, 0 , 0);
        System.out.println(res);
    }

    boolean is_24(int[] nums, int start, int res){
        if(start >= nums.length){
            return res == 24;
        }

        for(int i = start; i<nums.length; i++){
            swap(nums, i, start);
            if(is_24(nums,start+1,res+nums[start])) return true;
            if(is_24(nums,start+1,res-nums[start])) return true;
            if(is_24(nums,start+1,res*nums[start])) return true;
            if(is_24(nums,start+1,res/nums[start])) return true;
            swap(nums, i, start);
        }
        return false;
    }

    void swap(int[] nums, int i, int j){
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j]= temp;
    }
}
