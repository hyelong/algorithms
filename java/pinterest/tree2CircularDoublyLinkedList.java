import java.util.*;

public class tree2CircularDoublyLinkedList{
    public static void main(String[] args){
        tree2CircularDoublyLinkedList tree = new tree2CircularDoublyLinkedList();
        TreeNode root = new TreeNode(1);
        root.left = new TreeNode(2);
        root.right = new TreeNode(3);
        root.left.left = new TreeNode(4);
        tree.tree2list(root);

        tree.print(tree.head);
    }

    void print(TreeNode head){
        TreeNode temp = head;
        System.out.println("Path1:");
        while(temp.visited==false){
            temp.visited = true;
            System.out.println(temp.val);
            temp = temp.right;
        }
        System.out.println("Path2:");
        temp = head;
        while(temp.visited)
        {
            temp.visited =false;
            System.out.println(temp.val);
            temp = temp.left;
        }
    }

    void tree2list(TreeNode root){
        if(root==null) return;
        tree2list(root.left);
        if(head==null) head = root;
        else pre.right = root;
        root.left = pre;
        // we don't know which node is the last one,
        // simply assume every node is the last one.
        TreeNode right = root.right;
        root.right = head;
        head.left = root;
        pre = root;
        tree2list(right);
    }

    TreeNode pre, head;
}

class TreeNode{
    TreeNode left;
    TreeNode right;
    boolean visited = false;
    int val;
    public TreeNode(int val){
        this.val = val;
    }
}
