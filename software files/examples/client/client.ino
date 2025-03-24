#include "Arduino.h"
#include "SoftwareSerial.h"

SoftwareSerial mySerial(21, 22);
uint32_t countdown = 10000;
char receiveBuffer[128];
uint8_t commandOrder=0;
#define order_limit 7
extern void tcpServerConfig(uint8_t command_Order);

uint8_t check() {
 for(int i = 0; i < 50; i++) {
    
    if (receiveBuffer[i] == 'O' && receiveBuffer[i+1] == 'K')
    { 
      return true;
    }
    else
    {
      if (i==49);

      //return false;
    }
 }
}


void readSerial() {
  uint8_t data_count=0;
  uint8_t send_count=0;
  //Serial.write(mySerial.read());
  countdown=10000;
  while (countdown)
    {
    if (mySerial.available())
      {
      receiveBuffer[data_count]=mySerial.read();
      data_count++;  
      countdown=10000;  
      }  
    countdown--;  
    }
  send_count=data_count;
  while (send_count)
    {
    Serial.print(receiveBuffer[data_count-send_count]);
    send_count--;  
    }
  if (check())
    {
      if (commandOrder<order_limit)
        {
        commandOrder++;
    
        }
      else
        {

        }  
    }
    else
    {

    }   
}

void tcpClientConfig() {
uint8_t i=0;
while (order_limit-commandOrder)
  {
  delay(100);  
  switch (commandOrder)
    {     
     case 0:{mySerial.println("AT");readSerial();} break;
     case 1:{mySerial.println("AT+CWMODE=1");readSerial();} break;
     case 2:{mySerial.println("AT+CWJAP_DEF=\"Mi Telefon\",\"12345678\""); delay(15000); readSerial();} break;
     case 3:{mySerial.println("AT+CIFSR");readSerial();} break;
     case 4:{mySerial.println("AT+CIPMUX=0");readSerial();} break;
     case 5:{mySerial.println("AT+CIPSTART=\"TCP\",\"192.168.4.1\",\"333\"");readSerial();} break;
     case 6:{mySerial.println("AT+CIPSEND=10");readSerial();} break;
    }
  }
}

void tcpServerConfig() {
uint8_t i=0;
while (order_limit-commandOrder)
  {
  delay(100);  
  switch (commandOrder)
    {     
     case 0:{mySerial.println("AT");readSerial();} break;
     case 1:{mySerial.println("AT+CWMODE=2");readSerial();} break;
     case 2:{mySerial.println("AT+CWSAP_DEF=\"BOARDOZA_IOT\",\"12345678\",5,4");readSerial();} break;
     case 3:{mySerial.println("AT+CIFSR");readSerial();} break;
     case 4:{mySerial.println("AT+CIPMUX=1");readSerial();} break;
     case 5:{mySerial.println("AT+CIPSERVER=1");readSerial();} break;
    }
  }
  
}

void setup() {

  Serial.begin(115200);
  while(!Serial){

  }
  mySerial.begin(115200);
  while(!mySerial){

  }
  tcpClientConfig();
  //tcpServerConfig();

}
void loop() {

/*
  if(Serial.available() > 0)
    {
    mySerial.write(Serial.read()); 
    }
  if(mySerial.available() > 0)
    { 
    Serial.write(mySerial.read()); 
    }
delay(5);*/
}