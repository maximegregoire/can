package ds.data_layer;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.List;

//import com.opencsv.CSVParser;
//import com.opencsv.CSVReader;
//import com.opencsv.CSVWriter;

public class SeparatedCSV extends ds.Bouncer {

	private final String csvLocation = "C:\\csvdb";
	
	private final String csvMacToIdaps = "C:\\csvdb\\macToIdaps.csv";
	
	public boolean CanAccess(String macAddress) {
		
		File folder = new File(csvLocation);
		File[] listOfFiles = folder.listFiles();
		
		return false;
	}

	public boolean Detects(String macAddress) {
		return false;
	}

	public boolean GetIdaps(String macAddress, String idaps) throws IOException
	{
		//TODO: check if map is dirty. If it is, reload.
		
//		CSVReader reader = new CSVReader(new FileReader("csvMacToIdaps.csv"));
//		List<String[]> myEntries = reader.readAll();
//		
//		for (String[] l : myEntries)
//		{
//			if (l.length >= 2 && l[1].equals(macAddress))
//			{
//				idaps = l[0];
//				return true;
//			}
//		}
		
		return false;
	}
}
