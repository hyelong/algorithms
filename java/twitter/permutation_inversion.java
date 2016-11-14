import java.util.*;

public class permutation_inversion{
    public static void main(String[] args){
        permutation_inversion p = new permutation_inversion();
        List<String> res= p.permu_inversion(5,5);
        for(String s : res) System.out.println(s);
    }

    List<String> permu_inversion(int n, int k){
        List<List<String>> list = new ArrayList<>();
        List<String> temp = new ArrayList<>();
        temp.add("1");
        list.add(temp);
        for(int i=2;i<=n;i++){
            List<List<String>> next = new ArrayList<>();
            int index = 0;
            while(index<=k) {next.add(new ArrayList<String>());index++;}
            for(int j = 0;j<list.size();j++){
                int length = list.get(0).get(0).length();
                for(String s : list.get(j)){
                    for(int m =length; m>=0;m--){
                        String temp_s = s.substring(0,m)+i;
                        if(m<length) temp_s += s.substring(m);
                        if(j+length-m<=k)
                            next.get(j+length-m).add(temp_s);
                    }
                }
            }
            list = next;
        }
        return list.get(k);
    }
}
