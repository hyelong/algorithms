import java.util.HashMap;
import java.util.Map;


class TrieNode {
    TrieNode[] children;
    boolean isWord;
    int numOfWords;
    
    public TrieNode() {
            this.children = new TrieNode[26];
    }
}

public class Abbreviation {
	public static void main(String[] args) {
		//String[] strs = {"aaaaa", "abaa", "aaaca", "god", "geed"};
        String[] strs = { "like","god","internal", "me","internet","interval","intension","face","iiiiiiiiiiiiintrusion"};
		Abbreviation so = new Abbreviation();
		String[] result = so.Encode(strs);
		for (String s : result) {
			System.out.println(s);
		}
	}
    public void insert(String s,TrieNode root) {   
        TrieNode node = root;
        for (int i=0;i<s.length();i++) { 
            char c = s.charAt(i);
            if (node.children[c-'a'] == null) {
                node.children[c-'a'] = new TrieNode();
            }
            node = node.children[c-'a'];
            node.numOfWords++;
        }
    }

    public String searchPrefix(String s, TrieNode root) {
            
            TrieNode node = root;
            String prefix = "";
            
            for (int i=0;i<s.length();i++) {
                    char c = s.charAt(i);
                    if (node.children[c-'a']!=null) {
                       node = node.children[c-'a'];
                    }
                    prefix+= c;
                    
                    if (node.numOfWords == 1) return prefix;
            }
            
            return prefix;
    }
    
    /* assume no duplicate in string array.*/
public String[] Encode(String[] strs) {
        
        Map<Integer,TrieNode> wordDict = new HashMap<Integer,TrieNode>();
        String[] encodeStrs = new String[strs.length];
        
        // Build trie.
        for (int i=0;i<strs.length;i++) {
                int len = strs[i].length();
                if (!wordDict.containsKey(len)) {
                        TrieNode root = new TrieNode();
                        wordDict.put(len, root);
                } 
                
                insert(strs[i],wordDict.get(len));
        }
        // compress each string.
        for (int i=0;i<strs.length;i++) {
                
                int len = strs[i].length();
                if(len<=3){
                    encodeStrs[i] = strs[i];
                    continue;
                }
                String prefix = searchPrefix(strs[i],wordDict.get(len));
                String encoded = prefix + (len-1-prefix.length()) + strs[i].charAt(len-1);

                if (encoded.length()  < len) 
                    encodeStrs[i] = encoded;
                else 
                    encodeStrs[i] = strs[i];
        }
        
        return encodeStrs;
        
	}
}