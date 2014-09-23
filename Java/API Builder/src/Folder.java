import java.util.ArrayList;

public class Folder {
	private String name;
	public ArrayList<Vi> vis;
	public ArrayList<Folder> subFolders;
	public Folder parent;
	public int row;
	
	public Folder(String name, Folder parent, int row) {
		subFolders = new ArrayList<Folder>();
		this.name = name;
		this.parent = parent;
		this.row = row;
	}
	
	public String getName() {
		return name;
	}
}
