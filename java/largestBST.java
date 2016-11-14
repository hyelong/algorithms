import java.util.*;
public class largestBST{
    public static void main(String[] args){
        largestBST l = new largestBST();
        TreeNode root = new TreeNode(5);
        root.left = new TreeNode(3);
        root.right = new TreeNode(1);
        root.left.left = new TreeNode(2);
        root.left.right = new TreeNode(4);
        l.findLargest(root, Integer.MIN_VALUE, Integer.MAX_VALUE);
        System.out.println(l.largest);
    }

    int largest = 0;
    int findLargest(TreeNode root, int mn, int mx){
        if(root==null) return 0;
        int res = 0;
        int left = findLargest(root.left, mn, root.val);
        if(root.val<=mn || root.val>=mx) return -1;
        int right = findLargest(root.right, root.val, mx);

        if(left!=-1 && right!=-1){
            res = 1+left+right;
        }
        else res = Math.max(left, right);
        largest = Math.max(largest,res);
        return res;
    }


}

class TreeNode{
    TreeNode left;
    TreeNode right;
    int val;
    public TreeNode(int val){
        this.val = val;
    }
}
