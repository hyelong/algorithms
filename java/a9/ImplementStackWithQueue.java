/*
 *Implement stack with two queues
 */

import java.util.*;

class MyStack {
    private Queue<Integer> q1 = new LinkedList<>();
    private Queue<Integer> q2 = new LinkedList<>();
    // Push element x onto stack.
    public void push(int x) {
        while(!q1.isEmpty()){
            q2.add(q1.poll());
        }
        q1.add(x);
        while(!q2.isEmpty()){
          q1.add(q2.poll());
        }
    }

    // Removes the element on top of the stack.
    public void pop() {
        q1.poll();
    }

    // Get the top element.
    public int top() {
        return q1.peek();
    }

    // Return whether the stack is empty.
    public boolean empty() {
        return q1.isEmpty();
    }
}
public class ImplementStackWithQueue{
    public static void main(String[] args){
      MyStack st = new MyStack();
      st.push(1);
      st.push(2);
      st.push(3);
      st.pop();
      System.out.println(st.top());

    }
}

