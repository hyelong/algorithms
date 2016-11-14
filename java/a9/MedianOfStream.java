import java.util.*;

class MedianFinder {
    private PriorityQueue<Integer> pq1 = new PriorityQueue<>(
            new Comparator<Integer>(){
                public int compare(Integer a, Integer b){
                  if(a < b) return 1;
                  return -1;
                }
            }
    );
    // by default, the first element is the smallest one
    private PriorityQueue<Integer> pq2 = new PriorityQueue<>();
    
    // Adds a number into the data structure.
    public void addNum(int num) {
      pq2.add(num); 
      pq1.add(pq2.poll());
      if(pq2.size() < pq1.size()) pq2.add(pq1.poll());
    }

    // Returns the median of current data stream
    public double findMedian() {
      int n = pq1.size() + pq2.size();
      if(n%2 == 0) return (pq1.peek() + pq2.peek())/(double)2.0;
      return pq2.peek();
    }
};

public class MedianOfStream{
  public static void main(String[] args){
      MedianFinder median = new MedianFinder();
      median.addNum(1);
      median.addNum(2);
      median.addNum(3);
      median.addNum(5);
      System.out.println(median.findMedian());
  }
}
