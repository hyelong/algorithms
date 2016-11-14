import java.util.*;

public class count_permution_inversion{
    public static void main(String[] args){
        count_permution_inversion count = new count_permution_inversion();
        int n = 5, k = 5;
        int[][] dp = new int[n+1][k+1];
        for(int i=0;i<=n;i++){
            for(int j=0;j<=k;j++){
                dp[i][j] = -1;
            }
        }
        int res = count.count_inversions(n, k, dp);
        System.out.println(res);
    }

    int count_inversions(int n, int k, int[][] dp){
        if(dp[n][k]!=-1) return dp[n][k];
        if(k==0) return 1;
        if(n==0) return 0;
        int val = 0;
        for(int j = 0; j<n && j<=k;j++){
            val += count_inversions(n-1, k-j, dp);
        }
        dp[n][k] = val;
        return val;
    }
}
