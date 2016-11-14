import java.util.*;

public class tree_serialize_deserialize{
    public static void main(String[] args){
        TreeNode root = new TreeNode(1);
        root.children.add(new TreeNode(2));
        root.children.add(new TreeNode(3));
        root.children.add(new TreeNode(4));
        root.children.get(0).children.add(new TreeNode(5));
        tree_serialize_deserialize tree = new tree_serialize_deserialize();
        String res = tree.serialize(root);
        System.out.println(res);
        TreeNode root2 = tree.deserialize(res);
        tree.print(root2);
    }

    void print(TreeNode root){
        if(root==null) return;
        System.out.println(root.val);
        for(TreeNode node : root.children) print(node);
    }

    String serialize(TreeNode root){
        if(root==null) return "";
        StringBuilder sb = new StringBuilder();;
        sb.append(root.val).append(' ');
        for(TreeNode node : root.children)
            sb.append(serialize(node));
        sb.append(')');
        return sb.toString();
    }

    TreeNode deserialize(String s){
        if(s==null || s.length()==0) return null;
        Stack<TreeNode> st = new Stack<>();
        String val="";
        int value=0;
        for(int i=0;i<s.length();i++){
            char c = s.charAt(i);
            if(Character.isDigit(c)){
                val += (c-'0');
            }
            else if(c == ' '){
                value = Integer.parseInt(val);
                TreeNode node = new TreeNode(value);
                st.push(node);
                val = "";
            }
            else{
                if(st.size()>=2){
                    TreeNode cur = st.pop();
                    st.peek().children.add(cur);
                }
            }
        }
        return st.pop();
    }
}

class TreeNode{
    int val;
    List<TreeNode> children = new ArrayList<>();
    public TreeNode(int val){
        this.val = val;
    }
}
