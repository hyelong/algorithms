import java.util.*;

public class AutoCompletion {
    public static void main(String[] args) {
        AutoCompletion autoCompletion = new AutoCompletion();
        String[] words = new String[]{"apple", "applepie", "applejuice", "banana"};
        Trie root = autoCompletion.buildTrie(words);
        List<String> res = autoCompletion.findWordsByPrefix("ban", root);
        for (String word : res) {
            System.out.println(word);
        }
    }

    Trie buildTrie(String[] words) {
        Trie root = new Trie();
        Trie current = null;
        for (String word : words) {
            current = root;
            for (char c : word.toCharArray()) {
                if (current.children[c - 'a'] == null) {
                    current.children[c - 'a'] = new Trie();
                }
                current = current.children[c - 'a'];
            }
            current.word = word;
        }
        return root;
    }

    List<String> findWordsByPrefix(String prefix, Trie root) {
        List<String> res = new ArrayList<>();
        Trie current = root;
        for (char c : prefix.toCharArray()) {
            if (current.children[c - 'a'] == null) return res;
            current = current.children[c - 'a'];
        }
        dfs(current, res);
        return res;
    }

    void dfs(Trie root, List<String> res) {
        if (root == null) return;
        if (root.word != null) res.add(root.word);
        for (Trie node : root.children) {
            dfs(node, res);
        }
    }
}

class Trie {
    Trie[] children = new Trie[26];
    String word = null;
}
