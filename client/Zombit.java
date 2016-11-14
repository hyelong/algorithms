
import java.util.*;

public class Zombit {   
    public static void main(String[] args){
        int[][] meetings = new int[][]{{0, 1000000}, {42, 43}, {0, 1000000}, {42, 43}};
	int res = answer(meetings);
	System.out.println(res);
    }
    public static int answer(int[][] meetings) { 

        // Your code goes here.
        List<Interval> intervals = new ArrayList<>();
        int n = meetings.length;
        if(n<2) return n;
        for(int i=0;i<n;i++){
            intervals.add(new Interval(meetings[i][0], meetings[i][1]));
        }
        
        List<Interval> res = merge(intervals);
        return res.size();
        
    } 
    
    public static List<Interval> merge(List<Interval> intervals) {
       if(intervals.size()<2) return intervals;
        Collections.sort(intervals, new Comparator<Interval>(){
            public int compare(Interval i1, Interval i2){
                return i1.end-i2.end;
            }
        });
        List<Interval> res = new ArrayList<>();
        res.add(intervals.get(0));
        for(int i=1;i<intervals.size();i++){
            Interval pre = res.get(res.size()-1);
            if(pre.end <= intervals.get(i).start)
                res.add(intervals.get(i));
        }
        return res;
    }
    
    public static class Interval {
      public int start;
      public int end;
      public Interval(int s, int e) { start = s; end = e; }
    }
}
