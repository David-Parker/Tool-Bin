
public class Control {
	private String type;
	private String name;
	private String dataType;
	private String command;
	private String ringValue;
	public final static String[] dataTypes = {"double","integer","int","string","boolean","bool","ring"};
	public final static int NUM_DATA_TYPES = 7;
	
	public Control(String type, String name, String dataType, String command, String ringValue) {
		this.type = type;
		this.name = name;
		this.dataType = dataType;
		this.command = command;
		this.ringValue = ringValue;
	}
	
	public String getName() {
		return name;
	}
	
	public String getType() {
		return type;
	}
	
	public String getCommand() {
		return command;
	}
	
	public String getRing() {
		return ringValue;
	}
	
	public String getDataType() {
		return dataType;
	}
	
	public static String fixDataTypes(String str) {
		if(str.toLowerCase().equals("int") || str.toLowerCase().equals("integer")) {
			return "I32";
		}
		
		else if(str.toLowerCase().equals("double")) {
			return "DBL";
		}
		
		else if(str.toLowerCase().equals("string")) {
			return "String";
		}
		
		else if(str.toLowerCase().equals("boolean") || str.toLowerCase().equals("bool")) {
			/* TODO Add Case */
			return str;
		}
		
		else if(str.toLowerCase().equals("ring")) {
			/* TODO Add Case */
			return str;
		}
		
		return str;
	}
	
	public static boolean isValidControlName(String name) {
		char[] arr = name.toCharArray();
		int count = 0;
		
		for(int i = 0; i < name.length(); i++) {
			if(arr[i] == ':') count++;
		}
		
		return (count >= 2 && count < 4);
	}
}
