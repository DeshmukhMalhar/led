#include <SPI.h>
#define 	LOAD 	10
#define 	MOSI 	11
#define 	MISO 	12
#define 	SCK  	13
//#define 	SERIAL_DEBUG
//#define USE_BLINKWITHOUTDELAY
#ifdef USE_BLINKWITHOUTDELAY
//for timing purposes
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 500;           // interval at which to blink (milliseconds)
#endif
void disp(uint8_t, uint8_t);
void setup() {
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A0, HIGH);
  digitalWrite(A2, LOW);

#ifdef SERIAL_DEBUG
  Serial.begin(9600);
  Serial.println("HEllo");
#endif
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV2);

  pinMode(LOAD, OUTPUT);
  pinMode(MOSI, OUTPUT);
  pinMode(SCK, OUTPUT);
  pinMode(MISO, INPUT);

  digitalWrite(LOAD, HIGH);
//  Serial.begin(9600);
}
uint8_t dg[] {
  0b00111111,//0
  0b00000110,//1
  0b01011011,//2
  0b01001111,//3
  0b01100110,//4
  0b01101101,//5
  0b01111101,//6
  0b00000111,//7
  0b01111111,//8
  0b01101111,//9
  //pgfedbca
};
int dataArray[] = {0, 0, 0, 0};
void dataToArray(double data)
{
  long temp = data;
  long temp1 = data;
  for (int i = 2; i >= 0; i--) {
    temp = temp1;
    temp /= pow(10, i);
    dataArray[2 - i] = temp;
    //    Serial.print(temp1);
    //    Serial.print(" ");
    //Serial.println(long(ceil(pow(10,i))));
    temp1 %= (long)ceil(pow(10, i));

  }
  //  Serial.print(data);
  //  Serial.print(" ");
  //  Serial.println(floor(data));
  //  Serial.print(data);
  dataArray[3] = int(data*10)%10;
  //  Serial.println(dataArray[3]);
}
int counter = 0;
int data;
uint16_t selector = 1;
void loop() {
  //  Serial.println(selector);
  disp(dataArray[counter], selector); //0b10000000
  selector <<= 1;
  counter++;
  counter %= 4;
  
  selector %= 255;
  data = analogRead(A1);
//  Serial.println(data);
  dataToArray(analogRead(A1));
  delay(1);
}
void disp(uint8_t digit = 0, uint8_t place = 0) {
  digitalWrite(LOAD, LOW);
  SPI.setBitOrder(MSBFIRST);
  SPI.transfer(place);//transfer place
  SPI.transfer(dg[digit]);//transfer digit
  digitalWrite(LOAD, HIGH);
  	digitalWrite(5,LOW);
  	SPI.transfer(0);
  	SPI.transfer(0);
  	digitalWrite(5,HIGH);
}
