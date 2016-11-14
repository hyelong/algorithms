
import java.math.BigInteger;

public class Carrotland{
	public static void main(String[] args){
	
		int[][] vertices = new int[][]{{0,1},{1,0},{-1,-1}};
		double A = area(vertices);
		long b = pointsOnBoudary(vertices);
		System.out.println(b);
		long i = (long)(A  - (double)b/2) + 1;
		System.out.println(i);
	}
	
	static double area(int[][] vertices){
		long x1 = vertices[0][0], y1 = vertices[0][1],
		x2 = vertices[1][0], y2 = vertices[1][1],
		x3 = vertices[2][0], y3 = vertices[2][1];
		
		return 0.5*Math.abs(x1*y2+x2*y3+x3*y1-y1*x2-y2*x3-y3*x1);
	}
	
	static long pointsOnBoudary(int[][] vertices){
		int x1 = vertices[0][0], y1 = vertices[0][1],
		x2 = vertices[1][0], y2 = vertices[1][1],
		x3 = vertices[2][0], y3 = vertices[2][1];
		return gcd(Math.abs(x1 - x2), Math.abs(y1 - y2)) 
    + gcd(Math.abs(x2 - x3), Math.abs(y2 - y3)) 
    + gcd(Math.abs(x3 - x1), Math.abs(y3 - y1));
	}
	
	static long gcd(long a, long b){
		return BigInteger.valueOf(a).gcd(BigInteger.valueOf(b)).longValue();
	}
}
