import java.util.HashMap;
import java.util.Map;

public class CollatzConjecture {
    public static void main(String[] args) {
        int res = findLongestSteps(100);
        System.out.println(res);
    }

    private static int findLongestSteps(int num) {
        if (num < 1) return 0;
        int res = 0;
        Map<Integer, Integer> cache = new HashMap<>();
        for (int i = 1; i <= num; i++) {
            int steps = count(i, cache);
            res = Math.max(res, steps);
            System.out.println(i + ":" + steps);
        }
        return res;
    }

    private static int count(int num, Map<Integer, Integer> cache) {
        int origin = num;
        int steps = 0;
        while(num != 1) {
            if (cache.containsKey(num)) {
                steps = steps + cache.get(num);
                cache.put(origin, steps);
                return steps;
            }
            steps++;
            if (num % 2 == 0) {
                num = num / 2;
            } else {
                num = 3 * num + 1;
            }
        }
        cache.put(origin, steps);
        return steps;
    }
}