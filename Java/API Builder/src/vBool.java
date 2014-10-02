
public class vBool extends Control{
	
	public vBool(String type, String name, String dataType, Command command, int row) {
		super(type, name, "Bool", command, row);
		polCmd = " {ON|OFF}";
	}

	public void writeTag() {
		/* TODO */
	}

	public String formatter() {
		return " %s";
	}
}
