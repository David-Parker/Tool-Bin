
public class CompileError {
	private static boolean forceContinue;
	public CompileError() {
		forceContinue = false;
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
			if(arg1 > 0) message("Mis matched brackets at line " + arg2);
			else if (arg1 < 0) message("Extra bracket found.");
		}
	}
	
	public static void message(String str) {
		System.out.println("Compile Error: " + str);
		if(!forceContinue) System.exit(-1);
	}
	
	public void force() {
		forceContinue = true;
	}
}
