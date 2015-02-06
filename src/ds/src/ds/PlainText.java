package ds;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class PlainText extends Bouncer {

	String dbPath = "C:\\Users\\mgregoire\\can\\db";
	
	public boolean CanAccess(String macAddress) {
		
		try {
			for (String line : Files.readAllLines(Paths.get(dbPath + "\\mydb"))) {
			    if (line.charAt(0) == '#')
			    {
			    	continue;
			    }
			    
				if (line.length() == 12)
			    {
			    	if (line.equalsIgnoreCase(macAddress))
			    		return true;
			    }
			    else if (line.length() > 12)
			    {
			    	if (line.substring(0, 12).equalsIgnoreCase(macAddress))
				    	return true;
			    }
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return false;
	}

	public boolean Detects(String macAddress) 
	{
		String fileName = dbPath + "\\" + macAddress;
		File file = new File(fileName);
		DateFormat df = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
		Date today = Calendar.getInstance().getTime();
		if (file.exists())
		{
			try 
			{
				BufferedWriter output = new BufferedWriter(new FileWriter(fileName, true));
				output.append(df.format(today) + ", " + DatabaseServer.NAME_OF_SERVER);
				output.newLine();
				output.close();
				return true;
			} 
			catch (IOException e) 
			{
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else
		{
			PrintWriter writer;
			try {
				writer = new PrintWriter(fileName, "UTF-8");
				
				writer.println(df.format(today) + ", " + DatabaseServer.NAME_OF_SERVER);
				writer.close();
				return true;
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (UnsupportedEncodingException e) {
				e.printStackTrace();
			}
			
		}
		
		return false;
	}
	
	public String WhoIs(String macAddress) 
	{
		try {
			for (String line : Files.readAllLines(Paths.get(dbPath + "\\mydb"))) {
			    if (line.charAt(0) == '#')
			    {
			    	continue;
			    }
			    else if (line.length() > 14)
			    {
			    	if (line.substring(0, 12).equalsIgnoreCase(macAddress))
				    	return line.substring(13);
			    }
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return null;
	}

}
