#include <SoftwareSerial.h>  
char buffer[300];
char deviceMAC[12];

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

void getMAC(int index)
{
  for (int i = 0; i < 12; i++)
  {
    deviceMAC[i] = buffer[index+i];
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
    //Serial.print(buffer[bufferIndex]);
    
    // Check for error
    if ((bufferIndex >= 2 && buffer[bufferIndex] == 'R' 
        && buffer[1] == 'R' && buffer[0] == 'E'))
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
        //Serial.println("END SEQUENCE FOUND");
        clearAll();
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
}

