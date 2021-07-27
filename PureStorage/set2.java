import java.util.HashMap;
import java.util.Map;
//remember using constructor
public class set2 {
	static int[] sequential = new int[10];
	static int count = 0;
	static Map<Integer, Integer> map = new HashMap<Integer, Integer>();
	private static boolean contains(int n) {
		if (map.containsKey(n) && map.get(n) < count) {
			return true;
		}
		return false;
	}
	private static boolean remove(int n) {
		if (!contains(n)) {
			return false;
		}
		int index = map.remove(n);
		if (index != count - 1) {
			int temp = sequential[count - 1];
			sequential[index] = temp;
			map.put(temp, index);
		}
		--count;
		return true;
	}
	private static void add(int n) {
		if (contains(n)) {
			return;
		}
		map.put(n, count);
		sequential[count++] = n;
	}
	private static void clear() {
		count = 0;
	}
	private static void iter() {
		//Iterate array through count
		for (int i = 0; i < count; ++i) {
			System.out.println(sequential[i]);
		}
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		add(5);
		add(1);
		add(2);
		remove(5);
		clear();
		add(1);
		add(5);
		add(3);
		remove(5);
		iter();
		clear();
		iter();
		System.out.println(contains(1));
	}

}
