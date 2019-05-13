import java.util.*;

public class Knight {

    static Map<Integer, List<Integer>> hopping = new HashMap<>();
    public static void main(String[] args) {
        hopping.put(0, Arrays.asList(4, 6));
        hopping.put(1, Arrays.asList(6, 8));
        hopping.put(2, Arrays.asList(7, 9));
        hopping.put(3, Arrays.asList(4, 8));
        hopping.put(4, Arrays.asList(0, 3, 9));
        hopping.put(5, Arrays.asList());
        hopping.put(6, Arrays.asList(0, 1, 7));
        hopping.put(7, Arrays.asList(2, 6));
        hopping.put(8, Arrays.asList(1, 3));
        hopping.put(9, Arrays.asList(2, 4));

        for (int i = 0; i <= 9; i++) {
            System.out.println(i + " -> " + reachable(i));
        }

        for(int i = 0; i <= 9; i++) {
            int[] visited = new int[10];
            Set<Integer> result = new HashSet<>();
            System.out.println(i + ":" + hoppedKeys(i, 2, visited, result));
        }
    }
    
    public static int reachable(int start) {
        return hopping.get(start).size();
    }

    
    public static int hoppedKeys(int start, int times, int[] visited, Set<Integer> result) {
        if(times == 1) {
            result.add(start);
            return result.size();
        }
        if (visited[start] == 0) {
            visited[start] = 1;
            result.add(start);
            for(int num : hopping.get(start)) {
                hoppedKeys(num, times - 1, visited, result);
            }
        }
        return result.size();
    }
    
}
