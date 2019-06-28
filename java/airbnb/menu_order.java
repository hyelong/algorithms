import java.util.*;
// http://xkcd.com/287/
public class menu_order{
   public static void main(String[] args){
        menu_order m = new menu_order();
        int[] menu = new int[]{215,275,335,420,580,655};
        int bill = 1505;
        List<List<Integer>> res = m.order(menu,0, bill);
        for(List<Integer> list : res){
            System.out.println(list.toString());
        }
   }


   List<List<Integer>> order(int[] menu,int index, int bill){
        List<List<Integer>> res = new ArrayList<>();
        if(bill==0){
            res.add(new ArrayList<Integer>());
            return res;
        }
        for(int i=index;i<menu.length;i++){
            if(bill>=menu[i]){
                List<List<Integer>> temp = order(menu,i, bill-menu[i]);
                for(List<Integer> list : temp){
                    List<Integer> ans = new ArrayList<>(list);
                    ans.add(0,menu[i]);
                    res.add(ans);
                }
            }
        }
        return res;
   }


}
