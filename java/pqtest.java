import java.util.*;

public class pqtest{
  public static void main(String[] args){
    PriorityQueue<Integer> pq = new PriorityQueue<>();
    for(int i=9;i>0;i--){
      pq.add(i);
    }

    for(int num : pq) System.out.println(num);
    System.out.println("---------------------------");
    while(!pq.isEmpty()){
      System.out.println(pq.remove());
    }
  }
}
