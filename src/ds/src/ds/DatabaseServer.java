package ds;

import java.io.*;
import java.net.*;

public class DatabaseServer {

	public final static boolean DEBUG = true;
	
	public static void main(String[] args)
	{
		String clientSentence = "";
        String response = "";
        boolean needResponse;
        
        ServerSocket serverSocket;
        Socket socket;

        BufferedReader reader;
        String message;
        try {
        	serverSocket = new ServerSocket(8887);
        	
            while(true)
            {	    
            	socket = serverSocket.accept();	
            	reader = new BufferedReader( new InputStreamReader ( socket.getInputStream() ) );	                
	            message = reader.readLine();
	            InetAddress clientIp = socket.getInetAddress();
		        int clientPort = socket.getPort();
		        
                if (DEBUG)
                {
                	System.out.println("\"" + message + "\" from " + clientIp + ":" + clientPort);
                }
                
                DataOutputStream outToClient = new DataOutputStream(socket.getOutputStream());
		        outToClient.writeBytes("Some clever response");
                
		        
                reader.close();	
	            socket.close();
            }
            
            //s.close();
        } catch (IOException e) {
            System.out.println(e);
        }       
        
        
//        	ServerSocket welcomeSocket;
//			try {
//				welcomeSocket = new ServerSocket(6999);
//				welcomeSocket.setSoTimeout(10000); 
//				while(true)
//		        {
//		        	//TODO: limit string char amount
//		           Socket connectionSocket = welcomeSocket.accept();
//		           BufferedReader inFromClient =
//		              new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
//		           InetAddress clientIp = connectionSocket.getLocalAddress();
//		           int clientPort = connectionSocket.getLocalPort();
//		           DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
//		           clientSentence = inFromClient.readLine();
//		           outToClient.writeBytes("ok");
//		           if (DEBUG)
//		           {
//		        	   System.out.println("Received: \"" + clientSentence + "\" From : " + clientIp.toString() + ":" + clientPort);
//		           }
//
//					welcomeSocket.close();
//		           //needResponse = QueryProcessing.ProcessQuery(clientSentence, response);
//		           
//		           //if (needResponse)
//		           //{
//		        	//   outToClient.writeBytes(response);   
//		           //}
//		        }
//				
//			} catch (IOException e) {
//				
//				//e.printStackTrace();
//				welcomeSocket = null;
//			}

        
//		String clientSentence;
//        String capitalizedSentence;
//        ServerSocket welcomeSocket = new ServerSocket(6789);

//        while(true)
//        {
//           Socket connectionSocket = welcomeSocket.accept();
//           BufferedReader inFromClient =
//              new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
//           DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
//           clientSentence = inFromClient.readLine();
//           System.out.println("Received: " + clientSentence);
//           capitalizedSentence = clientSentence.toUpperCase() + '\n';
//           outToClient.writeBytes(capitalizedSentence);
//        }

	}

}
