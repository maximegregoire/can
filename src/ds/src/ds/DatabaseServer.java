package ds;

import java.io.*;
import java.net.*;

public class DatabaseServer {

	public final static boolean DEBUG = true;
	
	public static void main(String[] args) throws Exception{
		String clientSentence = "";
        String response = "";
        boolean needResponse;
        
        ServerSocket welcomeSocket = new ServerSocket(7777);

        while(true)
        {
           Socket connectionSocket = welcomeSocket.accept();
           BufferedReader inFromClient =
              new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
           InetAddress clientIp = connectionSocket.getLocalAddress();
           int clientPort = connectionSocket.getLocalPort();
           DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
           clientSentence = inFromClient.readLine();
           
           if (DEBUG)
           {
        	   System.out.println("Received: \"" + clientSentence + "\" From : " + clientIp.toString() + ":" + clientPort);
           }
           
           needResponse = QueryProcessing.ProcessQuery(clientSentence, response);
           
           if (needResponse)
           {
        	   outToClient.writeBytes(response);   
           }
        }

	}

}
