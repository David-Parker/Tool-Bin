import java.util.ArrayList;

public class SheetParser {
	public static final char leftDelim = '[';
	public static final char rightDelim = ']';
	private static int numDelims;
	private static Folder root;
	private static Folder currFolder;
	
	public SheetParser() {
		numDelims = 0;
		root = new Folder("Root",null,-1);
		currFolder = root;
	}
	
	public void parse(String[][] data, int rows, int cols) {
		parseInstrumentData(data,rows,cols);
		parseFolders(data,rows,cols);
	}
	
	public static void parseInstrumentData(String[][] data, int rows, int cols) {
		Instrument inst = Instrument.getInstance();
		CompileError ce = new CompileError();
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
		CompileError ce = new CompileError();
		
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				if(data[i][j] != null) {
					/* Read the formatting */
					if(data[i][j].charAt(0) == leftDelim) {
						Folder newFolder = new Folder(parseFolderName(data[i][j]),currFolder,i);
						currFolder.subFolders.add(newFolder);
						currFolder = newFolder;
						numDelims++;
					}
					
					if(data[i][j].charAt(data[i][j].length() - 1) == rightDelim) {
						numDelims--;
						currFolder = currFolder.parent;
					}
				}
			}
		}
		/* In case of an extra bracket somewhere, and the currFolder is null */
		if(currFolder == null) currFolder = root;
		ce.checkError("Delim", numDelims, currFolder.row + 1);
		printFolders(root,0);
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
			System.out.print("  ");
		
		System.out.println(f.getName());
		for(Folder nf: f.subFolders) {
			printFolders(nf,tabs + 1);
		}
	}
}
