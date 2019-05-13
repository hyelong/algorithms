import java.util.*;

public class IteratorOfIntersection{
    public static void main(String[] args) {
        int[] arr1 = new int[]{1,2,3,4,4,5,5};
        int[] arr2 = new int[]{1,1,2,2,3};
        SortedInterator iterator = new SortedInterator(arr1, arr2);
        while(iterator.hasNext()){
            System.out.println(iterator.next());
        }
    }
    
    static class SortedInterator {
        int[] array1, array2;
        int i1 = 0, i2 = 0;
        public SortedInterator(int[] arr1, int[] arr2) {
            array1 = arr1;
            array2 = arr2;
        }
        
        public boolean hasNext() {
            if (i1 >= array1.length || i2 >= array2.length) {
                return false;
            }
            return true;
        }
        
        public int next() {
            int res = -1;
            while(res == -1 && i1 < array1.length && i2 < array2.length) {
                if (array1[i1] == array2[i2]) {
                    res = array1[i1];
                    while(i1 < array1.length && res == array1[i1]) {
                        i1++;
                    }
                    while(i2 < array2.length && res == array2[i2]) {
                        i2++;
                    }
                    break;
                } else {                
                    if (array1[i1] < array2[i2]) {
                        int temp = array1[i1];
                        while(i1 < array1.length && temp == array1[i1]) {
                            i1++;
                        }
                    } else {
                        int temp = array2[i2];
                        while(i2 < array2.length && temp == array2[i2]) {
                            i2++;
                        }
                    }
                }
            }
            return res;
        }
    }
}
