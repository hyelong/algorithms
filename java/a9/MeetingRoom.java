/*
Given an array of meeting time intervals consisting of start and end times 
[[s1,e1],[s2,e2],...] (si < ei), determine if a person could attend all meetings. 
For example, Given [[0, 30],[5, 10],[15, 20]], return false.
*/
import java.util.*;

class Interval{
    public int start;
    public int end;
    public Interval(int start, int end){
        this.start = start;
        this.end = end;
    }
}
public class MeetingRoom{
  boolean canAttendMeetings(Interval[] intervals){
    Arrays.sort(intervals, new Comparator<Interval>(){
      public int compare(Interval i1, Interval i2){
          if(i1.start < i2.start) return -1;
          return 1;
      }
    });
    for(int i=1; i<intervals.length;i++){
      if(intervals[i-1].end > intervals[i].start) return false;
    }
    return true;
  }
 
  int minMeetingRooms(Interval[] intervals) {
        if(intervals == null || intervals.length == 0) {
            return 0;
        }
        
        Arrays.sort(intervals, new Comparator<Interval>() {
            @Override
            public int compare(Interval int1, Interval int2) {
                return Integer.compare(int1.start, int2.start);
            }
        });
        
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        pq.add(intervals[0].end);
        int roomRequired = 1;
        
        for(int i = 1; i<intervals.length; i++) {
            Interval cur = intervals[i];
            while(!pq.isEmpty() && cur.start >= pq.peek()) {
                pq.poll();
            }
            pq.add(cur.end);
            roomRequired = pq.size() > roomRequired ? pq.size() : roomRequired;
        }
        
        return roomRequired;
    }
 
  public static void main(String[] args){
    MeetingRoom room = new MeetingRoom();
    Interval[] intervals = {new Interval(0,30), new Interval(5,10), new Interval(15, 20)};
    boolean res = room.canAttendMeetings(intervals);
    System.out.println(res);
		System.out.println(room.minMeetingRooms(intervals));
  }
}
