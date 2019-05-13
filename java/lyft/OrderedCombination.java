/**
N个string合并成一个，要保留原来string里面字符的顺序。求所有可能组合
merge(['AB', 'C']) => ['ABC', 'ACB', 'CAB']
merge(['AB', 'CD']) => ['ABCD', 'ACBD', 'ACDB', 'CABD', 'CADB', 'CDAB']

merge(['AB', 'CD', 'E']) => ['ABCDE', 'ABCED', 'ABECD', 'ACBDE', 'ACBED', 'ACDBE', 'ACDEB', 
'ACEBD', 'ACEDB', 'AEBCD', 'AECBD', 'AECDB', 'CABDE', 'CABED', 'CADBE', 'CADEB', 'CAEBD', 'CAEDB', 
'CDABE', 'CDAEB', 'CDEAB', 'CEABD', 'CEADB', 'CEDAB', 'EABCD', 'EACBD', 'EACDB', 'ECABD', 'ECADB', 
'ECDAB']
*/
import java.util.*;

public class OrderedCombination {
    
     
    public static List<String> mergeStrings(List<String> strList){
        int len = 0;
        for(String str: strList) len += str.length();
        int[] strIdx = new int[strList.size()];
        List<String> result = new ArrayList<>();
        backtracking(len, strList, strIdx, "", result);
        return result;
    }
 
    public static void backtracking(int len, List<String> strList, int[] strIdx, 
                                    String path, List<String> result) {
        if(len == 0){
            result.add(path);
            return;
        }
 
        for(int i = 0; i < strIdx.length; i++){
            if(strIdx[i] < strList.get(i).length()){
                char c = strList.get(i).charAt(strIdx[i]);
                strIdx[i]++;
                backtracking(len-1, strList, strIdx, path + c, result);
                strIdx[i]--;
            }
        }
    }

    public static void main(String[] args) {
        List<String> input = Arrays.asList("AB", "CD", "E");
        List<String> res = mergeStrings(input);
        System.out.println("size:" + res.size());
        for (String s : res) System.out.println(s);
    }
}