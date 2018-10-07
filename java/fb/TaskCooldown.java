import java.util.*;

public class TaskCooldown {
    private static int calculate(List<String> tasks, int cooldown) {
        int n = tasks.size();
        Map<String, Integer> taskPos = new HashMap<>();
        int res = 0;
        for (int i = 0; i < n; i++) {
            if (taskPos.containsKey(tasks.get(i))) {
                while(taskPos.get(tasks.get(i)) + cooldown >= res) res++;
            }
            taskPos.put(tasks.get(i), res);
            res++;
        }
        return res;
    }
    public static void main(String[] args) {
        List<String> tasks = Arrays.asList("A", "B", "A", "A", "B", "C", "C");
        int cooldown = 3;
        int res = calculate(tasks, cooldown);
        System.out.println(res);
    }
}
