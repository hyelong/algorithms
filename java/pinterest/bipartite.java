import java.util.*;

public class bipartite{
    public static void main(String[] args){
        bipartite b = new bipartite();
        int[][] graph = new int[][]{{1,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}};
        boolean res = b.is_bipartite(graph, 4);
        int[][] edges = new int[][]{{1,2},{2,3},{1,4},{6,5},{5,7},{7,6}};
        res = b.is_bi(edges);
        System.out.println(res);
    }

    boolean is_bipartite(int[][] graph, int nodes){
        int[] color = new int[nodes];
        for(int i=0;i<nodes;i++) color[i] = -1;
        color[0] = 1;
        Queue<Integer> q = new LinkedList<>();
        q.add(0);
        while(q.isEmpty()==false){
            int u = q.poll();
            for(int v=0;v<nodes;v++){
                if(graph[u][v]!=1) continue;
                if(color[v]==-1){
                    color[v]=1-color[u];
                    q.add(v);
                }
                else if(color[v]==color[u]) return false;
            }
        }
        return true;
    }

    boolean is_bi(int[][] edges){
        int n = edges.length;
        Map<Integer, Integer> visited = new HashMap<>();
        for(int i=0;i<n;i++){
            int from = edges[i][0];
            int to = edges[i][1];
            if(!visited.containsKey(from) && !visited.containsKey(to)){
                visited.put(from, 0);
                visited.put(to, 1);
            }
            else if(visited.containsKey(from)){
                if(!visited.containsKey(to)) visited.put(to, 1-visited.get(from));
                else if(visited.get(from)==visited.get(to)) return false;
            }
            else if(visited.containsKey(to)){
                if(!visited.containsKey(from)) visited.put(from, 1-visited.get(to));
                else if(visited.get(from)==visited.get(to)) return false;
            }
        }
        return true;
    }
    
}
