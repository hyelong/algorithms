
/*
 * 一个背包有特定容量，和一些物品，每种物品所占空间不同，所代表的价值不同。
 * 输入是背包容量 和 物品list，要求背包能装的最大的物品价值。
 */
public class Knapsack {
	private int maxValue(int[] values, int[] sizes, int capacity){
		int[][] dp = new int[sizes.length+1][capacity+1];
		for(int i=1;i<=sizes.length;i++){
			for(int j=1;j<=capacity;j++){
				if(j>=sizes[i-1]){
					dp[i][j] = Math.max(values[i-1]+dp[i-1][j-sizes[i-1]], dp[i-1][j]);
				}
				else dp[i][j]=dp[i-1][j];
			}
		}
		return dp[sizes.length][capacity];
	}
	
	public static void test(){
		int[] values = {60,100,120};
		int[] sizes = {10,20,30};
		int capacity = 50;
		Knapsack knapsack = new Knapsack();
		int res = knapsack.maxValue(values,sizes,capacity);
		System.out.println(res);
	}
}
