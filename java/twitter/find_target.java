import java.util.*;

public class find_target{
    public static void main(String[] args){
        find_target f = new find_target();   
        boolean res = f.find(2,12,7);
        Set<Integer> visited = new HashSet<>();
        List<Integer> path = new ArrayList<>();
        res = f.dfs(2,12,6, visited, path);
        System.out.println(res);
        visited = new HashSet<>();
        res = f.recursive(8,12,4,0,visited);
        System.out.println(res);
    }

    boolean find(int m, int n, int target){
        if(target > Math.max(m, n)) return false;
        Set<Integer> visited = new HashSet<>();
        Queue<Integer> q = new LinkedList<>();
        visited.add(target);
        int diff = Math.abs(m-target);
        if(!visited.contains(diff)){
            q.offer(diff);
            visited.add(diff);
        }
        diff = Math.abs(n-target);
        if(!visited.contains(diff)){
            q.offer(diff);
            visited.add(diff);
        }
        while(!q.isEmpty()){
            int cur = q.poll();
            if(cur==0) return true;
            
            diff = Math.abs(m-cur);
            if(!visited.contains(diff)){
                q.offer(diff);
                visited.add(diff);
            }
            diff = Math.abs(n-cur);
            if(!visited.contains(diff)){
                q.offer(diff);
                visited.add(diff);
            }
        }
        return false;
    }
    
    boolean dfs(int m, int n, int target, Set<Integer> visited, List<Integer> path){
        path.add(target);
        if(target==0) return true;
        if(visited.contains(target)) return false;
        visited.add(target);
        if(dfs(m,n,Math.abs(m-target),visited,path)) return true;
        if(dfs(m,n,Math.abs(n-target),visited,path)) return true;
        path.remove(path.size()-1);
        return false;
    }

    boolean recursive(int m, int n,int can_make, int target, Set<Integer> visited){
        if(m>n) return recursive(n,m,can_make,target,visited);
        if(can_make==target) return true;
        if(visited.contains(can_make)) return false;
        visited.add(can_make);
        return recursive(m, n, (can_make+m)%n, target, visited);
    }
}
