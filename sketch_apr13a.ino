

#define Pot1 A0
#define Pot2 A1

unsigned char sendbuf[]={0x7E,0xFF,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0xEF};

int mode=0;

void setup () {
	Serial.begin (9600);
  pinMode(Pot1,INPUT_PULLUP);
  pinMode(Pot2,OUTPUT);
  digitalWrite(Pot2,0);
        delay (200);
        mp3_set_volume (30);
        delay(1);         
//        mp3play(1);      
//        delay (2000);

}

void loop () { 
  int PotBuffer1 = analogRead(Pot1);  //读取AD值
 // Serial.println( PotBuffer1);
  if(PotBuffer1<900)
  {
      mp3play(1); 
      delay (1000);
  }
  delay(100); 
}

 void sendfunc () {
	for (int i=0; i<10; i++) {
		Serial.write (sendbuf[i]);
	}
}
 uint16_t mp3getchecksum (uint8_t *thebuf)
 {
	uint16_t sum = 0;
	for (int i=1; i<7; i++) {
		sum += thebuf[i];
	}
	return -sum;
}
 void mp3fillchecksum () {
	uint16_t checksum = mp3getchecksum (sendbuf);
	filluint16bigend (sendbuf+7, checksum);
}
 void filluint16bigend (uint8_t *thebuf, uint16_t data) {
	*thebuf =	(uint8_t)(data>>8);
	*(thebuf+1) =	(uint8_t)data;
}
void mp3sendcmd (uint8_t cmd, uint16_t arg) {
	sendbuf[3] = cmd;
	filluint16bigend ((sendbuf+5), arg);
	mp3fillchecksum ();
	sendfunc ();
}
 void mp3play(uint16_t num) {
	mp3sendcmd (0x12, num);
}
void mp3_set_volume (uint16_t volume) {
  mp3sendcmd (0x06, volume);
}
