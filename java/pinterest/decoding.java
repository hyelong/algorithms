import java.util.*;
//http://www.1point3acres.com/bbs/thread-174321-1-1.html
public class decoding{
    public static void main(String[] args){
        decoding d = new decoding();
        d.decode(41);
    }

    public Set<String> decode(int num){
        Map<String, String> map = new HashMap<>();
        for(int i=1;i<=26;i++){
            map.put(int2string(i), Character.toString((char)('a'+i-1)));
        }
        Map<String, Set<String>> dp = new HashMap<>();
        Set<String> res = decodeHelper(int2string(num), map, dp);
        for(String s : res) System.out.println(s);
        return res;
    }

    private String int2string(int num){
        StringBuilder sb = new StringBuilder();
        while(num>0){
            int cur = num%10;
            sb.append(cur);
            num = num/10;
        }
        return sb.reverse().toString();
    }

    private Set<String> decodeHelper(String num, Map<String, String> map, Map<String, Set<String>> dp){
        if(dp.containsKey(num)) {
            System.out.println("Already solved: " + num);
            return dp.get(num);
        }
        Set<String> res = new HashSet<>();
        if(num == null||num.length()==0||num.charAt(0)=='0'){
            return res;
        }
        if(num.length()==1){
            res.add(map.get(num));
            return res;
        }
        if(num.length()==2){
            if(num.charAt(1)=='0'){
                if(num.charAt(0)<='2')
                    res.add(map.get(num));
                return res;
            }
            else{
                res.add(map.get(num.substring(0,1))+map.get(num.substring(1,2)));
                if(Integer.parseInt(num)<=26)
                    res.add(map.get(num));
                return res;
            }

        }
        if(num.charAt(1)=='0'){
            if(num.charAt(0)<='2'){
                Set<String> temp = decodeHelper(num.substring(2), map, dp);
                for(String s : temp) res.add(map.get(num.substring(0,2)) + s);
            }
        }
        else{
            Set<String> temp = decodeHelper(num.substring(1), map, dp);
            for(String s : temp) res.add(map.get(num.substring(0,1)) + s);
            if(Integer.parseInt(num.substring(0,2))<=26){
                temp = decodeHelper(num.substring(2), map, dp);
                for(String s : temp) res.add(map.get(num.substring(0,2)) + s);
            }
        }
        dp.put(num, res);
        return res;
    }
}
