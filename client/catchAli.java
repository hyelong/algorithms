package FB;

/*
 *  finding ali baba
就是ali baba是个怪兽，他可能在[0，1, ..., numCaves-1]出现，他每隔一天就要换
一个地方，但他每次只能移左右一格。
然后给你一个strategy[]数组，数组里面是猜测每天ali baba的位置。如果里面有一个
猜中了，这个strategy就是正确的。
问题就是让你写一个判断函数 alibaba(int numCaves, int[] strategy)来判别这个
strategy数组是不是稳赢的策略。写完后问时间复杂度，然后问了下大概怎么样可以优
化～～～

 */
public class catchAli {
	public static boolean catchAlibaba(int numCaves, int[] strategy){
        int i,j,l=strategy.length;
        boolean[][] dp = new boolean[numCaves][l];
        dp[strategy[l-1]][l-1] = true;
        
        for(j=l-2;j>=0;j--){
                dp[0][j] = dp[1][j+1];
                for(i=1;i<numCaves-1;i++){
                        dp[i][j] = dp[i-1][j+1] && dp[i+1][j+1];  
                }
                dp[numCaves-1][j] = dp[numCaves-2][j+1];
                dp[strategy[j]][j] = true;
        }
        for(i=0;i<numCaves;i++){
                if(!dp[i][0]) return false;
        }
        return true;
	}
        
	public static void test(String[] args){
	        System.out.println(catchAlibaba(3, new int[]{1,1}));
	        System.out.println(catchAlibaba(4, new int[]{1,1,2,2,1}));
	}
}
