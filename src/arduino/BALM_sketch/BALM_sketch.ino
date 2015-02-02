#include <SoftwareSerial.h>  
char buffer[300];
char deviceMAC[12];
char rssi[2];

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

const char END_SEQUENCE[] = "Inquiry Done";
const byte END_SEQUENCE_CHAR_COUNT = 12;
const char ERROR_SEQUENCE[] = "ERR";
const unsigned long TIMEOUT = 13000;

boolean requestSignals;
int endSequenceCount;
int bufferIndex;
unsigned long requestTime;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);


void setup()
{
  Serial.begin(9600);  // Begin the serial monitor at 9600bps

  bluetooth.begin(115200);  // The Bluetooth Mate defaults to 115200bps
  bluetooth.print("$");  // Print three times individually
  bluetooth.print("$");
  bluetooth.print("$");  // Enter command mode
  
  delay(100);  // Short delay, wait for the Mate to send back CMD
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  
  //delay(500);
  //bluetooth.println("SM,1");
  
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  bluetooth.print("$$$");
  requestSignals = true;
  delay(500);
}

void getMAC()
{
  for (int i = 0; i < 12; i++)
  {
    deviceMAC[i] = buffer[25+i];
  }
}

void parseBuffer()
{
  getMAC();
  
  deviceMAC
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
    Serial.println("Sending IQ2 signals");
    bluetooth.println("IQ2"); 
    requestTime = millis();
    bufferIndex = 0;
    requestSignals = false;
    endSequenceCount = 0;
  }
  
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    buffer[bufferIndex] = (char)bluetooth.read();
    Serial.print(buffer[bufferIndex]);
    
    // Check for error
    if (bufferIndex >= 2 && buffer[bufferIndex] == 'R' 
        && buffer[1] == 'R' && buffer[0] == 'E')
    {
       Serial.println("ERROR MUST ABORT");
       setup();
    }
    
    // Check for end sequence
    if (buffer[bufferIndex] == END_SEQUENCE[endSequenceCount])
    {
      //Serial.print("Compare success # ");
      //Serial.println(bufferIndex);
      if(endSequenceCount == END_SEQUENCE_CHAR_COUNT - 1)
      {
        //TODO finish
        parseBuffer();
        Serial.println("END SEQUENCE FOUND");
        requestSignals = true;
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
    if (millis() - requestTime == TIMEOUT)
    {
      Serial.println("Timeout");
      requestSignals = true;
    }
  }
  
  
  
  
  
//  delay(1000);
//  while(bluetooth.available())
//  {
//    buffer[i] = (char)bluetooth.read();
//    
//    i++;
//  }
  
//  delay(4000);
//  Serial.print("available = ");
//  Serial.println(bluetooth.available());
//  
//  while(bluetooth.available() != 0)
//  {
//    while(bluetooth.available() != 0)
//    {
//      buffer[i] = (char)bluetooth.read();
//      i++;
//    }
//    delay(100);
//  }
//  
//  Serial.println(buffer);
  
//  // 64 maximum buffer capacity
//  if(bluetooth.available() == 63)
//  {
//    while(i!=63)
//    {
//      buffer[i] = (char)bluetooth.read();
//      i++;
//    }
//  }
//  
//  Serial.println(buffer);
//  
//  delay(100);
//  
//  Serial.print("after 1st buffer emptied = ");
//  Serial.println(bluetooth.available());
  
//  while(bluetooth.available())
//  {
//    buffer[i] = (char)bluetooth.read();
//    //if (i == 25) break;
//    if (i ==63) break;
//    i++;
//  }
//  delay(1500);
//  
//  while(bluetooth.available())
//  {
//    buffer[i] = (char)bluetooth.read();
//    //if (i == 25) break;
//    if (i ==63+64) break;
//    i++;
//  }
//  
//  delay(500);
//  
//  while(bluetooth.available())
//  {
//    buffer[i] = (char)bluetooth.read();
//    //if (i == 25) break;
//    if (i ==63+128) break;
//    i++;
//  }
//  
//  Serial.println(buffer);
  
  
  
  
  
  
  
//  if (buffer[25] >= '1' && buffer[25] <= '9')
//  {
//    int number = buffer[25] - '0'; // Char-to-digit conversion
//    
//    // Devices found
//    if (number > 0)
//    {
//      // Skip 2 chars (space and newline)
//      bluetooth.read();
//      bluetooth.read();
//      
//      Serial.print(number);
//      Serial.println(" devices");
//      
//      // Go through devices' info
//      for (int j = 0; j < number; j++)
//      {
//        i = 0;
//        
//        // MAC Address
//        while(bluetooth.available())
//        {
//          deviceMAC[i] = (char)bluetooth.read();
//          if (i == 11) break;
//          i++;
//        }
//        
//        // Skip 17 characters
//        for (i = 0; i < 17; i++)
//        {
//          bluetooth.read();
//        }
//        
//        // Signal strength, smaller is closer
//        i = 0;
//        while(bluetooth.available())
//        {
//          rssi[i] = (char)bluetooth.read();
//          if (i == 1) break;
//          i++;
//        }
//        
//        if (rssi[0] >= '1' && rssi[0] <= '9' && rssi[1] >= '1' && rssi[1] <= '9')
//        {
//          // string to int conversion [10 to 99]
//          int rssiNum = ((rssi[0]-'0')*10) + (rssi[1]-'0');
//          Serial.print(deviceMAC);
//          Serial.print(" => ");
//          Serial.println(rssiNum);
//          
//          //TODO send through ethernet
//        }
//        
//        bluetooth.read();
//      }
//    }
//  }
  
    
  //clearAll();
}

