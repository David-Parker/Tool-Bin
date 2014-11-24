import java.util.ArrayList;


public class MyQueue<E> {
	private ArrayList<E> data;
	
	public MyQueue() {
		data = new ArrayList<E>();
	}
	
	public String toString() {
		String str = new String("[");
		for(E dat: data) {
			str += (dat + ",");
		}
		return str + "]";
	}
	
	public void push(E entry) {
		data.add(entry);
	}
	
	public E pop() {
		if(data.size() > 0)
			return data.remove(data.size() - 1);
		else 
			return null;
	}

}
