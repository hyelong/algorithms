/** Given a list of tasks, same task should be executed with a cooldown time, return
 *  total time needed. There may be a follow up, what if cooldown time is much bigger
 *  than the # of types of task.
 */
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

    private static int calculate_followup(List<String> tasks, int cooldown) {
      int n = tasks.size();
      Map<String, List<Integer>> taskPos = new HashMap<>();
      int res = 0;
      for (int i = 0; i < n; i++) {
        if (!taskPos.containsKey(tasks.get(i))) {
          taskPos.put(tasks.get(i), new ArrayList<>());
        } else {
          List<Integer> positions = taskPos.get(tasks.get(i));
          int lastPos = positions.get(positions.size() - 1);
          if (lastPos + cooldown >= res - 1)
            res += lastPos + cooldown - res + 1;
        }
        taskPos.get(tasks.get(i)).add(res);
        res++;
      }
      return res;
    }
    public static void main(String[] args) {
        List<String> tasks = Arrays.asList("A", "B", "A", "A", "B", "C", "C");
        int cooldown = 10;
        int res = calculate(tasks, cooldown);
        System.out.println(res);
        res = calculate_followup(tasks, cooldown);
        System.out.println(res);
    }
}
