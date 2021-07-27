import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;
//Remove duplicates is really tricky part here, default hashcode is using internal memory address, if the object added in array is creating by new keyword
//set cannot remove that. Need to override the implementation of hashcode and equals function. Hashcode must be same, if they are equal. 
//Using x + y << 31 - y as a hashcode. 0.75 is default resizing factor; 
//Integer array? How many points? Duplicate same points-Count twice? 
public class validSquare {
	private static int distance(int [] p, int [] q) {
		return (p[0] - q[0])*(p[0] - q[0]) + (p[1] - q[1])*(p[1] - q[1]);
	}
	private static boolean hashMethod(int [] a1, int [] a2, int [] a3, int [] a4) {
		if (a1 == null || a2 == null || a3 == null || a4 == null) {
			return false;
		}
		Set<Integer> allLength = new HashSet<Integer>();
		allLength.add(distance(a1,a2));
		allLength.add(distance(a1,a3));
		allLength.add(distance(a1,a4));
		allLength.add(distance(a2,a3));
		allLength.add(distance(a2,a4));
		allLength.add(distance(a3,a4));
		if (allLength.size() == 2 && !allLength.contains(0)) {
			//Corner Cases: 4 points, one point inside the equilateral, 4 points, rhombus, rectangule, 
			//4 Points, equilateral triangle, with one point is same as the one of the rest of three
			//two equilateral triangle form a shape, only two types of length
			return true;
		}
		return false;
	}
	private static boolean sortMethod(int [] a1, int [] a2, int [] a3, int [] a4) {
		if (a1 == null || a2 == null || a3 == null || a4 == null) {
			return false;
		}
		int[][] all_points = {a1,a2,a3,a4};
		Arrays.sort(all_points, (a,b) -> a[0] == b[0] ? a[1] - b[1] : a[0] - b[0]);
		int s1 = distance(all_points[0], all_points[1]);
		int s2 = distance(all_points[0], all_points[2]);
		int s3 = distance(all_points[1], all_points[3]);
		int s4 = distance(all_points[2], all_points[3]);
		int diagonal = distance(all_points[0], all_points[3]);
		if (s1 == s2 && s2 == s3 && s3 == s4 && diagonal == 2 * s1 && s1 != 0) {
			return true;
		}
		return false;
	}
	private static int distance2(Point p, Point q) {
		return (p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y);
	}
	private static boolean hashMethod2(Point a1, Point a2, Point a3, Point a4) {
		if (a1 == null || a2 == null || a3 == null || a4 == null) {
			return false;
		}
		Set<Integer> allLength = new HashSet<Integer>();
		allLength.add(distance2(a1,a2));
		allLength.add(distance2(a1,a3));
		allLength.add(distance2(a1,a4));
		allLength.add(distance2(a2,a3));
		allLength.add(distance2(a2,a4));
		allLength.add(distance2(a3,a4));
		if (allLength.size() == 2 && !allLength.contains(0)) {
			//Corner Cases: 3 points, isosceles triangle, 4 points, one point inside the equilateral, 4 points, rhombus, rectangule
			return true;
		}
		return false;
	}
	private static int numSquare(ArrayList<int[]> points) {
		if (points.size() < 4) {
			return 0;
		}
		int count = 0;
		Set<Point> all_points = new HashSet<Point> ();
		for (int i = 0; i < points.size(); ++i) {
			all_points.add(new Point(points.get(i)));
		}
		ArrayList<Point> refinedPoints = new ArrayList<Point>(all_points);
		for (int i = 0; i < refinedPoints.size(); ++i) {
			for (int j = i + 1; j < refinedPoints.size(); ++j) {
				for (int k = j + 1; k < refinedPoints.size(); ++k) {
					for (int t = k + 1; t < refinedPoints.size(); ++t) {
						if (hashMethod2(refinedPoints.get(i), refinedPoints.get(j), refinedPoints.get(k), refinedPoints.get(t))) {
							++count;
						}
					}
				}
			}
		}
		return count;
	}
	//if Coding in the way j = i + 1, k = j + 1, non-deterministic behavior E.G 01 10 -> 11 00, when deal with some points, it cannot check back. Only one 
	//Diagonal has been resolving
	private static int numSquare2(ArrayList<int[]> points) {
		if (points.size() < 4) {
			return 0;
		}
		int count = 0;
		Set<Point> deduplicate = new HashSet<Point>();
		for (int i = 0; i < points.size(); ++i) {
			deduplicate.add(new Point(points.get(i)));
		}
		ArrayList<Point> all_points = new ArrayList<Point>(deduplicate);
		//if last two points form a diagonal, fails
		for (int i = 0; i < all_points.size(); ++i) {
			for (int j = 0; j < all_points.size(); ++j) {
				if (i == j) {
					continue;
				}
				int d1 = distance2(all_points.get(i), all_points.get(j));
				for (int k = 0; k < all_points.size(); ++k) {
					if (k == i || k == j) {
						continue;
					}
					int d2 = distance2(all_points.get(k), all_points.get(j));
					int d3 = distance2(all_points.get(i), all_points.get(k));
					if (d2 == d3 && d1 == 2 * d3) {
						int[] container = new int[2];
						container[0] = all_points.get(i).x + all_points.get(j).x - all_points.get(k).x;
						container[1] = all_points.get(i).y + all_points.get(j).y - all_points.get(k).y;
						Point temp = new Point(container);
						if (deduplicate.contains(temp)) {
							++count;
							break;
						}
					}
				}
			}
		}
		return count/4;//each diagonal checks twice, because two points on one diagonal
	}
	private static int numSquare3(ArrayList<int[]> points) {
		if (points.size() < 4) {
			return 0;
		}
		int count = 0;
		Set<Point> deduplicate = new HashSet<Point>();
		for (int i = 0; i < points.size(); ++i) {
			deduplicate.add(new Point(points.get(i)));
		}
		ArrayList<Point> all_points = new ArrayList<Point>(deduplicate);
		for (int i = 0; i < all_points.size(); ++i) {
			for (int j = i + 1; j < all_points.size(); ++j) {
				Point temp1 = new Point();
				Point temp2 = new Point();
				Point temp3 = new Point();
				Point temp4 = new Point();
				temp1.x = all_points.get(i).x - (all_points.get(i).y - all_points.get(j).y);
				temp1.y = all_points.get(i).y + (all_points.get(i).x - all_points.get(j).x);
				temp2.x = all_points.get(j).x - (all_points.get(i).y - all_points.get(j).y);
				temp2.y = all_points.get(j).y + (all_points.get(i).x - all_points.get(j).x);
				temp3.x = all_points.get(i).x + (all_points.get(i).y - all_points.get(j).y);
				temp3.y = all_points.get(i).y - (all_points.get(i).x - all_points.get(j).x);
				temp4.x = all_points.get(j).x + (all_points.get(i).y - all_points.get(j).y);
				temp4.y = all_points.get(j).y - (all_points.get(i).x - all_points.get(j).x);
				if (deduplicate.contains(temp1) && deduplicate.contains(temp2)) {
					++count;
				}
				if (deduplicate.contains(temp3) && deduplicate.contains(temp4)) {
					++count;
				}
			}
		}
		return count/4;// 
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int [] a1 = new int[]{0,1};
		int [] a2 = new int[]{1,2};
		int [] a3 = new int[]{1,0};
		int [] a4 = new int[]{2,1};
		int [] a5 = new int[]{0,0};
		int [] a6 = new int[]{0,1};
		int [] a7 = new int[]{1,1};
		int [] a8 = new int[]{1,0};
		int [] b1 = new int[]{0,0};
		int [] b2 = new int[]{0,1};
		int [] b3 = new int[]{-1,1};
		int [] b4 = new int[]{-1,0};
		int [] b5 = new int[]{0,0};
		int [] b6 = new int[]{0,-1};
		int [] b7 = new int[]{1,-1};
		int [] b8 = new int[]{1,0};
		int [] c1 = new int[]{0,0};
		int [] c2 = new int[]{0,-1};
		int [] c3 = new int[]{-1,-1};
		int [] c4 = new int[]{-1,0};
		ArrayList<int[]> allPoints = new ArrayList<int[]>();
		allPoints.add(a1);
		allPoints.add(a2);
		allPoints.add(a3);
		allPoints.add(a4);
		allPoints.add(a5);
		allPoints.add(a6);
		allPoints.add(a7);
		allPoints.add(a8);
		allPoints.add(b1);
		allPoints.add(b2);
		allPoints.add(b3);
		allPoints.add(b4);
		allPoints.add(b5);
		allPoints.add(b6);
		allPoints.add(b7);
		allPoints.add(b8);
		allPoints.add(c1);
		allPoints.add(c2);
		allPoints.add(c3);
		allPoints.add(c4);
 		System.out.println(hashMethod(a1,a2,a3,a4));
		System.out.println(sortMethod(a1,a2,a3,a4));
		System.out.println(numSquare(allPoints));
		System.out.println(numSquare2(allPoints));
		System.out.println(numSquare3(allPoints));
	}
}
