/**
 * Question: You are designing a New User sign-up form for a website. When a user enters text in the password field, you want to suggest possible 'stronger' passwords to the user by swapping in special characters, like turning an "a" into an "@". Given a password represented as a string and a character map that contains common characters and substitutions, create a list of all possible password combinations that can be created. 
 *
 */
import java.util.*;

public class password_suggestion{
    List<String> getPassword(String password, Map<Character, Character> map){
        List<String> res = new ArrayList<>();
        int n = password.length();
        for(int i=0;i<n;i++){
            char c = password.charAt(i);
            if(map.containsKey(c)){
                char newChar = map.get(c);
                int len = res.size();
                for(int j=0;j<len;j++){
                    String pass = res.get(j);
                    res.add(pass.substring(0, i) + String.valueOf(newChar) + pass.substring(i));
                }
                    res.add(password.substring(0, i) + String.valueOf(newChar) + password.substring(i));
                }
            }
           return res;
        }

    public static void main(String[] args){
        Map<Character, Character> map = new HashMap<>();
        map.put('i','!');
        map.put('a','@');
        map.put('s','$');
        map.put('o','0');
        map.put('E','3');
        List<String> res = new password_suggestion().getPassword("password", map);    
        for(String s : res) System.out.println(s);
    }
}
