import java.util.Arrays;

/*
 * Given an n*n matrix of positive and negative integers,
 * write code to find the submatrix with largest possible sum.  
 */
public class SubmatrixSum {
	private void clearArray(int[] array){
		Arrays.fill(array, 0);
	}
	
	private int maxSubarray(int[] array, int n){
		int max = Integer.MIN_VALUE;
		int sum = 0;
		for(int i=0;i<n;i++){
			sum += array[i];
			max = Math.max(sum, max);
			if(sum<0) sum=0;
		}
		return max;
	}
	
	private int maxSubmatrix(int[][] matrix){
		int rowCount = matrix.length;
		if(rowCount==0) return 0;
		int colCount = matrix[0].length;
		int[] partialSum = new int[colCount];
		int res = Integer.MIN_VALUE;
		for(int i=0;i<rowCount;i++){
			clearArray(partialSum);
			for(int j = i;j<rowCount;j++ ){
				for(int k=0;k<colCount;k++){
					partialSum[k] += matrix[j][k];
				}
				int tempMax = maxSubarray(partialSum, colCount);
				res = Math.max(res, tempMax);
			}
		}
		return res;
	}
	
	public static void test(){
		SubmatrixSum submatrixSum = new SubmatrixSum();
		int[][] matrix={{1,2,3},{4,-150,6},{7,8,9}};
		int res = submatrixSum.maxSubmatrix(matrix);
		System.out.println(res);
	}
}
