package FB;

import java.util.*;

/*
Find all words [A-Z] in a dictionary (about 1M words) that are made of a subset (in any order) 
of the chars in the input parameter [A-Z].
ex: input "ACRAT" (10 to 20 chars, up to 30 worst case)
matching words: "A", "CAR", "ACA", "ART", "RAC"
non-matching words: "BAR", "AAA"

一上来就做题，function会被call multiple times, 问怎么优化。回答用trie，然后没想起来怎么做，在他提示下才想到思路，感觉答得不好。
*/

public class FBTrieSearch {

	public static void main(String[] args){
		FBTrieSearch fb = new FBTrieSearch("ACRAT");
		String[] dict = {"A", "CAR", "ACA", "ART", "RAC","BAR", "AAA"};
		for(String s : dict){
			fb.insert(s);
		}
		List<String> res = new ArrayList<>();
		StringBuilder word = new StringBuilder();
		fb.findWords(fb.root, word, res, fb.map);
		for(String s : res){
			System.out.println(s);
		}
	}

	public class Trie{
		Trie[] nodes = new Trie[26];
		boolean isWord = false;
	}
	
	Trie root;
	Map<Character, Integer> map = new HashMap<>();
	public FBTrieSearch(String input){
		root = new Trie();
		pre_process(map, input);
	}
	
	private void pre_process(Map<Character, Integer> map, String input){
		for(char c:input.toCharArray()){
			if(!map.containsKey(c)) map.put(c, 0);
			map.put(c, 1+map.get(c));
		}
	}

	public void insert(String word){
		Trie cur = root;
		int i = 0;
		while(i<word.length()){
			int index = word.charAt(i)-'A';
			if(cur.nodes[index]==null) cur.nodes[index] = new Trie();
			cur = cur.nodes[index];
			i++;
		}
		cur.isWord = true;
	}
	
	public void findWords(Trie root, StringBuilder word, List<String> res, Map<Character, Integer> map){
		if(root.isWord){
			res.add(word.toString());
			// do not return!!!! otherwise will lose some result
		}
		for(int i=0;i<root.nodes.length;i++){
			if(root.nodes[i]!=null){
				char c= (char)('A'+i);
				if(!map.containsKey(c) || map.get(c)==0) continue;
				map.put(c, map.get(c)-1);
				int length = word.length();
				word.append(c);
				findWords(root.nodes[i], word, res, map);
				word.setLength(length);
				map.put(c, map.get(c)+1);
			}
		}
	}
	
	
	
}
