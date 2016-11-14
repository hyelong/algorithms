import java.util.*;

public class Huffman {
	class TreeNode {
        TreeNode left;
        TreeNode right;
        char val;
        double fre;

        public TreeNode(char val, double fre) {
                this.val = val;
                this.fre = fre;
        }
	} 
	
	
	TreeNode buildTree(TreeNode[] input){
		Queue<TreeNode> q = new PriorityQueue<>(new Comparator<TreeNode>(){
			public int compare(TreeNode n1, TreeNode n2){
				if(n1.fre>n2.fre) return 1;
				if(n1.fre<n2.fre) return -1;
				return 0;
			}
		});
		for(TreeNode node:input){
			q.add(node);
		}
		while(q.size()>1){
			TreeNode n1 = q.poll();
			TreeNode n2 = q.poll();
			TreeNode parent = new TreeNode('\0', n1.fre+n2.fre);
			parent.left = n1;
			parent.right = n2;
			q.add(parent);
		}
		return q.poll();
	}
	
	Map<Character, String> buildCode(TreeNode root, boolean isleft, StringBuilder code){
		Map<Character, String> map = new HashMap<>();
		buildHelper(root, true,code,map);
		return map;
	}
	
	void buildHelper(TreeNode root, boolean isleft, StringBuilder code, Map<Character, String> res){
		if(root==null) return ;
		
		int length = code.length();
		if(isleft) code.append("0");
		else code.append("1");
		buildHelper(root.left, true, code, res);
		buildHelper(root.right, false, code, res);
		
		if(root.left==null && root.right==null){
			res.put(root.val, new String(code).substring(1));
		}
		code.setLength(length);
	}
	
	public static void test(){
		Huffman huffman = new Huffman();
		TreeNode[] input={huffman.new TreeNode('a', 0.32),
				huffman.new TreeNode('b', 0.25),
				huffman.new TreeNode('c', 0.2),
				huffman.new TreeNode('d', 0.18),
				huffman.new TreeNode('e', 0.05)};
		TreeNode root = huffman.buildTree(input);
		Map<Character, String> res = huffman.buildCode(root,false, new StringBuilder());
		for(Character key : res.keySet()){
			System.out.println(key + ":" + res.get(key));
		}
	}
	
}
