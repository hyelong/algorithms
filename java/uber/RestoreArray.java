/**第四是原本有一个 N 个数组成的数组，但这个数组不会给你，只会给你这个数组里两两组成的 pair，一共有 N-1 个。这些 pair 的顺序是 shuffled，并且每个 pair 里的两个数也可能会互换顺序。要求还原数组。

比如给你的是 [[5, 4], [2, 4], [1, 3], [1, 5]]，要求输出 [3, 1, 5, 4, 2]（或者 [2, 4, 5, 1, 3] 也是正确答案）
*/
import java.util.*;

public class RestoreArray {
    public static void main(String[] args) {
        int[][] pairs = new int[][]{{5,4},{2,4}, {1,3}, {1,5}};
        int[] res = restore(pairs);
        for (int num : res) {
            System.out.print(num + ", ");
        }
        System.out.println();
    }

    static int[] restore(int[][] pairs) {
        int n = pairs.length;
        int[] res = new int[n + 1];
        Map<Integer, List<Integer>> graph = new HashMap<>();
        for (int[] pair : pairs) {
            if (!graph.containsKey(pair[0])) {
                graph.put(pair[0], new ArrayList<>());
            }
            graph.get(pair[0]).add(pair[1]);

            if (!graph.containsKey(pair[1])) {
                graph.put(pair[1], new ArrayList<>());
            }
            graph.get(pair[1]).add(pair[0]);
        }
        int start = -1;
        for (int key : graph.keySet()) {
            if (graph.get(key).size() == 1) {
                start = key;
                break;
            }
        }
        List<Integer> ans = new ArrayList<>();
        boolean[] visited = new boolean[n + 2];
        ans.add(start);
        dfs(graph, start, ans, visited);
        for (int i = 0; i < ans.size(); i++) {
            res[i] = ans.get(i);
        }
        return res;
    }

    static void dfs(Map<Integer, List<Integer>> graph, int start, List<Integer> ans, boolean[] visited) {
        if (ans.size() == graph.size()) {
            return;
        }
        if (visited[start]) return;
        visited[start] = true;
        for (int neigh : graph.get(start)) {
            if (visited[neigh]) continue;
            ans.add(neigh);
            dfs(graph, neigh, ans, visited);
        }
    }
}
