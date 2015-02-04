package ds;

import java.util.ArrayList;

public enum Response {
	AccessGranted ('G'),
	AccessDenied ('D'),
	ManualAccessGranted ('M'),
	ShowOnMonitor ('s');
	
	public final char command;
	
	Response(char command)
	{
		this.command = command;
	}
}
