import java.util.*;
public class shortest_path_matrix{
    public static void main(String[] args){
        item start = new item(0, 0, 0);
        item end = new item(0, 2, 0);
        shortest_path_matrix s = new shortest_path_matrix();
        int[][] matrix = new int[][]{
            {0,1,0},
            {0,1,0},
            {0,0,0}
        };
        int d = s.shortest_path(matrix, start, end);
        System.out.println(d);
    }

    int shortest_path(int[][] matrix, item start, item end){
        Queue<item> q = new LinkedList<item>();
        q.offer(start);
        Set<Integer> visited = new HashSet<>();
        int n = matrix.length;
        int m = matrix[0].length;
        visited.add(start.x*m + start.y);
        while(!q.isEmpty()){
            item cur = q.poll();
            int x = cur.x, y = cur.y, d = cur.distance;
            if(x==end.x && y==end.y) {
                item temp = cur;
                while(temp!=null){
                    System.out.println(temp.x+","+temp.y);
                    temp = temp.parent;
                }
                return d;
            }
            if(x-1>=0 && matrix[x-1][y]==0 && !visited.contains((x-1)*m+y)){
                item next = new item(x-1,y,d+1);
                next.parent = cur;
                q.offer(next);
                visited.add((x-1)*m+y);
            }
            if(x+1<n && matrix[x+1][y]==0 && !visited.contains((x+1)*m+y)){
                item next = new item(x+1,y,d+1);
                next.parent = cur;
                q.offer(next);
                visited.add((x+1)*m+y);
            }
            if(y-1>=0 && matrix[x][y-1]==0 && !visited.contains(x*m+y-1)){
                item next = new item(x,y-1,d+1);
                next.parent = cur;
                q.offer(next);
                visited.add(x*m+y-1);
            }
            if(y+1<m && matrix[x][y+1]==0 && !visited.contains(x*m+y+1)){
                item next = new item(x,y+1,d+1);
                next.parent = cur;
                q.offer(next);
                visited.add(x*m+y+1);
            }
        }
        return -1;
    }
}

class item{
    public item parent;
    public int x;
    public int y;
    public int distance;
    public item(int x, int y, int d){
        this.x = x;
        this.y = y;
        this.distance = d;
    }
}
