import java.util.*;

public class display_names{
    public static void main(String[] args){
        display_names display = new display_names();
        System.out.println(display.displayNames(new String[]{"Alice","James","Bob",""}));
        System.out.println(display.displayNames(new String[]{"Alice","James"}));
        System.out.println(display.displayNames(new String[]{"Alice"}));
        System.out.println(display.displayNamesLimit(new String[]{"Alice","James","Bob"},2));
    }

    private String displayNames(String[] names){
        if(names==null) return "";
        int n = names.length;
        //validate strings first, remove empty string "" from names
        List<String> valid = new ArrayList<>();
        for(int i=0;i<names.length;i++){
            if(names[i].equals("")==false) valid.add(names[i]);
        }
        names = new String[valid.size()];
        valid.toArray(names);
        n = names.length;
        if(n==0) return "";
        if(n==1) return names[0];
        if(n==2) return names[0] + " and " + names[1];
        StringBuilder sb = new StringBuilder();
        for(int i=0;i<n-1;i++){
            sb.append(names[i]);
            if(i!=n-2) sb.append(',');
            sb.append(' ');
        }
        sb.append("and "+names[n-1]);
        return sb.toString();
    }

    //assume limit>=2
    private String displayNamesLimit(String[] names, int limit){
        if(names==null) return "";
        int n = names.length;
        if(n==0) return "";
        if(n==1) return names[0];
        if(n==2) return names[0] + " and " + names[1];
        StringBuilder sb = new StringBuilder();
        for(int i=0;i<limit;i++){
            sb.append(names[i]);
            if(i!=limit-1) sb.append(',');
            sb.append(' ');
        }
        sb.append("and ").append(n-limit).append(" more");
        return sb.toString();
    }
}
