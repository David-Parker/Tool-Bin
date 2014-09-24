import java.util.ArrayList;

public class Vi {
	private String name;
	public ArrayList<Control> controls;
	
	public Vi(String name) {
		this.name = name;
		controls = new ArrayList<Control>();
	}
	
	public String getName() {
		return name;
	}
}
