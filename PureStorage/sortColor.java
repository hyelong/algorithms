public class sortColor {
	void sortColors2(int[] nums) {
		int i = 0;
	    int j = nums.length - 1;
	    while (i < j) {
	        while (i < j && nums[i] == 0) {
	        	++i;
	        }
	        while (j >= i && nums[j] != 0) {
	            --j;
	        }
	        if (i >= j) {
	            break;
	        }
	        int temp = nums[i];
	        nums[i] = nums[j];
	        nums[j] = temp;
	    }
	    j = nums.length - 1;
	    while (i < j) {
	    	while (i < j && nums[i] == 1) {
	    		++i;
	        }
	        while (j >= i && nums[j] != 1) {
	            --j;
	        }
	        if (i >= j) {
	            break;
	        }
	        int temp = nums[i];
	        nums[i] = nums[j];
            nums[j] = temp;
	    }
	}
	
	void sortColors(int[] nums) {
		int p0 = 0, curr = 0;
		int p2 = nums.length - 1;
		int tmp;
		while (curr <= p2) {
			while (p0 < nums.length - 1 && nums[p0] == 0) {
				++p0;
		    }
		    while (p2 >= 0 && nums[p2] == 2) {
		        --p2;
	        }
	        if (nums[curr] == 0 && curr > p0) {
	        	tmp = nums[p0];
		        nums[p0++] = nums[curr];
		        nums[curr++] = tmp;
	        }
	        else if (nums[curr] == 2 && curr < p2) {
	        	tmp = nums[curr];
		        nums[curr] = nums[p2];
		        nums[p2--] = tmp;
	        }
	        else {
	        	curr++;
		    }
		}
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
