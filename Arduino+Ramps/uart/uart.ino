/*
 아두이노와 라즈베리 파이의 UART 연결
 아두이노 : SoftSerial
 라즈베리파이 : GPIO UART
*/
 
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(11, 10); // RX, TX
//SoftwareSerial mySerial(3, 2); // RX, TX
//SoftwareSerial mySerial(12, 13); // RX, TX

 
void setup()  
{
  Serial.begin(9600);
  Serial.println("Start UART test");  // PC의 시리얼 모니터에 표시합니다.
  mySerial.begin(9600); //소프트 시리얼로 라즈베리 파이와 통신하게 됩니다.
  
    pinMode(53    , OUTPUT);
    pinMode(51    , OUTPUT);
    digitalWrite(53, HIGH);
    digitalWrite(51, HIGH);   
    
}
 
void loop() {
  
  if(mySerial.available()){
    
    Serial.write(mySerial.read());
    
    digitalWrite(53, HIGH);     // RED
    digitalWrite(51, LOW);      //GREEN
    delay(5);
  }
  if(Serial.available()){
    mySerial.write(Serial.read());
    
    digitalWrite(53, LOW);     // RED
    digitalWrite(51, HIGH);      //GREEN
        delay(5);

  }

}
  /*
  // 라즈베리 파이에서 넘어온 데이터가 있으면 PC로 넘겨줍니다.
  if (mySerial.available()){
    Serial.write(mySerial.read());
        digitalWrite(53, HIGH);     // RED
    digitalWrite(51, LOW);      //GREEN
  }
  // PC에서 넘어온 데이터가 있으면 라즈베리파이로 넘겨줍니다.
  if (Serial.available()){
    mySerial.write(Serial.read());
        digitalWrite(53, LOW);     // RED
    digitalWrite(51, HIGH);      //GREEN
  }
    */
