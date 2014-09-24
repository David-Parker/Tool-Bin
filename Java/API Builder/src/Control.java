
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
}
