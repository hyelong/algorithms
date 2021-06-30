/* Then a coding question: When you buy something in grocery, the cashier needs to pay the change. Given the cashier has a register to keep all existing demonimations, write a method simulating how the cashier finds all the denominations to pay the change. For example you paid $5 for something worth $2.35, the cashier needs to find 2 $1, 6 dimes and 5 one cents if there are enough of these. You only need to find one solution and it's possible there is no solution. It's an interesting problem. Once it's paied, the register needs to be updated. There were lots of discussions. I did very well in this round.
*/

import java.util.*;


public class PayChange {
    Map<Integer, Integer> register = new HashMap<>();
    public static void main(String[] args) {
        PayChange payChange = new PayChange();
        payChange.register.put(1, 10);
        payChange.register.put(2, 10);
        payChange.register.put(5, 10);
        payChange.makeChange(payChange.register, 11);
    }

    Map<Integer, Integer> makeChange(Map<Integer, Integer> register, int amount) {
        Map<Integer, Integer> paid = new HashMap<>();
        backtrack(register, amount, paid);
        return paid;
    }

    boolean backtrack(Map<Integer, Integer> register, int amount, Map<Integer, Integer> paid) {
        if (amount < 0) return false;
        if (amount == 0) {
            for (int coin : paid.keySet()) {
                if (paid.get(coin) == 0) continue;
                System.out.println(coin + ":" + paid.get(coin));
                register.put(coin, register.get(coin) - paid.get(coin));
            }
            return true;
        }
        for (int coin : register.keySet()) {
            if (amount < coin) continue;
            if (register.get(coin) == 0) continue;
            register.put(coin, register.get(coin) - 1);
            paid.put(coin, paid.getOrDefault(coin, 0) + 1);
            if(backtrack(register, amount - coin, paid)) return true;
            paid.put(coin, paid.getOrDefault(coin, 0) - 1);
            register.put(coin, register.get(coin) + 1);
        }
        return false;
    }
}
