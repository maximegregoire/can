#include <SoftwareSerial.h>  
#include <SPI.h>
#include <Ethernet.h>

// Pins map
int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

// Constant values
const int DETECTION_THRESHOLD = 58;
const char END_SEQUENCE[] = "Inquiry Done";
const byte END_SEQUENCE_CHAR_COUNT = 12;
const char NO_DEVICE_SEQUENCE[] = "No Devices Found";
const byte NO_DEVICE_SEQUENCE_CHAR_COUNT = 16;
const char ERROR_SEQUENCE[] = "ERR";
const unsigned long TIMEOUT = 13000; //ms
const byte SERVER[] = { 172, 29, 12, 15 };
const int SERVER_PORT = 8887;
byte MAC[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x88, 0x6D };

// Global variables
char buffer[300];
char deviceMAC[12];
boolean requestSignals;
int endSequenceCount;
int noDeviceSequenceCount;
int bufferIndex;
unsigned long requestTime;

// Global objects
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
EthernetClient client;
IPAddress IP(192,168,0,177); //fallback if DHCP fails

void emptyBuffer()
{
  while(bluetooth.available())
  {
    bluetooth.read();
    delay(20);
  }
}

void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("SF,1");
  delay(1000);
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  
  //delay(500);
  //bluetooth.println("SM,1");
  
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  bluetooth.print("$$$");
  requestSignals = true;
  
  //IP assignation try
  if (Ethernet.begin(MAC) == 0) 
  {
    delay(10000);
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(MAC, IP);
  }
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  
  delay(1000);
}

void getMAC(int index)
{
  for (int i = 0; i < 12; i++)
  {
    deviceMAC[i] = buffer[index+i];
  }
}

void sendAccessRequest(int rssi)
{
  if (rssi <= DETECTION_THRESHOLD)
  {
    if(client.connect(SERVER, SERVER_PORT))
    {
      client.print("A");
      client.println(deviceMAC);
      char response[20];
      byte responseIndex = 0;
      
      Serial.println("Waiting on server");
      
      while(!client.available())
      {      
      }
      
      while(client.available())
      {
        response[responseIndex] = (char)client.read();
        responseIndex++;
        delay(10);
      }
      
      Serial.println(response);
      
      digitalWrite(9, HIGH);   // sets the LED on
      delay(5000);                  // waits for a second
      digitalWrite(9, LOW);
      
      client.stop();
    }  
  }
}

void parseBuffer()
{
  byte comasAmount = 0;
  byte indexBuffer = 19;
  byte numberOfDevices = -1;
  while(numberOfDevices < 0 || numberOfDevices > 9)
  {
    numberOfDevices = buffer[indexBuffer] - '0';
    indexBuffer++;
  }
  
    
  //Serial.print("NUMBER OF DEVICES = ");
  //Serial.println(numberOfDevices);
    
  indexBuffer = indexBuffer + 2;
  int rssiNum;
  for(int deviceIndex = 0; deviceIndex < numberOfDevices; deviceIndex++)
  {
    rssiNum = 0;
    comasAmount = 0;
    getMAC(indexBuffer);
    Serial.print("MAC ADDRESS = ");
    Serial.println(deviceMAC);
    
    // Look for 3 comas
    while(comasAmount != 3)
    {
      indexBuffer++;
      if (buffer[indexBuffer] == ',')
      {
        comasAmount++;
      }
    }
    
    // Get RSSI
    indexBuffer = indexBuffer + 2;
    //Serial.println("");
    //Serial.println(buffer[indexBuffer]);
    rssiNum = ((buffer[indexBuffer]-'0')*10) + (buffer[indexBuffer + 1]-'0');
    Serial.print("RSSI = ");
    Serial.println(rssiNum);
    
    // Put buffer to next line
    indexBuffer = indexBuffer + 4;
    
    sendAccessRequest(rssiNum);
  }
}

void clearAll()
{
  while(bluetooth.available())
  {
    bluetooth.read();
  }
  
  for(int i = 0; i<200; i++)
  {
    buffer[i] = '\0';
  }
}

void loop()
{ 
  if (requestSignals)
  {
    clearAll();
    Serial.println("");
    Serial.println("Sending IQ2 signals");
    bluetooth.println("IQ2"); 
    requestTime = millis();
    bufferIndex = 0;
    requestSignals = false;
    endSequenceCount = 0;
    noDeviceSequenceCount = 0;
  }
  
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    buffer[bufferIndex] = (char)bluetooth.read();
    Serial.print(buffer[bufferIndex]);
    
    // Check for error
    if ((bufferIndex >= 2 && buffer[bufferIndex] == 'R' 
        && buffer[1] == 'R' && buffer[0] == 'E'))
    {
       Serial.println(""); 
       Serial.println("ERROR MUST ABORT");
       requestSignals = true;
       return;
    }
    
    // Check for no device found
    if (buffer[bufferIndex] == NO_DEVICE_SEQUENCE[noDeviceSequenceCount])
    {
      if(noDeviceSequenceCount == NO_DEVICE_SEQUENCE_CHAR_COUNT - 1)
      {
        Serial.println("");
        Serial.println("NO DEVICE FOUND");
        requestSignals = true;
      }
      
      noDeviceSequenceCount++;
      bufferIndex++;
      return;
    }
    else
    {
      noDeviceSequenceCount = 0;
    }
    
    
    // Check for end sequence
    if (buffer[bufferIndex] == END_SEQUENCE[endSequenceCount])
    {
      //Serial.print("Compare success # ");
      //Serial.println(bufferIndex);
      if(endSequenceCount == END_SEQUENCE_CHAR_COUNT - 1)
      {
        Serial.println("");
        
        if(buffer[0]=='I')
        {        
          parseBuffer();
          //Serial.println("END SEQUENCE FOUND");
        }
        
        //Serial.println("RESTARTING");
        requestSignals = true;
        return;
      }
      
      endSequenceCount++;
    }
    else
    {
      endSequenceCount = 0;
    }
    
    bufferIndex++;
  }
  else
  {
    if (millis() - requestTime >= TIMEOUT)
    {
      Serial.println("Timeout");
      requestSignals = true;
    }
  }
}

