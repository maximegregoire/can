package ds;

public class QueryProcessing {	

	public final static String ENDLINE = "\n";
	
//	public static boolean ProcessQuery(String query, String response)
//	{
//		if (!ValidateQuery(query))
//		{
//			return false;
//		}
//		
//		switch (query)
//		{
//		case "a":
//			//check for access
//			
//			//change this
//			response = "g" + query.substring(1) + ENDLINE;
//		case "m":
//			//check for manual access
//		default:
//			//invalid query
//			return false;
//		}
//	}
	
	private static boolean ValidateQuery(String query)
	{
		//For now, since all querries are 1 char commands only
		String firstChar = query.substring(0, 1);
		
		for (Query q : Query.values())
		{
			if (q.command.equals(firstChar))
			{
				return true;
			}
		}
		
		return false;
	}
}
