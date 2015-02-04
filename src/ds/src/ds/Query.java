package ds;

public enum Query
{
	AccessRequest ('A'),
	ManualAccessRequest ('M');
	
	public final char command;
	
	Query(char command)
	{
		this.command = command;
	}
}