
public class Main {

	public static void main(String[] args) {
		System.out.println("Hello, World!");
		MyQueue<Integer> myq = new MyQueue<Integer>();
		
		for(int i = 0; i < 10; i++)
			myq.push(i);
		
		myq.pop();
		
		System.out.println(myq.toString());

	}

}
