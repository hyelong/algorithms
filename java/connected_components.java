import java.util.*;
public class connected_components{
    public static void main(String[] args){
        connected_components c = new connected_components();
        int[][] edges = new int[][]{{2,3},{3,4},{5,6}};
        List<List<Integer>> res = c.connected_component(edges);
        for(List<Integer> list : res){
            for(int i : list) 
                System.out.print(i+" ");
            System.out.println();
        }
    }

    List<List<Integer>> connected_component(int[][] edges){
        Set<Integer> nums = new HashSet<>();
        for(int[] edge : edges){
            nums.add(edge[0]);
            nums.add(edge[1]);
        }

        Map<Integer, Integer> roots = new HashMap<>();
        for(int i : nums) roots.put(i, i);

        for(int[] edge : edges){
            int x = find_rec(roots, edge[0]);
            int y = find_rec(roots, edge[1]);
            if(x!=y) roots.put(x, y);
        }
        Map<Integer, List<Integer>> components = new HashMap<>();
        for(int i : nums){
            int root = find(roots, i);
            if(!components.containsKey(root)){
                components.put(root, new ArrayList<Integer>());
            }
            components.get(root).add(i);
        }
        List<List<Integer>> res = new ArrayList<>();
        for(int key : components.keySet()){
            System.out.println("key:"+key);
            res.add(components.get(key));
        }
        return res;
    }

    int find(Map<Integer, Integer> roots, int id){
        int x = id;
        while(id!=roots.get(id)){
            id = roots.get(id);
        }
        while(roots.get(x)!=id){
            int parent = roots.get(x);
            roots.put(x, id);
            x = parent;
        }
        return id;
    }

    int find_rec(Map<Integer, Integer> roots, int id){
        if(id == roots.get(id)) return id;
        int res = find_rec(roots, roots.get(id));
        roots.put(roots.get(id), res);
        return res;
    }
}
