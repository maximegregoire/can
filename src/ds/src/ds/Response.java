package ds;

import java.util.ArrayList;

public enum Response {
	AccessGranted ("g"),
	AccessDenied ("d"),
	ManualAccessGranted ("m"),
	ShowOnMonitor ("s");
	
	public final String command;
	
	Response(String command)
	{
		this.command = command;
	}
}
