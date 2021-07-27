import java.util.ArrayList;

//double, int Two ways
public class drawCircle {
	static int r = 20;
	public static int squareDiff(int a, int b, int x, int y) {
		return (a-x)*(a-x) + (b-y)*(b-y);
	}
	public static int normalDiff(int a, int b, int x, int y) {
		int square = squareDiff(a,b,x,y);
		int normal = Math.abs(Math.sqrt(square) - r) > 1 ? 1 : 0;
		return normal;
	}
	//Slow and expensive in square root, but can take care of all points near the circle!
	public static ArrayList<int[]>draw1() {
		ArrayList<int[]> res = new ArrayList<int[]>();
		for (int i = -r; i < r + 1; ++i) {
			for (int j = -r; j < r + 1; ++j) {
				if (normalDiff(0,0,i,j) < 1) {
					res.add(new int[] {i,j});
				}
			}
		}
		//System.out.print(res.size());
		return res;
	}
	public static int calculateJ(int i) {
		double temp = Math.sqrt(r * r - i * i);
		int res = temp - (int) temp > 0.5 ? (int) temp + 1 : (int) temp;
		return res;
	}
	public static ArrayList<int[]>draw2() {
		ArrayList<int[]> res = new ArrayList<int[]>();
		for (int i = -r; i < r + 1; ++i) {
			int j = calculateJ(i);
			res.add(new int[] {i,j});
			res.add(new int[] {i, -j});
		}
		return res;
	}
	public static ArrayList<int[]>draw3() {
		ArrayList<int[]> res = new ArrayList<int[]>();
		for (int i = 0; i < r + 1; ++i) {
			int j = calculateJ(i);
			res.add(new int[] {i,j});
			res.add(new int[] {i, -j});
			res.add(new int[] {-i, -j});
			res.add(new int[] {-i, j});
		}
		return res;
	}
	public static void eightWay(ArrayList<int[]> res, int x, int y) {
		res.add(new int[] {x,y});
		res.add(new int[] {x,-y});
		res.add(new int[] {-x,y});
		res.add(new int[] {-x,-y});
		res.add(new int[] {-y,x});
		res.add(new int[] {y,-x});
		res.add(new int[] {-y,-x});
		res.add(new int[] {y,x});
	}
	public static ArrayList<int[]>draw4() {
		ArrayList<int[]> res = new ArrayList<int[]>();
		double limit = r/Math.sqrt(2);
		for (int i = 0; i < limit; ++i) {
			int j = calculateJ(i);
			eightWay(res, i, j);
		}
		return res;
	}
	public static double squareDiff2(double a, double b, int x, int y) {
		return (a-x)*(a-x) + (b-y)*(b-y);
	}
	public static ArrayList<int[]>draw5() {
		ArrayList<int[]> res = new ArrayList<int[]>();
		int i = 0;
		int j = r;
		while (i < j) {
			//System.out.println(i + " " + j);
			eightWay(res, i, j);
			double temp = squareDiff2(j-0.5, i + 1, 0, 0);
			//System.out.println(temp);
			if (temp - r*r >0) {
				--j;
			}
			++i;
		}
		return res;
	}
	public static ArrayList<int[]>draw6() {
		ArrayList<int[]> res = new ArrayList<int[]>();
		int i = 0;
		int j = r;
		while (i < j) {
			//System.out.println(i + " " + j);
			eightWay(res, i, j);
			double temp = squareDiff2(j-1, i + 1, 0, 0);
			double temp2 = squareDiff2(j, i + 1, 0, 0);
			if (temp + temp2 - 2 * r * r > 0) {
				--j;
			}
			++i;
		}
		return res;
	} 
	public static ArrayList<int[]>draw7() {
		ArrayList<int[]> res = new ArrayList<int[]>();
		int i = 0;
		int j = r;
		int d = 3-2*r;
		while (i < j) {
			eightWay(res, i, j);
			//System.out.println(i + " " + j);
			if (d > 0) {
				d = d + 4*(i-j) +10;
				--j;
			}
			else {
				d = d + 4*i + 6;
			}
			++i;
		}
		return res;
	}
	
	public static void printRes(char [][] board) {
		for (int i = 0; i < board.length; ++i) {
			for (int j = 0; j < board[0].length; ++j) {
				System.out.print(board[i][j] + " ");
			}
			System.out.println();
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ArrayList<int[]> recei1 = draw1();
		char[][] board = new char[41][41];
		for (int i = 0; i < recei1.size(); ++i) {
			board[recei1.get(i)[0] + r][recei1.get(i)[1] + r] = '*';
		}
		printRes(board);
		System.out.println();
		board = new char[41][41];
		ArrayList<int[]> recei2 = draw2();
		for (int i = 0; i < recei2.size(); ++i) {
			board[recei2.get(i)[0] + r][recei2.get(i)[1] + r] = '*';
		}
		printRes(board);
		System.out.println();
		board = new char[41][41];
		ArrayList<int[]> recei3 = draw3();
		for (int i = 0; i < recei3.size(); ++i) {
			board[recei3.get(i)[0] + r][recei3.get(i)[1] + r] = '*';
		}
		printRes(board);
		System.out.println();
		board = new char[41][41];
		ArrayList<int[]> recei4 = draw4();
		for (int i = 0; i < recei4.size(); ++i) {
			board[recei4.get(i)[0] + r][recei4.get(i)[1] + r] = '*';
		}
		printRes(board);
		System.out.println();
		board = new char[41][41];
		ArrayList<int[]> recei5 = draw5();
		for (int i = 0; i < recei5.size(); ++i) {
			board[recei5.get(i)[0] + r][recei5.get(i)[1] + r] = '*';
		}
		printRes(board);
		System.out.println();
		board = new char[41][41];
		ArrayList<int[]> recei6 = draw6();
		for (int i = 0; i < recei6.size(); ++i) {
			board[recei6.get(i)[0] + r][recei6.get(i)[1] + r] = '*';
		}
		printRes(board);
		System.out.println();
		board = new char[41][41];
		ArrayList<int[]> recei7 = draw7();
		for (int i = 0; i < recei7.size(); ++i) {
			board[recei7.get(i)[0] + r][recei7.get(i)[1] + r] = '*';
		}
		printRes(board);
	}
}
