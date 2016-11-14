/*
 * 241, Different ways add parentheses
 */
import java.util.*;

public class DifferentWaysAddParentheses{
    
    List<Integer> diffWaysToCompute(String s){
      int n = s.length();
      Map<Integer, List<Integer>> cache = new HashMap<>();
      return diffWaysHelper(s, 0, n-1, cache);
    }

    List<Integer> diffWaysHelper(String s, int start, int end, Map<Integer, List<Integer>> cache){
      List<Integer> res = new ArrayList<>();
      if(start > end) return res;
      int key = start * s.length() + end;
      if(cache.containsKey(key)) return cache.get(key); 
      boolean has_op = false;
      for(int i = start; i<=end; i++){
          char c = s.charAt(i);
          if(c == '*' || c == '+' || c == '-'){
              has_op = true;
              List<Integer> left =  diffWaysHelper(s, start, i-1,cache);
              List<Integer> right = diffWaysHelper(s, i+1, end, cache);
              for(int num1 : left)
                  for(int num2 : right){
                      if(c == '*') res.add(num1 * num2);
                      else if(c == '+') res.add(num1 + num2);
                      else if(c == '-') res.add(num1 - num2);
                  }
          }
      }
      if(!has_op) {res.add(Integer.valueOf(s.substring(start,end+1)));}
      cache.put(key, res);
      return res;
    }

    public static void main(String[] args){
      DifferentWaysAddParentheses dwap = new DifferentWaysAddParentheses();
      System.out.println(dwap.diffWaysToCompute("2*3-4*5"));
    }
}
