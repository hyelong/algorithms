import java.util.*;

public class longestSubstringDistictK{
    public static void main(String[] args){
        longestSubstringDistictK l = new longestSubstringDistictK();
        String s = "aaaaabbcccc";
        int k = 1;
        int res = l.longestSubWithK(s, k);
        System.out.println(res);
    }

    int longestSubWithK(String s, int k){
        if(s==null || s.length()==0 || k==0) return 0;
        int res = 0;
        Map<Character, Integer> visited = new HashMap<>();
        int left=0;
        visited.put(s.charAt(0), 1);
        for(int right = 1; right<s.length(); right++){
            char c = s.charAt(right);
            if(visited.containsKey(c)){
                visited.put(c, visited.get(c)+1);
            }
            else{
                if(visited.size()==k){
                    res = Math.max(res, right-left);
                    while(left < right){
                        char cur = s.charAt(left);
                        visited.put(cur, visited.get(cur)-1);
                        left++;
                        if(visited.get(cur)==0){
                            visited.remove(cur);
                            break;
                        }
                    }
                }
                visited.put(c, 1);
            }
        }
        res = Math.max(res, s.length() - left);
        return res;
    }

}
