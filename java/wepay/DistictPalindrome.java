import java.util.*;

public class DistictPalindrome{
    public static void main(String[] args){
        DistictPalindrome d = new DistictPalindrome();
        String s = "abaaa";
        int res = d.distinct_palindrome(s);
        System.out.println(res);
    }

    int distinct_palindrome(String s){
        Set<String> res_set = new HashSet<>();
        int n = s.length();
        for(int i = 0; i < n; i++){
            int start = i, end = i;
            while(start>=0 && end<n && s.charAt(start)==s.charAt(end)){
                res_set.add(s.substring(start, end+1));
                start--;
                end++;
            }

            start = i;
            end = i+1;
            while(start>=0 && end<n && s.charAt(start)==s.charAt(end)){
                res_set.add(s.substring(start, end+1));
                start--;
                end++;
            }
        }
        return res_set.size();
    }
}
