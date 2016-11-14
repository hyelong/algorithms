
public class WaysToChangeCoins {
	int[][] dp;
	private int findWays(int[] coins, int types, int target ){
		if(target==0) return 1;
		if(target<0) return 0;
		if(types<=0 && target>0) return 0;
		if(dp[types][target]!=-1) return dp[types][target];
		//excluding coins[types-1] and including coins[types-1]
		int res = findWays(coins, types-1, target)+findWays(coins, types, target-coins[types-1]);
		dp[types][target] = res;
		return res;
	}
	
	
	//every coin with limited count
	private int findWays2(int[] coins,int[] counts, int types, int target ){
		if(target==0) return 1;
		if(target<0) return 0;
		if(types<=0 && target>0) return 0;
		int res = 0;
		if(counts[types-1]>0){
			res = findWays2(coins,counts, types-1, target);
			for(int i=1;i<=counts[types-1];i++){
				res += findWays2(coins,counts, types-1, target-i*coins[types-1]);
			}
			
		}
		else res = findWays2(coins,counts, types-1, target);
		
		return res;
	}
	
	// m is size of coins array (number of different coins)
	int minCoins(int coins[], int m, int V)
	{
	   // base case
	   if (V == 0) return 0;
	 
	   // Initialize result
	   int res = Integer.MAX_VALUE;
	 
	   // Try every coin that has smaller value than V
	   for (int i=0; i<m; i++)
	   {
	     if (coins[i] <= V)
	     {
	         int sub_res = minCoins(coins, m, V-coins[i]);
	 
	         // Check for INT_MAX to avoid overflow and see if
	         // result can minimized
	         if (sub_res != Integer.MAX_VALUE && sub_res + 1 < res)
	            res = sub_res + 1;
	     }
	   }
	   return res;
	}
	
	public static void test(){
		WaysToChangeCoins ways = new WaysToChangeCoins();
		int[] coins = {1,2,5};
		int types = coins.length;
		int target = 5;
		ways.dp = new int[types+1][target+1];
		for(int i=0;i<=types;i++){
			for(int j=0;j<=target;j++){
				ways.dp[i][j]=-1;
			}
		}
		int[] counts={4,2,1};
		int res = ways.findWays2(coins,counts, types, target);
		res = ways.minCoins(coins, types, target);
		System.out.println(res);
	}
}
