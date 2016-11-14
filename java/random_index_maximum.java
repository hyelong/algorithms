import java.util.*;

public class random_index_maximum{
    public static void main(String[] args){
        random_index_maximum random_index = new random_index_maximum();
        int[] arr = {1,2,9,9,2,4,8,9,5,9};
        int count = 0;
        for(int i=0;i<10000;i++){
            int index = random_index.findMax(arr);
            if(index==2) count++;
        }
        System.out.println(count);
    }

    public int findMax(int[] arr){
        if(arr.length==0) throw new IllegalArgumentException();
        int max = arr[0], counter=0, result=0;
        Random random = new Random();
        for(int i=0;i<arr.length;i++){
            if(arr[i]>max){
                max = arr[i];
                counter=1;
                result = i;
            }
            else if(max == arr[i]){
                counter++;
                if(random.nextInt(counter)==0) result = i;
            }
        }
        return result;
    }
}
