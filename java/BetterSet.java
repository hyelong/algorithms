public class BetterSet{
    public static void main(String[] args){
        BetterSet bs = new BetterSet();
        bs.add(5);
        bs.add(4);
        System.out.println(bs.contains(1));
        System.out.println(bs.contains(4));
        System.out.println(bs.contains(5));
        bs.add(5);
        bs.remove(5);
                
        bs.iterate();
        bs.clear();
        bs.iterate();
    }

    public void add(int x){
        if(contains(x)) return;
        bucket[x] = count;
        seq_array[count] = x;
        count++;
    }

    public void remove(int x){
        if(contains(x)){
            int index = bucket[x];
            seq_array[index] = seq_array[count-1];
            count--;
        }
    }

    public void clear(){
        count = 0;
    }

    public boolean contains(int x){
        if(bucket[x]>=count) return false;
        if(seq_array[bucket[x]]!=x) return false;
        return true;
    }

    public void iterate(){
        for(int i=0;i<count;i++)
            System.out.print(seq_array[i]+" ");
        System.out.println();
    }

    int[] bucket = new int[20];
    int[] seq_array = new int[20];
    int count = 0;
}
