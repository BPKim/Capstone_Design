#include <SoftwareSerial.h>

#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38
#define X_MIN_PIN 3
#define X_MAX_PIN 2

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56
#define Y_MIN_PIN 14
#define Y_MAX_PIN 15

#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62
#define Z_MIN_PIN 18
#define Z_MAX_PIN 19

#define E_STEP_PIN 26
#define E_DIR_PIN 28
#define E_ENABLE_PIN 24
#define Q_STEP_PIN 36
#define Q_DIR_PIN 34
#define Q_ENABLE_PIN 30

#define SDPOWER -1
#define SDSS 53
#define LED_PIN 13
#define FAN_PIN 9
#define PS_ON_PIN 12
#define KILL_PIN -1


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
int inputdata;



uint32_t curVal, lastVal = 1;

uint32_t x_min = 0, x_max = 0, y_min = 0, y_max = 0;
uint32_t x_tin = 1, x_tax = 1, y_tin = 1, y_tax = 1;

boolean stop_y_step = false;
boolean stop_x_step = false;
boolean turn_di = false;

int go_default = 0;

boolean UP_step = false;
boolean DOWN_step = false;
boolean RIGHT_step = false;
boolean LEFT_step = false;
boolean turn_turn = false;

// BT
void send_message(){
    for(uint8_t i = 0; i < index; ++i) {
    swSerial.write(buffer[i]);
  }
  index = 0;
}

/// step control 
void stop_step()
{
          // stop   
         digitalWrite(X_ENABLE_PIN, HIGH);
         digitalWrite(Y_ENABLE_PIN, HIGH);
}

void enable_step()
{
          // enable   
         digitalWrite(X_ENABLE_PIN, LOW);
         digitalWrite(Y_ENABLE_PIN, LOW);
}

void right(){
           // right
            digitalWrite(X_DIR_PIN    , HIGH);
            digitalWrite(Y_DIR_PIN    , HIGH);

             digitalWrite(X_STEP_PIN    , HIGH);
             digitalWrite(Y_STEP_PIN    , HIGH);
 
             //delay(1);
                     delayMicroseconds(50);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}

void left(){
           // right
            digitalWrite(X_DIR_PIN    , LOW);
            digitalWrite(Y_DIR_PIN    , LOW);

             digitalWrite(X_STEP_PIN    , HIGH);
             digitalWrite(Y_STEP_PIN    , HIGH);
 
            // delay(1);
                    delayMicroseconds(50);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}


void up()
{
     digitalWrite(X_DIR_PIN    , LOW);
   digitalWrite(Y_DIR_PIN , HIGH);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   //delay(1);
           delayMicroseconds(50);
   
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
}


void down()
{
     digitalWrite(X_DIR_PIN    , HIGH);
   digitalWrite(Y_DIR_PIN , LOW);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   //delay(1);
   delayMicroseconds(50);
   
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
}

void defualt_position(){
    // 맨
  if(y_min != y_tin)
    {
      Serial.print("Y min push!\n");
      //BTSerial.write("Y min push!\n");
      y_tin = y_min;
      stop_y_step = true;
    }
    //맨 올
  if(x_min != x_tin)
    {
      Serial.print("X min push!\n");
            //BTSerial.write("X min push!\n");

      x_tin = x_min;
      stop_x_step = true;
    }
    
    if(!stop_y_step){
      // up
       up();
   
    }else
    {
      // 잠깐멈춤
      if(!turn_di)
      {
        stop_step();
        turn_di=true;
        delay(1);
        enable_step();
      }
      
      if(!stop_x_step){
        right();

      }else
      {
         stop_step();
         //////////
         go_default=3;
      }
      
    }
}

void setup() {
  
  // end stop switch setup
  pinMode(X_MIN_PIN, INPUT_PULLUP);
  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MIN_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  
  Serial.begin(9600);
 // BTSerial.begin(9600);
 //BTSerial.begin(9600);
  x_min = digitalRead(X_MIN_PIN);
  x_max = digitalRead(X_MAX_PIN);
  y_min = digitalRead(Y_MIN_PIN);
  y_max = digitalRead(Y_MAX_PIN);
  // end stop switch setup end
  
 pinMode(LED_PIN  , OUTPUT);
 
 pinMode(X_STEP_PIN  , OUTPUT);
 pinMode(X_DIR_PIN    , OUTPUT);
 pinMode(X_ENABLE_PIN    , OUTPUT);
 
 pinMode(Y_STEP_PIN  , OUTPUT);
 pinMode(Y_DIR_PIN    , OUTPUT);
 pinMode(Y_ENABLE_PIN    , OUTPUT);
 
 pinMode(53    , OUTPUT);
   digitalWrite(53, LOW);
    pinMode(51    , OUTPUT);
   digitalWrite(51, LOW);
 // enable
 digitalWrite(X_ENABLE_PIN    , LOW);
 digitalWrite(Y_ENABLE_PIN    , LOW);
 
   swSerial.begin(9600);


}
 
void loop () {

    x_min = digitalRead(X_MIN_PIN);
    x_max = digitalRead(X_MAX_PIN);
    y_min = digitalRead(Y_MIN_PIN);
    y_max = digitalRead(Y_MAX_PIN);
   
  //  digitalWrite(ledPin, LOW);
  // 데이터가 들어올때 까지 대기.
  // go to default position
  if(go_default==1){

    digitalWrite(53, LOW);
    digitalWrite(51, HIGH);      


    // 맨
  if(y_min != y_tin)
    {
      Serial.print("Y min push!\n");
      //BTSerial.write("Y min push!\n");
      y_tin = y_min;
      stop_y_step = true;
    }
    //맨 올
  if(x_min != x_tin)
    {
      Serial.print("X min push!\n");
            //BTSerial.write("X min push!\n");

      x_tin = x_min;
      stop_x_step = true;
    }
    
    if(!stop_y_step){
      // up
       up();
   
    }else
    {
      // 잠깐멈춤
      if(!turn_di)
      {
        stop_step();
        turn_di=true;
        delay(1);
        enable_step();
      }
      
      if(!stop_x_step){
        right();

      }else
      {
         stop_step();
         //////////
         go_default=0;
         buffer[0]='f';
         buffer[1]='\0';
          // 블루투스를 통하여 받은 데이터를 되돌려준다.
  for(uint8_t i = 0; i < index; ++i) {
    swSerial.write(buffer[i]);
  }
  index = 0;
  
      }
      
    }
    
  }
/*  else if(go_default==0){
    while( !swSerial.available()){
       digitalWrite(53, HIGH);
       digitalWrite(51, HIGH);           
    }
    
      while(swSerial.available()) {
    data = swSerial.read();
//  inputdata  = swSerial.read();
  
    buffer[index++] = data;

    // 버퍼가 꽉 찼거나 문자열이 끝났을 때,
    // 루프에서 나간다.
    if(index == BUFF_SIZE || data == '\0') break;
    // 9600bps 기준으로 delay 를 1ms 을 줘야 한다.
    
  } 

  }
*/
  if(swSerial.available()) {
    byte data = swSerial.read();
//  inputdata  =  swSerial.read();
  
    buffer[index++] = data;

      swSerial.write(buffer, index);
    // 버퍼가 꽉 찼거나 문자열이 끝났을 때,
    // 루프에서 나간다.
    if(index == BUFF_SIZE || data == '\n') 
    {
      buffer[index] = '\0';

      // 스마트폰으로 문자열 전송
//      swSerial.write(buffer, index);
      index = 0;
    }  
    delay(1);
    
  } 
/*
  // 블루투스를 통하여 받은 데이터를 되돌려준다.
  for(uint8_t i = 0; i < index; ++i) {
    swSerial.write(buffer[i]);
  }
  
  */
  
  if(buffer[0]=='g'){
      go_default=1;
       digitalWrite(53, LOW);
       digitalWrite(51, HIGH);      
      delay(10);
  }
  // defualt_position
  // defualt_position();

} 
