/* 
 * reverse a stack in place.
 */
import java.util.*;

public class reverse_stack{
  private void reverseStack(Stack<Integer> st){
    if(st.isEmpty()) return;
    int top = st.pop();
    reverseStack(st);
    st.push(top);
  }
  public static void main(String[] args){
    Stack<Integer> st = new Stack<>();
    for(int i=1;i<=5;i++) st.push(i);
    reverse_stack rs = new reverse_stack();
    rs.reverseStack(st);

    for(int i : st) System.out.println(i);
  }
}
