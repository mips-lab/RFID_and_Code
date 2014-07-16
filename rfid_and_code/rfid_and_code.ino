#include <Keypad.h>
#include <SoftwareSerial.h>
 
SoftwareSerial SoftSerial(12, 13);
unsigned char buffer[64]; // buffer array for data recieve over serial port
unsigned char buffer2[4];
unsigned long currentTime;
unsigned long loopTime;
int count=0;     // counter for buffer array 
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
char RFID;

void setup()
{
	currentTime = millis();
	loopTime = currentTime;
	SoftSerial.begin(9600);               // the SoftSerial baud rate   
	Serial.begin(9600);             // the Serial port of Arduino baud rate.
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

 
void loop()
{
	if (SoftSerial.available())              // if date is comming from softwareserial port ==> data is comming from SoftSerial shiel
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
	while(currentTime >= (loopTime + 30000))
	{
	if (Serial.available())
	{
		buffer2[count++]=Serial.read();          // if data is available on hardwareserial port ==> data is comming from PC or notebook
		if(count == 4)break;
	}
//	Serial.write(buffer2,count);
	RFID = (buffer2,count);
    clearBuffer2Array();
    count = 0;
	}
	if (RFID) {
		int i;
		char key[3];
		for (i = 0; i < 4; i = i + 1) {
			key[i] = keypad.waitForKey();
		}
		Serial.println(String(RFID).length() + "&" + String(key));
	}
}