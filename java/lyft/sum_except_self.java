public class sum_except_self {
  
  static int[] sum(int[] array) {
    int before = 0, after = 0;
    int n = array.length;
    int[] res = new int[n];
    for (int i = 0; i < n; i++) {
      res[i] += before;
      res[n - 1 - i] += after;
      before += array[i];
      after += array[n - 1 - i];
    }
    return res;
  }
        
  public static void main(String[] args) {
    int[] arr = new int[] {1,2,3,4};
    int[] res = sum(arr);
    for (int i : res)
    System.out.println(i);
  }
}
