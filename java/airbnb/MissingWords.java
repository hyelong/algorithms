import java.util.*;

public class MissingWords{
    private static List<String> missingWords(String s, String t){
        List<String> res = new ArrayList<>();
        List<String> s_words = split(s);
        List<String> t_words = split(t);
        int i = 0, j = 0;
        while(i < s_words.size() && j < t_words.size()){
            if(s_words.get(i).equals(t_words.get(j))){
                i++;
                j++;
            } else {
                res.add(s_words.get(i));
                i++;
            }
        }
        while(i < s_words.size()) res.add(s_words.get(i++));
        return res;
    }

    private static List<String> split(String s){
        List<String> res = new ArrayList<>();
        StringBuilder sb = new StringBuilder();
        for(char c : s.toCharArray()){
            if(c == ' ') {
                if(sb.length() != 0) res.add(sb.toString());
                sb.setLength(0);
            }
            else sb.append(c);
        }
        if(sb.length() != 0) res.add(sb.toString());
        return res;
    }

    public static void main(String[] args){
        String s = "I like cheese";
        String t = "like";
        List<String> res = missingWords(s, t);
        System.out.println(res);
    }
}