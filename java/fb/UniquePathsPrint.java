import java.util.*;
import java.lang.StringBuilder;

public class UniquePathsPrint {
    public static void main(String[] args) {
        StringBuilder path = new StringBuilder();
        List<String>  res = new ArrayList<>();
        boolean[][] visited = new boolean[7][3];
        UniquePathsPrint printer = new UniquePathsPrint();
        printer.dfs(7, 3, 0, 0, path, res, visited);
        for (String p : res) {
            System.out.println(p);
        }
    }

    private void dfs(int m, int n, int x, int y, StringBuilder path, List<String> res, boolean[][] visited) {
        if (x >= m || y >= n) return;
        if (visited[x][y]) return;
        visited[x][y] = true;
        int size = path.length();
        if (x == m - 1 && y == n - 1) {
            res.add(path.toString());
        }
        dfs(m, n, x + 1, y, path.append('D'), res, visited);
        dfs(m, n, x, y + 1, path.append('R'), res, visited);
        path.setLength(size);
        visited[x][y] = false;
    }
}