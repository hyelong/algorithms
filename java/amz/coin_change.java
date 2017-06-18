/**
 * Question: For US currency, there are six coins that are in use today: 1¢, 5¢, 10¢, 25¢, 50¢, 1$. Write a function that returns the number of possible combinations of change that can be made from n ¢. 
 * Example:
 * input: 7 output: 2 (7p, 1n 2p)
 * input: 10 output: 4 (1d, 10p, 2n, 1n 5p)
 * input: 15 output: 6 (1d 1n, 1d 5p, 3n, 2n 5p, 1n 10p, 15p)
 */

import java.util.*;

public class coin_change{
   
    int change(int[] coins, int m, int n){
        if(n < 0) return 0;
        if(n == 0) return 1;
        if(m <= 0 && n>=1) return 0;
        return change(coins, m-1, n) + change(coins, m, n-coins[m-1]);
    }
    public static void main(String[] args){
        int[] coins = {100, 50, 25, 10, 5, 1};
        int ways = new coin_change().change(coins, 6, 15);
        System.out.println(ways);
    }
}
