/* Given a document in the form of a string, find the shortest substring from the document that contains all the words in a input string. For example, the document is "code hello root leet world good sina leet which code" and the input string is "leet code", we should return "leet which code" since it has only three words, shorter than "code hello root leet" which has four words.
*/
import java.util.*;


public class MinWindowWords {
    public static void main(String[] args) {
        MinWindowWords minWindow = new MinWindowWords();
        String res = minWindow.minWindow("code hello root leet world good sina leet which code", "leet code");
        System.out.println(res);
    }

    String minWindow(String doc, String input) {
        Map<String, Integer> toAppear = new HashMap<>();
        String[] inputWords = input.split(" ");
        for (String word : inputWords) {
            int count = toAppear.getOrDefault(word, 0);
            toAppear.put(word, count + 1);
        }
        String[] words = doc.split(" ");
        int left = 0;
        int validWordCount = 0;
        Map<String, Integer> appeared = new HashMap<>();
        int width = words.length + 1;
        int minLeft = 0;
        for (int right = 0; right < words.length; right++) {
            String word = words[right];
            if (toAppear.containsKey(word)) {
                int count = appeared.getOrDefault(words[right], 0);
                appeared.put(word, count + 1);
                if (count + 1 <= toAppear.get(word)) {
                    validWordCount++;
                }
            }

            if (validWordCount == inputWords.length) {
                while (appeared.getOrDefault(words[left], 0) > toAppear.getOrDefault(words[left], 0) || !toAppear.containsKey(words[left])) {
                    if (appeared.containsKey(words[left])) appeared.put(words[left], appeared.get(words[left]) - 1);
                    left++;
                }
                if (width > right - left + 1) {
                    width = right - left + 1;
                    minLeft = left;
                }
            }
        }
        if (width == words.length + 1) return "";
        StringBuilder sb = new StringBuilder();
        for (int i = minLeft; i < minLeft + width; i++) sb.append(words[i]).append(" ");
        return sb.toString().trim();
    }
}
