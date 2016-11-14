import java.util.*;

public class alien_dictionary{
    public static void main(String[] args){
        alien_dictionary a = new alien_dictionary();
        String[] words = new String[]{"wrt","wrf","er","ett","rftt"};
        String res = a.alien_order(words);
        System.out.println(res);
    }

    String alien_order(String[] words){
        Map<Character, Set<Character>> graph = new HashMap<>();
        for(int i=1;i<words.length;i++){
            String word1 = words[i-1];
            String word2 = words[i];
            int length = Math.min(word1.length(), word2.length());
            for(int j=0;j<length;j++){
                char c1 = word1.charAt(j);
                char c2 = word2.charAt(j);
                if(c1==c2) continue;
                if(!graph.containsKey(c1)) graph.put(c1, new HashSet<Character>());
                graph.get(c1).add(c2);
            }
        }
        return toposort(graph);
    }

    String toposort(Map<Character, Set<Character>> graph){
        Set<Character> visited = new HashSet<>();
        Set<Character> path = new HashSet<>();
        StringBuilder topo = new StringBuilder();
        for(char key : graph.keySet()) 
            if(!acyclic(graph, key, visited, path, topo)) return "";
        return topo.reverse().toString();
    }

    boolean acyclic(Map<Character, Set<Character>> graph, char cur,
            Set<Character> visited, Set<Character> path, StringBuilder topo){
                if(path.contains(cur)) return false;
                if(visited.contains(cur)) return true;
                visited.add(cur);
                path.add(cur);
                if(graph.get(cur)!=null){
                    for(char c : graph.get(cur)){
                        if(!acyclic(graph, c, visited, path, topo)) return false;
                    }
                }
                path.remove(cur);
                topo.append(cur);
                return true;
            }
}
