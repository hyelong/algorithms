/*
 * 1. 给一个空格（一个或多个）分割的string，把它变成一个一个单词。不能用split() function.
 * 2. 统计词频
 * 3. 输出top K
 */
import java.util.*;

public class SplitStrings{
    List<String> splitString(String s){
      List<String> res = new ArrayList<>();
      String word = "";
      boolean word_begin = false;
      for(int i = 0; i<s.length(); i++){
        char c = s.charAt(i);
        if(Character.isLetter(c)){
            word_begin = true;
            word += c;
        }
        else{
            res.add(word);
            word_begin = false;
            word = "";
        }
      }
      if(word!="") res.add(word);
      return res;
    }

    public static void main(String[] args){
      SplitStrings split = new SplitStrings();
      String s = " this  is  a  test";
      List<String> res = split.splitString(s);
      for(String ss : res) System.out.print(ss+" ");
      System.out.println();
    }
}
