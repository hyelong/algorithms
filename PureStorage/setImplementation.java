 //If allowed negative value, then we can add each number by the value of smallest element. e.g -3,-2,-1,0,1,2,3 Each number increased by 3
//If allowed 0, we need one flag to indicate whether 0 is present. 
public class setImplementation {
	static int[] bucket = new int[10];
	static int[] sequential = new int[10];
	static int count = 0;
	public static boolean contains(int v) {
		if(bucket[v] < count && sequential[bucket[v]] == v) {
			return true;
		}
		return false;
	}
	public static boolean remove(int v) {
		if(!contains(v)) {
			return false;
		}
		int index = bucket[v];
		if (index != count - 1) {
			int lastindex = count - 1;
			int lastelement = sequential[lastindex];
			sequential[index] = lastelement;
			bucket[lastelement] = index;
		}
		count--;
		return true;
	}
	public static boolean add(int v) {
		if(contains(v)) {
			return false;
		}
		sequential[count] = v;
		bucket[v] = count;
		count++;
		return true;
	}
	public static void clear() {
		count = 0;
	}
	public static void iter() {
		for (int i = 0; i < count; ++i) {
			System.out.println(sequential[i]);
		}
	}
	public static void main(String[] args) {
		add(5);
		add(1);
		add(2);
		add(3);
		remove(5);
		clear();
		add(2);
		remove(2);
		System.out.println(contains(3));
	}
}
