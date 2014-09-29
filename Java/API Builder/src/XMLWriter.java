import java.io.*;
import java.util.ArrayList;


public class XMLWriter {
	private static PrintStream specFile;
	private static Folder root;
	private static CompileError ce;
	
	public static final boolean toConsole = false;
	
	public XMLWriter(String file, Folder root) {
		this.root = root;
		ce = new CompileError();
		
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
		writeFunctions();
		write(closeTag("Interface"));
		write(closeTag("API"));
		
		/* Write out commands */
		writeCommands();
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
		Instrument instr = Instrument.getInstance();
		write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>");
		write("<!-- This Driver Specification file was created with API Builder -->");
		write("<IDSpecification xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" Author=\"Liping\" Company=\"String\" Fax=\"String\" Phone=\"String\" Version=\"String\" xsi:noNamespaceSchemaLocation=\"ID%20Specification.xsd\">");
		AttributeList al = new AttributeList();
		al.add("Identifier",instr.identifier);
		al.add("Template","C:\\Program Files\\National Instruments\\LabVIEW 8.6\\instr.lib\\_Template - Generic");
		write(createTag("Application",al.attributes,"",false));
		write(closeTag("Application"));
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
		write(createTag("Technology",null,"LabVIEW PNP",true));
		write(createTag("Manufacturer",null,inst.manufacturer,true));
		write("<InstrumentModels><InstrumentModel/></InstrumentModels><CommunicationInterface><IndustoryBus>USB</IndustoryBus></CommunicationInterface><ModelTested><InstrumentModel/></ModelTested><FirmwareTested><Manufacturer/><InstrumentModel/><SerialNO/><BuildVersion/></FirmwareTested><InterfaceTested><IndustoryBus>USB</IndustoryBus></InterfaceTested>");
	}
	
	public static void writeFolders(Folder fold) {
		write(createTag("Folders",null,"",false));
		writeFoldersRecurse(fold);
		write(closeTag("Folders"));
	}
	
	public static void writeFoldersRecurse(Folder fold) {	
		write(createTag("FolderPath",null,fold.getPath(),true));
		
		for(Folder f: fold.subFolders) {
			writeFoldersRecurse(f);
		}
	}
	
	public static void writeFunctions() {
		write("<API Version=\"String\">");
		write("<Interface Identifier=\"String\">");
		//writeTemplateFunctions();
		writeCustomFunctions();
	}
	
	public static void writeTemplateFunctions() {
		try {
			FileReader reader = new FileReader("data/template.data");
			BufferedReader br = new BufferedReader(reader);
			String line;
			
			while((line = br.readLine()) != null) {
				write(line);
			}
			
			br.close();
		}
		
		catch(FileNotFoundException ex) {
			/* Missing template.data file */
			ce.checkError("File",CompileError.ERROR_1,0);
		}
		
		catch(IOException ex) {
			/* Corrupted Template data file */
			ce.checkError("File",CompileError.ERROR_2,0);
		}
	}
	
	public static void writeCustomFunctions() {
		AttributeList al = new AttributeList();
		writeCustomFunctionsRecurse(root,al);
	}
	
	public static void writeCustomFunctionsRecurse(Folder fold, AttributeList al) {
		for(Vi v: fold.vis) {
			al.clear();
			al.add("Identifier",v.getName());
			al.add("Source","Customized");
			write(createTag("Function",al.attributes,"",false));
			
			write(createTag("Flag",null,"",false));
			write(createTag("DesignerFlag",null,"Configuration/Action-Status",true));
			write(closeTag("Flag"));
			
			write(createTag("Path",null,v.getFolder().getPath(),true));
			write(createTag("Description",null,"",true));
			write(createTag("ErrorQuery",null,"false",true));
			write(createTag("ManualUpdate",null,"false",true));
			write(createTag("BlockDiagramComments",null,"",true));
			
			al.clear();
			al.add("TotalNumber","" + v.controls.size());
			write(createTag("Parameters",al.attributes,"",true));
			
			for(Control c: v.controls) {
				writeControl(c,al);
				//System.out.println(v.getFolder().getPath());
				//System.out.println(c.getDataType());
			}
			
			write(closeTag("Function"));
		}
		
		for(Folder f: fold.subFolders) {
			writeCustomFunctionsRecurse(f,al);
		}
	}
	
	public static void writeControl(Control c, AttributeList al) {
		al.clear();
		al.add("Access","RW");
		al.add("Extension","true");
		al.add("IDValue","");
		al.add("Identifier",c.getName());
		al.add("InputOutput",c.getType());
		write(createTag("Parameter",al.attributes,"",false));
		al.clear();
		al.add("NativeDescriptor","");
		write(createTag("DataObject",al.attributes,"",false));
		write(createTag("DataType",null,"",false));
		
		writeControlDataType(c,al);
		
		write(closeTag("DataType"));
		write(closeTag("DataObject"));
		write(closeTag("Parameter"));
	}
	
	public static void writeControlDataType(Control c, AttributeList al) {
		
	}
	
	public static void writeCommands() {
		AttributeList al = new AttributeList();
		al.add("NumberOfCommands","" + root.numCommands);
		write(createTag("Commands",al.attributes,"",false));
		writeCommandsRecurse(root,al);
		//write("<Command Identifier=\"Test/" NumberOfImplentation=1)
		write("<Command Identifier=\"*IDN?\" NumberOfImplementation=\"1\"/><Command Identifier=\"*RST\" NumberOfImplementation=\"1\"/><Command Identifier=\"*TST?\" NumberOfImplementation=\"1\"/><Command Identifier=\":SYST:ERR?\" NumberOfImplementation=\"1\"/>");
		write(closeTag("Commands"));
	}
	
	public static void writeCommandsRecurse(Folder fold, AttributeList al) {
		for(Vi v : fold.vis) {
			for(Control c: v.controls) {
				if(!c.getCommand().equals("")) {
					al.clear();
					al.add("Identifier",c.getCommand());
					al.add("NumberOfImplementation","1");
					write(createTag("Command",al.attributes,"",true));
				}
			}
		}
		
		for(Folder f: fold.subFolders) {
			writeCommandsRecurse(f,al);
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
