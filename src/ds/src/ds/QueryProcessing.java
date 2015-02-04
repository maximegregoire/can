package ds;

public class QueryProcessing {	

	public final static String ENDLINE = "\n";
	
	public static String ProcessQuery(String query, Bouncer bouncer)
	{
		if (!ValidateQuery(query))
		{
			return null;
		}
		
		switch (query.charAt(0))
		{
		case 'A':
			if (query.length() >= 13 && bouncer.CanAccess(query.substring(1)))
			{
				bouncer.Detects(query.substring(1));
				return Response.AccessGranted.command + query.substring(1) + ENDLINE;
			}
			else
			{
				return Response.AccessDenied.command + "";
			}
			
		case 'M':
			if (query.length() >= 13 && bouncer.CanAccess(query.substring(1)))
			{
				bouncer.Detects(query.substring(1));
				PermServerThread.SendManualAccess = true;
				return null;
			}
			else
			{
				return Response.AccessDenied.command + "";
			}
			
		default:
			//invalid query
			return null;
		}
	}
	
	private static boolean ValidateQuery(String query)
	{
		//For now, since all querries are 1 char commands only
		//TODO validate length
		char firstChar = query.charAt(0);
		
		for (Query q : Query.values())
		{
			if (q.command == (firstChar))
			{
				return true;
			}
		}
		
		return false;
	}
}
