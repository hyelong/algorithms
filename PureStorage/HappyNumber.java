import java.util.HashSet;
import java.util.Set;

public class HappyNumber {
	//Use hashset to detect cycle
	private static boolean happy(int num) {
		Set<Integer> set = new HashSet<Integer>();
		while (num != 1 && !set.contains(num)) {
			int temp = 0;
			set.add(num);
			while (num > 0) {
				temp += (num % 10) * (num % 10);
				num = num/10;
			}
			num = temp;
		}
		if (num == 1) {
			return true;
		}
		if (set.contains(num)) {
			return false;
		}
		return false;
	}
	private static int getNext(int n) {
		int temp = 0;
		while (n != 0) {
			temp += (n%10)*(n%10);
			n = n/10;
		}
		return temp;
	}
	private static boolean happy2(int n) {
		//Fast always move forward faster than slow pointer, and 1's next is 1, when encounter 1, it will become 11111111.
		int slow = n;
		int fast = getNext(n);
		while (slow != fast && fast != 1) {
			slow = getNext(slow);
			fast = getNext(getNext(fast));
		}
		return fast == 1;
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
