#include <SoftwareSerial.h>  

char buffer[200];

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

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
  // 115200 can be too fast at times for NewSoftSerial to relay the data reliably
  bluetooth.begin(9600);  // Start bluetooth serial at 9600
  bluetooth.print("$$$");
  delay(100);
}

//void clearAll() {
//    for(int i = 0; i < bluetooth.available(); i++) {
//        bluetooth.read();
//    }
//}
//
//void readSerial(int h, char * buffer) {
//    char input;
//    if (bluetooth.available() > 0) {
//        int j = 0;
//        for (int i = 0; i < h; i++) { // the id's start at char 21, se we copy from there
//            input = (char)bluetooth.read();
//            if(i >= 21) {
//                buffer[j] = input;
//                buffer[j+1] = '\0';
//                j++;
//            }
//        }
//        return;
//    } else {
//        return;
//    }
//}

void loop()
{ 
  bluetooth.println("IQ2"); 
  int i = 0;
  delay(500);
  while(bluetooth.available())
  {
    buffer[i] = (char)bluetooth.read();
    
    i++;
  }
  
  delay(4500);
  
  while(bluetooth.available())
  {
    buffer[i] = (char)bluetooth.read();
    
    i++;
  }
  
  Serial.println(buffer);
  
}

