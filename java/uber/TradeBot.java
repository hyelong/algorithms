/*
 * Question 3
You've decided to create a bot for handling stock trades. For now, you have a simple prototype which handles trades for just one stock. Each day, it's programmed to either buy or sell one share of the stock.
You are given prices, an array of positive integers where prices[i] represents the stock price on the ith day. You're also given algo, an array of 0s and 1s representing the bot's schedule, where 0 means buy and 1 means sell.
In order to improve the bot's performance, you'd like to choose a range of k consecutive days where the bot will be programmed to sell; in other words, set a range of k consecutive elements from algo to 1. Your task is to choose the interval such that it maximizes the bot's total revenue. The revenue is defined as the sum of all selling prices minus the sum of all buying prices (in other words, the difference between the end and start amount).
NOTE: Assume you begin with enough shares of the stock that it's always possible to sell.
Example
For prices = [2, 4, 1, 5, 2, 6, 7], algo = [0, 1, 0, 0, 1, 0, 0], and k = 4, the output should be maxRevenueFromStocks(prices, algo, k) = 21.
First, let's calculate the revenue if the algorithm is left as it is without any change.
• Before the trades start, the revenue is 0;
• Day 0: algo[0] = 0, so we buy stocks at price prices[0] = 2, and the revenue becomes 0 - 2 = -2;
• Day 1: algo[1] = 1, so we sell stocks at price prices[1] = 4, and the revenue becomes -2 + 4 = 2;
• Day 2: algo[2] = 0, so we buy stocks at price prices[2] = 1, and the revenue becomes 2 - 1 = 1;
• Day 3: algo[3] = 0, so we buy stocks at price prices[3] = 5, and the revenue becomes 1 - 5 = -4;
• Day 4: algo[4] = 1, so we sell stocks at price prices[4] = 2, and the revenue becomes -4 + 2 = -2;
• Day 5: algo[5] = 0, so we buy stocks at price prices[5] = 6, and the revenue becomes -2 - 6 = -8;
• Day 6: algo[6] = 0, so we buy stocks at price prices[6] = 7, and the revenue becomes -8 - 7 = -15.
Thus, the total revenue is -15.

We can maximize the total revenue by making the last k = 4 orders 1 (sell), thus making algo = [0, 1, 0, 1, 1, 1, 1]. The total revenue will become -2 + 4 - 1 + 5 + 2 + 6 + 7 = 21.
*/

import java.util.*;

public class TradeBot {
    public static void main(String args[]) {
        int[] prices = new int[] {2, 4, 1, 5, 2, 6, 7};
        int[] algo = new int[] {0, 1, 0, 0, 1, 0, 0};
        int k = 4;
        TradeBot tradeBot = new TradeBot();
        int res = tradeBot.trade(prices, algo, k);
        System.out.println(res);
    }

    private int trade(int[] prices, int[] algo, int k) {
        int[] prefixSum = new int[prices.length + 1];
        int sum = 0;
        for (int i = 0; i < prices.length; i++) {
            if (algo[i] == 0)
                sum -= prices[i];
            else sum += prices[i];

            prefixSum[i + 1] = sum;
        }
        int total = sum;
        int res = Integer.MIN_VALUE;
        for (int i = k - 1; i < prices.length; i++) {
            int newValue = total - (prefixSum[i + 1] - prefixSum[i + 1 - k]);
            for (int j = i + 1 - k; j <= i; j++) {
                newValue += prices[j];
            }
            res = Math.max(res, newValue);
        }
        return res;
    }
}
