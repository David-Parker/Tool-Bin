import java.util.ArrayList;

public class Folder {
	private String name;
	private String path;
	public ArrayList<Vi> vis;
	public ArrayList<Folder> subFolders;
	public Folder parent;
	public int row;
	
	public Folder(String name, Folder parent, int row, String path) {
		subFolders = new ArrayList<Folder>();
		vis = new ArrayList<Vi>();
		this.name = name;
		this.parent = parent;
		this.row = row;
		this.path = path;
	}
	
	public String getName() {
		return name;
	}
	
	public String getPath() {
		return path;
	}
}
