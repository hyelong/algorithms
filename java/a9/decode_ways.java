/*
 * Decode ways
 */

public class decode_ways{
    private int decodeWays(String s){
      if(s==null || s.equals("")) return 0;
      if(s.length()==1) return s.charAt(0)=='0'?0:1;
      int last2 = 1, last1 = s.charAt(0)=='0'?0:1;
      for(int len = 2; len <= s.length(); len++){
        int cur = 0;
        if(s.charAt(len-1)!='0') cur += last1;
        if(s.charAt(len-2)=='1' || s.charAt(len-2)=='2' && s.charAt(len-1)<'7') cur += last2;
        last2 = last1;
        last1 = cur;
        if(cur == 0) return 0;
      }
      return last1;
    }
    public static void main(String[] args){
      decode_ways decode = new decode_ways();
      System.out.println(decode.decodeWays("12"));
      System.out.println(decode.decodeWays("1001"));
    }
}
