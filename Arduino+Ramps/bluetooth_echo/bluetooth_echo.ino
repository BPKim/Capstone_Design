#include <SoftwareSerial.h>
#include <mthread.h>

// Digital Pin 2
//#define rxPin 19
#define rxPin 10
// Digital Pin 3
#define txPin 11
//#define txPin 18
// 내장 LED
//#define ledPin 13 


// 데이터(문자열)을 받을 버퍼의 크기.
#define BUFF_SIZE 256 

SoftwareSerial swSerial(txPin, rxPin);

// 데이터 버퍼
uint8_t buffer[BUFF_SIZE];
uint8_t index = 0;
uint8_t data;

class FooThread : public Thread
{
public:
    FooThread(int id);
protected:
    bool loop();
private:
    int id;
};
 
FooThread::FooThread(int id)
{
    this->id = id;
}
 
bool FooThread::loop()
{
 
    // Die if requested:
    if(kill_flag)
        return false;
 
    // Print the status message:
    Serial.print("FooThread ");
    Serial.print(id);
    Serial.println(" called.");
 
    // Sleep for one second:
    sleep(1);
    return true;
 
}

void setup() {
  swSerial.begin(9600);
//  pinMode(ledPin, OUTPUT);
}

void loop() {
//  digitalWrite(ledPin, LOW);
  // 데이터가 들어올때 까지 대기.
  while(!swSerial.available());
  //digitalWrite(ledPin, HIGH);
  while(swSerial.available()) {
    data = swSerial.read();
    buffer[index++] = data;
    // 버퍼가 꽉 찼거나 문자열이 끝났을 때,
    // 루프에서 나간다.
    if(index == BUFF_SIZE || data == '\0') break;
    // 9600bps 기준으로 delay 를 1ms 을 줘야 한다.
    delay(1);
  }   
  // 블루투스를 통하여 받은 데이터를 되돌려준다.
  for(uint8_t i = 0; i < index; ++i) {
    swSerial.write(buffer[i]);
  }
  index = 0;
}
