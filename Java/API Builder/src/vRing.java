
public class vRing extends Control {
	private String ringValue;
	
	public vRing(String type, String name, String dataType, Command command, int row, String ringValue) {
		super(type,name,"I32",command,row);
		this.ringValue = ringValue;
		/* TODO Add */
		polCmd = "";
	}

	public void writeTag() {
	 /* TODO */
		
	}
	
	public String formatter() {
		return " %d";
	}
}
