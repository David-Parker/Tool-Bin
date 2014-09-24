import java.util.ArrayList;

public class CompileError {
	private static boolean forceContinue;
	private static ArrayList<String> errors;
	public static final int CONTROL_ERROR_1 = 0;
	public static final int CONTROL_ERROR_2 = 1;
	
	public CompileError() {
		forceContinue = false;
		errors = new ArrayList<String>();
	}
	
	public void checkError(String type, int arg1, int arg2) {
		if(type.equals("Instrument")) {
			Instrument inst = Instrument.getInstance();
			if(inst.prefix == null) message("Instrument Prefix has not been set.");
			if(inst.identifier == null) message("Instrument Identifier has not been set.");
			if(inst.technology == null) message("Instrument Technology has not been set.");
			if(inst.manufacturer == null) message("Instrument Manufacturer has not been set.");
		}
		else if(type.equals("Delim")) {
			if(arg1 > 0) message("Missing closing brace for line " + arg2 + ".");
			else if (arg1 < 0) message("Extra brace found.");
		}
		else if(type.equals("Control")) {
			if(arg2 == CONTROL_ERROR_1)
				message("Control found without a Vi at line " + arg1 + ".");
			else if (arg2 == CONTROL_ERROR_2)
				message("Invalid control name at line " + arg1 + ".");
		}
	}
	
	public void checkError(String type, int arg1, String str) {
		if(type.equals("Instrument")) {

		}
		else if(type.equals("Delim")) {

		}
		else if(type.equals("Control")) {
			if(str.equals(""))
				message("Invalid control name at line " + arg1 + ".");
		}
	}
	
	public static void message(String str) {
		errors.add("[Compile Error]: " + str);
	}
	
	public void force() {
		forceContinue = true;
	}
	
	public void printErrors() {
		if(errors.size() > 0) {
			for(String s: errors) {
				System.out.println(s);
			}
			if(!forceContinue) {
				System.out.println("[Compile Error]: " + errors.size() + " errors found. Compile failed, exiting program.");
				System.exit(-1);
			}
		}	
	}

}
