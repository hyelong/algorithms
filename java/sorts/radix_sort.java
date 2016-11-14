import java.util.*;

public class radix_sort{
    public static void main(String[] args){
        radix_sort r = new radix_sort();
        int[] arr = new int[]{12345, 12, 2345};
        r.sort(arr);
        for(int num : arr) System.out.print(num + " ");
        System.out.println();
    }

    void sort(int[] arr){
        if(arr == null || arr.length < 2) return;
        int radix = 10;
        List<Integer>[] buckets = new ArrayList[radix];
        for(int i=0;i<radix;i++){
            buckets[i] = new ArrayList<Integer>();
        }

        boolean finished = false;
        int placement = 1;
        while(!finished){
            finished = true;
            for(int i=0;i<arr.length;i++){
                int cur = arr[i]/placement;
                buckets[cur%radix].add(arr[i]);
                if(finished && cur > 0) finished = false;
            }
        
            int index = 0;
            for(int i=0;i<radix;i++){
                if(buckets[i].size()==0) continue;
                for(int num : buckets[i]) arr[index++]=num;
                buckets[i].clear();
            }
            placement *= 10;
        }
    }
}
