import java.util.*;

public class collect_coins{
    public static void main(String[] args){
        int[][] matrix = new int[][]{{3,1,1},{2,4,6},{1,-1,100}};
        collect_coins c = new collect_coins();
        int res = c.collect(matrix);
        System.out.println(res);
    }

    int collect(int[][] matrix){
        int n = matrix.length;
        if(n==0) return 0;
        int m = matrix[0].length;

        int[][] path = new int[n][m];
        if(matrix[n-1][0]<0) return 0;
        path[n-1][0] = matrix[n-1][0];
        // first column
        for(int i=n-2;i>=0;i--){
            if(matrix[i][0]>0) path[i][0] = path[i+1][0] + matrix[i][0];
            else break;
        }
        // last row
        for(int i=1;i<m;i++){
            if(matrix[n-1][i]>0) path[n-1][i] = path[n-1][i-1]+matrix[n-1][i];
            else break;
        }
        for(int i=n-2; i>=0;i--){
            for(int j=1;j<m;j++){
                 if(matrix[i][j]>0)
                    path[i][j] = Math.max(path[i+1][j], path[i][j-1])+matrix[i][j];
            }
        }
        print_path(matrix, path,0,m-1);  //0, m-1 is the start point.     
        return path[0][m-1];
    }

    void print_path(int[][] matrix, int[][] path, int x, int y){
        if(x==matrix.length && y==0) return;
        if(path[x][y]>0) System.out.println(x+","+y);
        // either below one or left one
        if(x+1<matrix.length && path[x+1][y]==path[x][y]-matrix[x][y]) print_path(matrix,path, x+1, y);
        else if(y-1>=0)print_path(matrix,path, x, y-1);
    }
}
