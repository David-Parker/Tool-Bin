import java.util.ArrayList;

public class Main {
	static Node targetNode;

	public static void main(String[] args) {
		Node root = new Node("root");
		
		/* Build an arbitrary Binary Tree */
		fillTree(root);
		findRightMostNeighbor(root);
		String neighbor = targetNode.rightmost != null ? targetNode.rightmost.name : "NULL";
		System.out.println("Target Node " + targetNode.name + " has the right most neighbor: " + neighbor);
	}
	
	public static void findRightMostNeighbor(Node root) {
		ArrayList<Node> temp = new ArrayList<Node>();
		ArrayList<Node> queue = new ArrayList<Node>();
		
		root.level = 0;
		temp.add(root);
		Node curr;
		int index = 0;
		
		/* Breadth first traversal */
		while(!temp.isEmpty()) {
			curr = temp.remove(0);
			queue.add(curr);
			
			if(curr.left != null) {
				curr.left.level = curr.level + 1;
				curr.left.index = index++;
				temp.add(curr.left);
			}
			
			if(curr.right != null) {
				curr.right.level = curr.level + 1;
				curr.right.index = index++;
				temp.add(curr.right);
			}
		}
		
		for(Node n : queue) {
			if(n.index > targetNode.index && n.level == targetNode.level) {
				targetNode.rightmost = n;
			}
		}
	}
	
	public static void fillTree(Node root) {
		Node one = new Node("1");
		Node two = new Node("2");
		root.left = one;
		root.right = two;
		
		Node three = new Node("3");
		Node four = new Node("4");
		one.left = three;
		one.right = four;
		
		Node five = new Node("5");
		Node six = new Node("6");
		two.left = five;
		two.right = six;
		
		/* Assign the target node */
		targetNode = three;
	}

}

class Node {
	public String name;
	public int level;
	public int index = 0;
	public Node left;
	public Node right;
	public Node rightmost;
	
	public Node(String name) {
		this.name = name;
	}
}
