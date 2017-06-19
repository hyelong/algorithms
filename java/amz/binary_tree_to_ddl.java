/**
 * Binary tree to doubly linkedlist
 */

import java.util.*;

public class binary_tree_to_ddl{

    Node head = null;

    void bt2dll(Node root){
        if(root == null) return;
        bt2dll(root.right);
        root.right = head;
        if(head != null) head.left = root;
        head = root;
        bt2dll(root.left);
    }

    void printDll(){
        Node pre = null;
        while (head != null) 
        {
             System.out.print(head.val + " ");
             pre = head;
             head = head.right;
        }
        System.out.println();

        while (pre != null){
            System.out.print(pre.val + " ");
            pre = pre.left;
        }
        System.out.println();
    }

    public static void main(String[] args){
        Node root = new Node(1);
        root.left = new Node(2);
        root.right = new Node(3);
        binary_tree_to_ddl bt2ddl = new binary_tree_to_ddl();
        bt2ddl.bt2dll(root);
        bt2ddl.printDll();
    }
}

class Node{
    public int val;
    public Node left;
    public Node right;
    public Node(int val){
        this.val = val;
        left = null;
        right = null;
    }
}
