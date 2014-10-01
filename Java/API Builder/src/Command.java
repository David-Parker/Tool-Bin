
public class Command {
	private String name;
	private int numControls;
	public int controlsFound;
	public static Command currCommand;
	public int row;
	
	public Command(String name, int row) {
		/* Check if the user specified a multi-control command */
		controlsFound = 1;
		this.name = name;
		this.row = row;
		numControls = findNumControls();
	}
	
	public String getName() {
		return name;
	}
	
	public int findNumControls() {
		/* TODO Temp function */
		
		if(name.equals("")) return 1;
		
		int spaceCount = 0;
		for (char c : name.trim().toCharArray()) {
		    if (c == ' ') {
		         spaceCount++;
		    }
		}
		return spaceCount;
	}
	
	public void checkNumControlsBelow(int row) {
		//System.out.println(controlsFound + " " + numControls );
		if(controlsFound > numControls) {
			//System.out.println("Below");
			CompileError ce = new CompileError();
			ce.checkError("Command", row, CompileError.ERROR_2);
		}
	}
	
	public void checkNumControlsAbove(int row) {
		//System.out.println(controlsFound + " " + numControls );
		if(controlsFound < numControls) {
			//System.out.println("Above");
			CompileError ce = new CompileError();
			ce.checkError("Command", row, CompileError.ERROR_3);
		}
	}
}
