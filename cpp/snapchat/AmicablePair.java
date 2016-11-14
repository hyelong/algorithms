/*
找Amicable Number Pairs
就是 数A 的所有因数(包括1，不包括A) 之和 等于 B。B的所有因数之和又刚好为A。 且 A != B.
求[1, N] 中所有符合条件的pair
*/
import java.util.*;

class Pair{
	int first;
	int second;
	public Pair(int first, int second){
		this.first = first;
		this.second = second;
	}
}

public class AmicablePair{
	public List<Pair> getAmicablePair(int n){
		List<Pair> result = new ArrayList<>();
		int[] record = new int[n+1];
		for (int i = 0; i <= n; i++) {
			record[i] += 1;
		}
		//这个循环关键，决定复杂度啊，用j来指代位置。
		for (int i = 2; i <= n/2; i++) {
			for (int j = 2*i; j <= n; j += i) {
				record[j] += i;
			}
		}
		for (int i = 1; i <= n; i++) {
			// 这里注意record[i]很有可能会越界。
			if (i < record[i] && record[i] <= n && record[record[i]] == i) {
				result.add(new Pair(i, record[i]));
			}
		}
		return result;
	}
	public static void main(String[] args) {
		AmicablePair test = new AmicablePair();
    	int n = 10500;
	    for (Pair pair : test.getAmicablePair(n)) {
	        System.out.println("Pair = " + pair.first + " ---- " + pair.second);
	    }
	}
}