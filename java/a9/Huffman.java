/*
 * input是一个array，element是{integer: frequency}，求出它们的huffman code
 */
import java.util.*;

class TreeNode{
    public char key;
    public double value;
    public TreeNode left;
    public TreeNode right;
    public TreeNode(char key, double value){
        this.key = key;
        this.value = value;
    }
}

class KeyValue{
    public char key;
    public double value;
    public KeyValue(char key, double value){
        this.key = key;
        this.value = value;
    }
}

public class Huffman{
    TreeNode huffmanTree(KeyValue[] inputs){
        List<TreeNode> nodes = new ArrayList<>();
        for(KeyValue item : inputs){
          nodes.add(new TreeNode(item.key, item.value));
        }
        PriorityQueue<TreeNode> pq = new PriorityQueue<>(
                new Comparator<TreeNode>(){
                  public int compare(TreeNode node1, TreeNode node2){
                      if(node1.value < node2.value) return -1;
                      return 1;
                  }
                }
        );

        for(TreeNode node : nodes){
          pq.add(node);            
        }

        while(pq.size()>1){
            TreeNode node1 = pq.poll();
            TreeNode node2 = pq.poll();
            TreeNode parent = new TreeNode('-', node1.value + node2.value);
            parent.left = node1;
            parent.right = node2;
            pq.add(parent);
        }
        return pq.peek();
    }

    private void print(TreeNode root){
        if(root == null) return ;
        System.out.println(root.key+":"+root.value);
        print(root.left);
        print(root.right);
    }

    private void encode(TreeNode root, String code, String cur){
      if(root == null) return;
      code += cur;
      if(root.key != '-'){
        System.out.println(root.key + ":" + code);
      }
      encode(root.left, code, "0");
      encode(root.right, code, "1");
    }

    public static void main(String[] args){
      KeyValue[] inputs = {new KeyValue('a', 0.4), new KeyValue('b', 0.3), new KeyValue('c', 0.2), new KeyValue('d', 0.1)};
      Huffman huff = new Huffman();
      TreeNode root = huff.huffmanTree(inputs);
      huff.print(root);
      huff.encode(root, "", "");
    }
}
