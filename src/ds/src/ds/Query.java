package ds;

public enum Query
{
	AccessRequest ("a"),
	ManualAccessRequest ("m");
	
	public final String command;
	
	Query(String command)
	{
		this.command = command;
	}
}