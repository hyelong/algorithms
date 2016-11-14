import java.util.*;

public class ZombieCluster{
    public static void main(String[] args){
        int[][] matrix = new int[][]{{1,1,0,1},{1,1,1,0},{0,1,1,0},{1,0,0,1}};
        int n = matrix.length;
        UnionFind uf = new UnionFind(n);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(matrix[i][j]==1){
                    uf.union(i,j);
                }
            }
        }
        System.out.println(uf.set_nums());
    }
}

class UnionFind{
    int[] father;
    public UnionFind(int n){
        father = new int[n];
        for(int i=0;i<n;i++){
            father[i] = i;
        }
    }
    public int find(int x){
        if(x == father[x]) return x;
        int fa = father[x];
        int res = father[fa];
        father[x] = res;
        return res;
    }

    public void union(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y) return;
        father[y] = x;
    }

    public int set_nums(){
        int count = 0;
        for(int i=0;i<father.length;i++)
        if(father[i]==i) count++;
        return count;
    }
}
