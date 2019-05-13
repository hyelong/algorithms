/**
 * 题目是有一个 paginated API 参数是 pageId， 每次返回该pageid的elements，现实fetchN
 * e.g. 3 pages, [ [0,1,2,3,4], [5,6,7,8,9], [10,11,12] ]
 * paginated(0) = [0,1,2,3,4],
 * paginated(1) =  [5,6,7,8,9],

 * fetchN(2) = [0,1]
 * fetchN(2) = [2,3]
 * fetchN(2) = [4,5]
 * fetchN(100) = [6,7,8,9,10,11,12]
 */
import java.util.*;

public class FetchN {
  static int current_index = 0, current_count = 0;
  static int[] page;
  static int page_index = 0;
  static int[][] paginated = new int[][]{{0, 1, 2, 3}, {5, 6, 7, 8}, {10, 11, 12, 13}};
  public static List<Integer> fetchN(int n) {
    int i = 0;
    List<Integer> res = new ArrayList<>();
    while(i < n) {
      if(current_index < current_count) {res.add(page[current_index++]); i++;}
      else {
        current_index = 0;
        if(page_index == paginated.length) break;
        page = paginated[page_index++];
        current_count = page.length;
      }  
    }
    return res;
  }
  public static void main(String[] args) {
    List<Integer> res = fetchN(2);
    for(int i : res)
    System.out.println(i);
    res = fetchN(2);
    for(int i : res) System.out.println(i);
    res = fetchN(2);
    for(int i : res) System.out.println(i);
    res = fetchN(100);
    for(int i : res) System.out.println(i);
  }
}
