
public class vBool extends Control{
	
	public vBool(String type, String name, String dataType, Command command, int row) {
		super(type, name, "Bool", command, row);
		polCmd = " {ON|OFF}";
	}

	public void writeTag() {
		AttributeList al = new AttributeList();
		XMLWriter.write(XMLWriter.createTag("Boolean",null,"",false));
		al.add("Text", "Enabled");
		al.add("Value", "1");
		XMLWriter.write(XMLWriter.createTag("True",al.attributes,"",true));
		al.clear();
		
		al.add("Text", "Disabled");
		al.add("Value", "0");
		XMLWriter.write(XMLWriter.createTag("True",al.attributes,"",true));
		XMLWriter.write(XMLWriter.closeTag("Boolean"));
		al.clear();
		
		XMLWriter.write(XMLWriter.closeTag("DataType"));
		al.add("Class","Slide");
		al.add("DefaultValue","1");
		al.add("Label",getName());
		XMLWriter.write(XMLWriter.createTag("Control",al.attributes,"",true));

	}

	public String formatter() {
		return " %s";
	}
}
