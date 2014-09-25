
public class main {

	public static void main(String[] args) {
		SheetReader sr = new SheetReader();
		String[][] data = sr.readSheet("test/test.xlsx");
		SheetParser parser = new SheetParser();
		Folder root = parser.parse(data, sr.getRows(), sr.getCols());
		Instrument inst= Instrument.getInstance();
		XMLWriter x = new XMLWriter("test/test1.driver",root);
		x.createXML();
		System.out.println("Done.");
//		System.out.println(inst.prefix);
//		System.out.println(inst.identifier);
//		System.out.println(inst.technology);
//		System.out.println(inst.manufacturer);
	}
}
