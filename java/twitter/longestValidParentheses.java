import java.util.*;

public class longestValidParentheses{
    public static void main(String[] args){
        longestValidParentheses l = new longestValidParentheses();
        String s = ")()())()()()";
        System.out.println(l.longestValid(s));
    }

    String longestValid(String s){
        if(s == null || s == "") return "";
        StringBuilder sb = new StringBuilder(s);
        Stack<Integer> indexes = new Stack<>();
        for(int i=0;i<sb.length();i++){
            if(sb.charAt(i)==')'){
                if(indexes.size() > 0){
                    sb.setCharAt(indexes.pop(), '0');
                    sb.setCharAt(i, '1');
                }
            }
            else{
                indexes.push(i);
            }
        }
      
        String res = "", cur = "";
        for(int i=0;i<sb.length();i++){
            if(sb.charAt(i)=='0' || sb.charAt(i)=='1'){
                if(sb.charAt(i)=='0') cur += '(';
                else cur += ')';
            }
            else{
                if(res.length() < cur.length()) {
                    res = cur;
                }
                cur = "";
            }
        }
        if(cur.length()>res.length()) res = cur;
        return res;
    }
}
