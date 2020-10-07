/** 
  * 给你一个n * n 的矩阵， 分成size * size的block
  * n % size == 0
  */
import java.util.*;

public class BlockPrinter{
    public static void main(String[] args) {
        int[][] grid = new int[][] { {1,2,3,4},
                                     {5,6,7,8},
                                     {3,2,1,4},
                                     {1,5,2,3}
                                    };
        BlockPrinter bp = new BlockPrinter();
        List<List<Integer>> res = new ArrayList<>();
        bp.print(grid, 2, res);

        System.out.println("Writing back:");
        bp.write_back(res, 2, grid);
    }

    void print(int[][] grid, int block_size, List<List<Integer>> res) {
        int n = grid.length;
        for (int i = 0; i < n; i++) {
            List<Integer> block = new ArrayList<>();
            for (int j = 0; j < n; j++) {
                int value = grid[i / block_size * block_size + j / block_size][i % block_size * block_size + j % block_size];
                block.add(value);
                System.out.print(value);
                System.out.print(", ");
            }
            System.out.println();
            res.add(block);
        }
    }

    void write_back(List<List<Integer>> res, int block_size, int[][] grid) {
        int n = grid.length;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                grid[i / block_size * block_size + j / block_size][i % block_size * block_size + j % block_size] = res.get(i).get(j);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                System.out.print(grid[i][j]);
                System.out.print(", ");
            }
            System.out.println();
        }
    }
}

