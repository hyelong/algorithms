/*
 * - You're given an array of integers
 * - You're asked to construct a binary search tree from this array
 * - Please create your BST class such that it supports two operations:
 *      exists(k) and successor(k) in logarithmic time
 */

class TreeNode{
    public TreeNode left = null;
    public TreeNode right = null;
    public int val;
    public TreeNode(int val){
      this.val = val;
    }
}

public class BSTInorderSuccessor{

  TreeNode construct(int[] nums){
    if(nums == null) return null;
    if(nums.length == 0) return null;
    TreeNode root = new TreeNode(nums[0]);
    for(int i=1;i<nums.length;i++){
        insertNode(root, nums[i]);
    }
    return root;
  }

  void insertNode(TreeNode root, int num){
    if(root == null){
        root = new TreeNode(num);
        return;
    }
    if(root.val < num){
       if(root.right!=null)
          insertNode(root.right, num);
       else root.right = new TreeNode(num);
    }
    else {
        if(root.left != null)
           insertNode(root.left, num);
        else root.left = new TreeNode(num);
    }
  }

  TreeNode inorderSuccessor(TreeNode root, TreeNode p){
    if(p.right!=null) return leftMost(p.right);
    TreeNode suc = null;
    while(root!=null){
        if(p.val < root.val){
          suc = root;
          root = root.left;
        }
        else root = root.right;
    }
    return suc;
  }

  TreeNode leftMost(TreeNode node){
      while(node.left!=null) node = node.left;
      return node;
  }

  private boolean exists(TreeNode root,int k){
    if(root == null) return false;
    if(root.val == k) return true;
    if(root.val < k) return exists(root.right, k);
    else return exists(root.left, k);
  }

  void printTree(TreeNode root){
      if(root == null) return;
      System.out.println(root.val);
      printTree(root.left);
      printTree(root.right);
  }

  public static void main(String[] args){
      BSTInorderSuccessor bst = new BSTInorderSuccessor();
      int[] nums = {4,2,3,1};
      TreeNode root = bst.construct(nums);
      System.out.println(root.left);
      bst.printTree(root);

      root = new TreeNode(3);
      root.left = new TreeNode(2);
      root.right = new TreeNode(4);
      TreeNode p = root.left;
      TreeNode res = bst.inorderSuccessor(root, p);
      System.out.println(res.val);
      System.out.println(bst.exists(root, 5));
  }
}
