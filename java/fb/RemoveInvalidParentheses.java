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
            
            
           
        System.out.println(removep(s1));
        System.out.println(removep(s2));
        System.out.println(removep(s3));
        System.out.println(removep(s4));
        System.out.println(removep(s5));
        System.out.println(removep(s6));
    }
    public static String removep(String s){
        if(s==null || s.length()==0)
            return s;
        StringBuilder res = new StringBuilder();
        Stack<Character> st = new Stack<Character>();
        int lc = 0; 
        for(int i=0;i<s.length();i++){
            char c = s.charAt(i);
            if(c == '('){
                st.push(c);
                lc++;
            }
            else if(c == ')'){
                if(lc == 0){//skip
                    continue;
                }else{
                    lc--;
                    st.push(c);
                }
            }
            else
              st.push(c);  
        }
        while(!st.empty()){
            char c = st.pop();
            if(c == '(' && lc >0){
                lc--;
                continue;
            }
            res.append(c);
        }
        return res.reverse().toString();
    }
}