import java.util.ArrayList;
import java.util.StringTokenizer;

public class SheetParser {
	public static final char leftDelim = '{';
	public static final char rightDelim = '}';
	public static final char comment = '#';
	private static int numDelims;
	private static Folder root;
	private static Folder currFolder;
	private static CompileError ce;
	
	public SheetParser() {
		numDelims = 0;
		root = new Folder("Root",null,-1);
		currFolder = root;
		ce = new CompileError();
	}
	
	public void parse(String[][] data, int rows, int cols) {
		parseInstrumentData(data,rows,cols);
		parseFolders(data,rows,cols);
		ce.printErrors();
	}
	
	public static void parseInstrumentData(String[][] data, int rows, int cols) {
		Instrument inst = Instrument.getInstance();
		int count = 0;
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				/* As soon as we have all the instrument info, abort so we don't have to continue reading the data */
				if(count == 4) {
					ce.checkError("Instrument",0,0);
					return;
				}
				if(data[i][j] != null) {
					if(data[i][j].length() > 7 && data[i][j].substring(0,7).toLowerCase().equals("prefix:")) {
						inst.prefix = parseRecord(data[i][j]);
						count++;
					}
					else if(data[i][j].length() > 11 && data[i][j].substring(0,11).toLowerCase().equals("identifier:")) {
						inst.identifier = parseRecord(data[i][j]);
						count++;
					}
					else if(data[i][j].length() > 11 && data[i][j].substring(0,11).toLowerCase().equals("technology:")) {
						inst.technology = parseRecord(data[i][j]);
						count++;
					}
					else if(data[i][j].length() > 13 && data[i][j].substring(0,13).toLowerCase().equals("manufacturer:")) {
						inst.manufacturer = parseRecord(data[i][j]);
						count++;
					}
				}
			}
		}
		ce.checkError("Instrument",0,0);
	}
	
	public static void parseFolders(String[][] data, int rows, int cols) {
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				if(data[i][j] != null) {
					/* Read the formatting */
					if(data[i][j].charAt(0) == comment) continue;
					
					if(data[i][j].charAt(0) == leftDelim) {
						Folder newFolder = new Folder(parseFolderName(data[i][j]),currFolder,i);
						currFolder.subFolders.add(newFolder);
						currFolder = newFolder;
						numDelims++;
					}
					
					if(data[i][j].charAt(data[i][j].length() - 1) == rightDelim) {
						numDelims--;
						/* Make sure that if there is an extra bracket, we don't go higher than the root level */
						if(currFolder != root)
							currFolder = currFolder.parent;
					}
					/* Check for Vis */
					else if(currFolder != root && (data[i][j].charAt(0) != leftDelim)) {
						String control = new String("");
						String command = new String("");
						if(j + 1 < cols && data[i][j + 1] != null)
							control = data[i][j + 1];
						if(j + 2 < cols && data[i][j + 2] != null)
							command = data[i][j+2];
						parseVi(data[i][j],control,command, i + 1);
						break;
					}
				}
			}
		}
		ce.checkError("Delim", numDelims, currFolder.row + 1);
		printFolders(root,0);
	}
	
	public static void parseVi(String name, String control, String command, int row) {
		/* Check if this is a Vi name and not a control name */
		if(!(name.length() >= 3 && name.substring(0,3).toLowerCase().equals("in:")) &&
		   !(name.length() >= 4 && name.substring(0,4).toLowerCase().equals("out:"))) {
				Vi newVi = new Vi(name);
				currFolder.vis.add(newVi);
				
				/* Parse the control */
				if(control.length() >= 3 && control.substring(0,3).toLowerCase().equals("in:") ||
				   (control.length() >= 4 && control.substring(0,4).toLowerCase().equals("out:"))) {
					Control cont = parseControl(control, command, row);
					if(cont == null) return;
					newVi.controls.add(cont);
				}
				
				else if(!control.equals("")) {
					ce.checkError("Control", row, CompileError.CONTROL_ERROR_2);
				}
		}
		/* We found a control before finding it's corresponding Vi */
		else {
			ce.checkError("Control", row, CompileError.CONTROL_ERROR_1);
		}
	}

	public static Control parseControl(String control, String command, int row) {
		/* strs is in order of Type, Name, dataType, ring */
		String[] strs = new String[4];
		int count = 0;
		
		if(!isValidControl(control)) {
			ce.checkError("Control", row, CompileError.CONTROL_ERROR_2);
			return null;
		}
		
		StringTokenizer strTok = new StringTokenizer(control, ":");
		
		while(strTok.hasMoreTokens()) {
			strs[count] = strTok.nextToken();
			count++;
		}
		
		if(strs[0].equals("in")) strs[0] = "input";
		else if(strs[0].equals("out")) strs[0] = "output";
		/* Not a recognized type */
		else {
			ce.checkError("Control", row, CompileError.CONTROL_ERROR_2);
			return null;
		}
		
		/* Not a ring or boolean, send empty string */
		if(strs[3] == null) strs[3] = "";
		
		return new Control(strs[0],strs[1],strs[2],command,strs[3]);
	}
	
	public static boolean isValidControl(String name) {
		char[] arr = name.toCharArray();
		int count = 0;
		
		for(int i = 0; i < name.length(); i++) {
			if(arr[i] == ':') count++;
		}
		
		return (count >= 2 && count < 4);
	}
	public static String parseFolderName(String name) {
		String newStr = new String("");
		for(int i = 0; i < name.length(); i++) {
			if(name.charAt(i) != leftDelim && name.charAt(i) != rightDelim) newStr = newStr + name.charAt(i);
		}
		
		return newStr;
	}
	
	public static String parseRecord(String str) {
		char[] newStr = null;
		int index = 0;
		boolean zeros = false;
		boolean start = false;
		
		/* Creates a new string that is the data after the : and ignores all leading spaces */
		for(int i = 0; i < str.length(); i++) {
			if(!start && zeros && (str.charAt(i) != ' ')){
				start = true;
				newStr = new char[str.length() - i];
			}
			
			if(str.charAt(i) == ':') zeros = true;
			if(start) {
				newStr[index] = str.charAt(i);
				index++;
			}
		}
		if(newStr == null) return null;
		return new String(newStr);
	}
	
	public static void printData(String[][] data, int row, int col) {
		for(int i = 0; i < row; i++) {
			for(int j = 0; j < col; j++) {
				if(data[i][j] != null)
					System.out.print(data[i][j] + "\t");
			}
			System.out.println("");
		}
	}
	
	public static void printFolders(Folder f, int tabs) {
		if(f == null) return;
		for(int i = 0; i < tabs; i++)
			System.out.print("   ");
		
		System.out.println(f.getName());
		
		for(Vi v: f.vis) {
			for(int i = 0; i < tabs; i++)
				System.out.print("   ");
			
			System.out.println("--" + v.getName());
			
			for(Control c: v.controls) {
				for(int i = 0; i < tabs; i++)
					System.out.print("   ");
				System.out.println(" >" + c.getName() + " = " + c.getCommand());
			}
		}
		
		for(Folder nf: f.subFolders) {
			printFolders(nf,tabs + 1);
		}
		
	}
}
