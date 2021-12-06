

#include <SoftwareSerial.h>
#include "DFPlayer_Mini_Mp3.h"
#define Pot1 A0
#define Pot2 A1
SoftwareSerial mySerial(2, 3); // RX, TX

//
void setup () {
  pinMode(Pot1,INPUT_PULLUP);
  pinMode(Pot2,OUTPUT);
  digitalWrite(Pot2,0);
	Serial.begin (9600);
	mySerial.begin (9600);
  delay(100);
	mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
	delay(1);  //wait 1ms for mp3 module to set volume
	mp3_set_volume (30);
  delay(100); 
  mp3_play (1);
  delay (6000);
  mp3_stop (); 
}

void loop () {        

  int PotBuffer1 = analogRead(Pot1);  //读取AD值
  Serial.println( PotBuffer1);
  if(PotBuffer1<900)
  {
      mp3_play (1);
      delay (16000);
  }
  else
  {
      mp3_stop ();     
  }
  delay(100); 
}
