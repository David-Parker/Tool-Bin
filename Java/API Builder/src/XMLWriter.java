import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;


public class XMLWriter {
	private static PrintStream specFile;
	private static Folder root;
	
	public static final boolean toConsole = true;
	
	public XMLWriter(String file, Folder root) {
		this.root = root;
		
		if(toConsole)
			specFile = System.out;
		else {
			try {
				specFile = new PrintStream(new File(file));
			} 
			catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}
	}
	
	public void createXML() {
		writeMetaData();
		writeInstrumentInfo();
		writeFolders(root);
		write(closeTag("General"));
		write(closeTag("IDSpecification"));
	}
	
	public static String createTag(String name, ArrayList<Attribute> att, String contents, boolean close) {
		String formatted = "<" + name;
		
		if(att != null) {
			for(Attribute a: att) {
				formatted += " " + a.name + "=\"" + a.value + "\"";
			}
		}
		
		formatted += ">" + contents;
		
		if(close)
			formatted += closeTag(name);
		
		return formatted;
	}
	
	public static String closeTag(String name) {
		return "</" + name + ">";
	}
	
	public static void writeMetaData() {
		write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>");
		write("<!-- This Driver Specification file was created with API Builder -->");
		write("<IDSpecification xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" Author=\"Liping\" Company=\"String\" Fax=\"String\" Phone=\"String\" Version=\"String\" xsi:noNamespaceSchemaLocation=\"ID%20Specification.xsd\">");
		write("<ModificationHistory>");
		write("<Creation Application=\"text\" Comments=\"String\" Date=\"1967-08-13\"/>");
		write("<Modification Application=\"String\" Comments=\"\" Date=\"2014-09-25\"/>");
		write("</ModificationHistory>");
	}
	
	public static void writeInstrumentInfo() {
		Instrument inst = Instrument.getInstance();
		write(createTag("General",null,"",false));
		write(createTag("Prefix",null,inst.prefix,true));
		write(createTag("Identifier",null,inst.identifier,true));
		write(createTag("Technology",null,inst.technology,true));
		write(createTag("Manufacturer",null,inst.manufacturer,true));
		write("<InstrumentModels><InstrumentModel/></InstrumentModels><CommunicationInterface><IndustoryBus>USB</IndustoryBus></CommunicationInterface><ModelTested><InstrumentModel/></ModelTested><FirmwareTested><Manufacturer/><InstrumentModel/><SerialNO/><BuildVersion/></FirmwareTested><InterfaceTested><IndustoryBus>USB</IndustoryBus></InterfaceTested>");
	}
	
	public static void writeFolders(Folder fold) {
		write(createTag("Folders",null,"",false));
		writeFoldersRecurse(fold);
		write(closeTag("Folders"));
	}
	
	public static void writeFoldersRecurse(Folder fold) {
		if(fold == null) return;
		
		write(createTag("FolderPath",null,fold.getPath(),true));
		
		for(Folder f: fold.subFolders) {
			writeFoldersRecurse(f);
		}
	}
	
	public static void writeln(String str) {
		specFile.println(str);
	}
	
	public static void write(String str) {
		if(toConsole)
			specFile.println(str);
		else specFile.print(str);
	}
}
