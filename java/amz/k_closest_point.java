/**
*Find the K closest points to the origin in a 2D plane, given an array containing N points.
*/

import java.util.*;

public class k_closest_point{
    List<Point> findKClosest(Point[] p, int k){
        PriorityQueue<Point> pq = new PriorityQueue<>(new Comparator<Point>(){
            public int compare(Point a, Point b){
                return (b.x*b.x + b.y*b.y)-(a.x*a.x + a.y*a.y);
            }
        });

        for(int i=0;i<p.length;i++){
            if(i<k) pq.offer(p[i]);
            else{
                Point temp = pq.peek();
                if(p[i].x*p[i].x + p[i].y*p[i].y<(temp.x*temp.x + temp.y+temp.y)){
                    pq.poll();
                    pq.offer(p[i]);
                }
            }
        }

        List<Point> res = new ArrayList<>();
        while(!pq.isEmpty()) res.add(pq.poll());
        return res;
    }

    public static void main(String[] args){
        Point[] ps = new Point[]{new Point(1,1), new Point(3,4), new Point(3,5), new Point(6,8)};
        List<Point> res = new k_closest_point().findKClosest(ps, 2);
        for(Point p:res){
            System.out.println(p.x+","+p.y);
        }
    }
}

class Point{
    public int x;
    public int y;
    public Point(int x, int y){
        this.x = x;
        this.y = y;
    }
}
