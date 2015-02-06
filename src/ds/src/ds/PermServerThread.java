package ds;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class PermServerThread extends Thread
{	
	public static boolean SendManualAccess;
	private int port;
	
   public PermServerThread(int port)
   {
      this.port = port;
      SendManualAccess = false;
   }

   public void run()
   {
	   String response = "";
       long time;
       ServerSocket serverSocket;
       Socket socket;

       //BufferedReader reader;
       //String message;
       try {
    	   System.out.println("PERM server started");
       	serverSocket = new ServerSocket(port);
       	socket = serverSocket.accept();	
        InetAddress clientIp = socket.getInetAddress();
        int clientPort = socket.getPort();
       	//reader = new BufferedReader( new InputStreamReader ( socket.getInputStream() ) );
       	time = System.currentTimeMillis();
           while(true)
           {	    
           		                
	        //message = reader.readLine();
		        
               
               	//System.out.println("PERM : \"" + message + "\" from " + clientIp + ":" + clientPort);
               
               //response = QueryProcessing.ProcessQuery(message);
        	   if(SendManualAccess)//System.currentTimeMillis() - time >= 15000)
        	   {
	        	   response = Response.ManualAccessGranted.command +"";
	               DataOutputStream outToClient = new DataOutputStream(socket.getOutputStream());
	               System.out.println("PERM request = " + response);
			       outToClient.writeBytes(response);  
			       SendManualAccess = false;
			       //time = System.currentTimeMillis();
        	   }
        	   
        	   try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		        
               //reader.close();	
	           // socket.close();
           }
           
           //s.close();
       } 
       catch (IOException e) 
       {
           System.out.println(e);
       }       
   }
}