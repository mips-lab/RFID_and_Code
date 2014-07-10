#include <SoftwareSerial.h>
 
SoftwareSerial SoftSerial(12, 13);
unsigned char buffer[64]; // buffer array for data recieve over serial port
unsigned char buffer2[4];
unsigned long currentTime;
unsigned long loopTime;
int count=0;     // counter for buffer array 
void setup()
{
  currentTime = millis();
  loopTime = currentTime;
  SoftSerial.begin(9600);               // the SoftSerial baud rate   
  Serial.begin(9600);             // the Serial port of Arduino baud rate.
 
}
 
void loop()
{
  if (SoftSerial.available())              // if date is comming from softwareserial port ==> data is comming from SoftSerial shield
  {
    while(SoftSerial.available())          // reading data into char array 
    {
      buffer[count++]=SoftSerial.read();     // writing data into array
      if(count == 64)break;
  }
    Serial.write(buffer,count);            // if no data transmission ends, write buffer to hardware serial port
    clearBufferArray();              // call clearBufferArray function to clear the storaged data from the array
    count = 0;                       // set counter of while loop to zero
 
  }
  currentTime = millis();
  while(currentTime >= (loopTime + 30000)){
    if (Serial.available()){
      buffer2[count++]=Serial.read();          // if data is available on hardwareserial port ==> data is comming from PC or notebook
      if(count == 4)break;
    }
    Serial.write(buffer2,count);
    clearBuffer2Array();
    count = 0;
  }
  
}

void clearBufferArray()              // function to clear buffer array
{
  for (int i=0; i<count;i++)
    { buffer[i]=NULL;}                  // clear all index of array with command NULL
}

void clearBuffer2Array()              // function to clear buffer array
{
  for (int i=0; i<count;i++)
    { buffer2[i]=NULL;}                  // clear all index of array with command NULL
}
