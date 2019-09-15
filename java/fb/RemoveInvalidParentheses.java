import java.util.*;

public class RemoveInvalidParentheses {
    public static void main(String[] args) {
        System.out.println("Hello World!");
        String s1="a(b))";
        String s2 = "(a(c()b)";
        String s3 =")(";
        String s4= "(a)b(c)d(e)f)(g)";
        String s5 ="ab(a(c)fg)9)";
        String s6 =   ")a(b)c()(";
            
            
        char[] pair = new char[]{')', '('};
        System.out.println(removep(new StringBuiler(s1), pair));
        System.out.println(removep(new StringBuiler(s2), pair));
        System.out.println(removep(new StringBuiler(s3), pair));
        System.out.println(removep(new StringBuiler(s4), pair));
        System.out.println(removep(new StringBuiler(s5), pair));
        System.out.println(removep(new StringBuiler(s6), pair));
    }
    public static String removep(StringBuilder sb, char[] pair){
        if (sb == null) return null;
        int lc = 0; 
        for(int i=0;i<sb.length();i++){
            char c = sb.charAt(i);
            if(c == pair[0]){
                lc++;
            }
            else if(c == pair[1]){
                if(lc == 0){//skip
                    continue;
                }else{
                    lc--;
                }
            }
        }
        if (pair[0] == '(') removep(sb.reverse(), new char[]{')', '('});
        return res.reverse().toString();
    }
}