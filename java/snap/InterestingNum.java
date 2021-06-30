/** 
 * 找到K以下的所有interesting number。   
 * interesting number的定义是： num = a1^3 + a2^3 = b1^3 + b2^3  = ... 也就是说至少要有两对及以上立方根。
 * 比如1729  = 1^3 + 12^3 = 9^3 + 10^3
 * 那么这个数就是一个intersting number.  要求找到所有K以下的interesting number。
 * 为了简洁起见，规定K > 0, 立方根只考虑正数，并且所有计算在int范围内
 * https://www.techiedelight.com/numbers-represented-as-sum-of-two-cubes/
 */

import java.util.*;

public class InterestingNum {
    public static void main(String[] args) {
        InterestingNum in = new InterestingNum();
        int K = 25000;
        K = 65673928 + 1;
        in.printInterestingNum(K);
    }

    void printInterestingNum(int K) {
        Set<Integer> set = new HashSet<>();
        for (int i = 1; i < K; i++) {
            int v1 = i * i * i;
            if (v1 > K) break;
            for (int j = i + 1; j < K; j++) {
                int v2 = j * j * j;
                if (v2 > K) break;
                int sum = v1 + v2;
                if (sum < K) {
                    if (set.contains(sum)) {
                        System.out.println(sum + " = " + i + "^3" + " + " + j + "^3");
                    }
                    System.out.println(sum + " = " + i + "^3" + " + " + j + "^3");
                    set.add(sum);
                }
            }
        }
    }
}
