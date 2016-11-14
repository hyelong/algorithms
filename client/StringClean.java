
import java.util.*;

public class StringClean {   
    public static void main(String[] args){
    String chunk = "goodgooogoogfogoood";
		String word = "goo";
		String res = answer(chunk, word);
		System.out.println(res);
    }
    public static String answer(String chunk, String word) { 

        // Your code goes here.
        if(chunk.indexOf(word)<0) return chunk;
        
        List<String> res = new ArrayList<>();
        Set<String> solved = new HashSet<>();
        helper(chunk, word, res, solved);
        Collections.sort(res);
        return res.get(0);
    } 
    
    static void helper(String chunk, String word, List<String> res, 
                       Set<String> solved){
        if(solved.contains(chunk)) return;
        if(chunk.indexOf(word)<0){
            res.add(chunk);
        }
        else{
            List<String> candidates = findAll(chunk, word);
            solved.add(chunk);
            for(String sub : candidates){
                helper(sub, word, res, solved);
            }
        }
    }
    
    static List<String> findAll(String chunk, String word){
        List<String> res = new ArrayList<>();
        int n = chunk.length();
        int m = word.length();
        for(int i=0;i<=n-m;i++){
            int pos = chunk.indexOf(word, i);
            if(pos>=0) 
            res.add(chunk.substring(0, pos)+chunk.substring(pos+m));
        }
        return res;
    }
}
