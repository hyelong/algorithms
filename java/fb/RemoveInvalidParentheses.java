import java.util.*;
import java.lang.*;

public class RemoveInvalidParentheses {
    public static void main(String[] args) {
        String s1="a(b))";
        String s2 = "(a(c()b)";
        String s3 =")(";
        String s4= "(a)b(c)d(e)f)(g)";
        String s5 ="ab(a(c)fg)9)";
        String s6 =   ")a(b)c()(";
            
        char[] pair = new char[]{'(', ')'};
        char[] pair1 = new char[]{')', '('};
        System.out.println(new StringBuilder(removep(new StringBuilder(removep(s1, pair)).reverse().toString(), pair1)).reverse().toString());
        System.out.println(new StringBuilder(removep(new StringBuilder(removep(s2, pair)).reverse().toString(), pair1)).reverse().toString());
        System.out.println(new StringBuilder(removep(new StringBuilder(removep(s3, pair)).reverse().toString(), pair1)).reverse().toString());
        System.out.println(new StringBuilder(removep(new StringBuilder(removep(s4, pair)).reverse().toString(), pair1)).reverse().toString());
        System.out.println(new StringBuilder(removep(new StringBuilder(removep(s5, pair)).reverse().toString(), pair1)).reverse().toString());
        System.out.println(new StringBuilder(removep(new StringBuilder(removep(s6, pair)).reverse().toString(), pair1)).reverse().toString());
    }
    public static String removep(String sb, char[] pair){
        if (sb == null) return null;
        StringBuilder res = new StringBuilder();
        int lc = 0; 
        for(int i=0;i<sb.length();i++){
            char c = sb.charAt(i);
            if(c == pair[0]){
                lc++;
            }
            else if(c == pair[1]){
                lc--;
                if (lc < 0) {
                    lc = 0;
                    continue;
                }
            }
            res.append(c);
        }
        return res.toString();
    }
}
