package ds;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class AppServerThread extends Thread
{	
	private int port;
	private boolean max;
	public static String DisplayIdaps;
   public AppServerThread(int port)
   {
      this.port = port;
      DisplayIdaps = null;
   }

   public void run()
   {
	   String response = "";
       long time;
       ServerSocket serverSocket;
       Socket socket;
       max = false;

       //BufferedReader reader;
       //String message;
       try {
    	   System.out.println("APP server started");
       	serverSocket = new ServerSocket(port);
       	socket = serverSocket.accept();	
        InetAddress clientIp = socket.getInetAddress();
        int clientPort = socket.getPort();
       	//reader = new BufferedReader( new InputStreamReader ( socket.getInputStream() ) );
       	time = System.currentTimeMillis();
           while(true)
           {	    
           		                
	        //message = reader.readLine();
		        
               

//        	   if(System.currentTimeMillis() - time >= 10000)
//        	   {
//        		   if (max)
//        		   {
//        			   response = "Amgregoire\n";
//        			   max = false;
//        		   }
//        		   else
//        		   {
//        			   response = "Aandyzg\n";
//        			   max = true;
//        		   }
//	               DataOutputStream outToClient = new DataOutputStream(socket.getOutputStream());
//	               System.out.println("APP request = " + response);
//			       outToClient.writeBytes(response);
//			       time = System.currentTimeMillis();
//        	   }
        	   
        	   if(DisplayIdaps != null)
        	   {
        		   response = "A" + DisplayIdaps + "\n";
        		   DataOutputStream outToClient = new DataOutputStream(socket.getOutputStream());
	               System.out.println("APP request = " + response);
			       outToClient.writeBytes(response);
			       System.out.println("Request sent");
        		   DisplayIdaps = null;
        	   }
		        
        	   try {
				Thread.sleep(100);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				System.out.println("Trying to reconnect");
				socket = serverSocket.accept();	
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