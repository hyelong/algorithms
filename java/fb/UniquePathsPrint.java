import java.util.*;
import java.lang.StringBuilder;

public class UniquePathsPrint {
    public static void main(String[] args) {
        List<String>  res = new ArrayList<>();
        UniquePathsPrint printer = new UniquePathsPrint();
        printer.dfs(4, 2, 0, 0, "", res);
        for (String p : res) {
            System.out.println(p);
        }
    }

    private void dfs(int m, int n, int x, int y, String path, List<String> res) {
        if (x >= m || y >= n) return;
        if (x == m - 1 && y == n - 1) {
            res.add(path);
        } else {
            dfs(m, n, x, y + 1, path + 'R', res);
            dfs(m, n, x + 1, y, path + "D", res);
        }
    }
}