import java.util.ArrayList;

public class Vi {
	private String name;
	private String source;
	public ArrayList<Control> controls;
	public static String[] templateVis = {"Self-Test","Self Test","Revision Query","Reset","Error Query","VI Tree","Close","Initialize"};
	public static final int NUM_TEMPLATE_VIS = 8;
	
	public Vi(String name) {
		this.name = name;
		controls = new ArrayList<Control>();
		source = new String();
	}
	
	public String getName() {
		return name;
	}
	
	public String getSource() {
		return source;
	}
	
	public void setSource(String type) {
		source = type;
	}
}
