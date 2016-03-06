#include <SoftwareSerial.h>
/*
#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38*/
#define X_STEP_PIN 46
#define X_DIR_PIN 48
#define X_ENABLE_PIN 62
#define X_MIN_PIN 3
#define X_MAX_PIN 2

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56
#define Y_MIN_PIN 14
#define Y_MAX_PIN 15
/*
#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN 62*/

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

#define SPEED 1000

// Digital Pin 2
//#define rxPin 19
#define rxPin 11
// Digital Pin 3
#define txPin 10
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
int inputdata;



uint32_t curVal, lastVal = 1;

uint32_t x_min = 0, x_max = 0, y_min = 0, y_max = 0;
uint32_t x_tin = 1, x_tax = 1, y_tin = 1, y_tax = 1;

boolean stop_y_step = false;
boolean stop_x_step = false;
boolean turn_di = false;


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
 
   delayMicroseconds(SPEED);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}

void left(){
           // right
            digitalWrite(X_DIR_PIN    , LOW);
            digitalWrite(Y_DIR_PIN    , LOW);

             digitalWrite(X_STEP_PIN    , HIGH);
             digitalWrite(Y_STEP_PIN    , HIGH);
 
   delayMicroseconds(SPEED);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}


void up()
{
     digitalWrite(X_DIR_PIN    , LOW);
   digitalWrite(Y_DIR_PIN , HIGH);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   delayMicroseconds(SPEED);
   
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
}


void down()
{
     digitalWrite(X_DIR_PIN    , HIGH);
   digitalWrite(Y_DIR_PIN , LOW);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   delayMicroseconds(SPEED);
   
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
  if(x_min != x_tax)
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
 // enable
 digitalWrite(X_ENABLE_PIN    , LOW);
 digitalWrite(Y_ENABLE_PIN    , LOW);
 
   swSerial.begin(9600);


}
 
void loop () {
  
  //  digitalWrite(ledPin, LOW);
  // 데이터가 들어올때 까지 대기.
  while(!swSerial.available()){
        
    
    // end stop switch init
  x_min = digitalRead(X_MIN_PIN);
  x_max = digitalRead(X_MAX_PIN);
  y_min = digitalRead(Y_MIN_PIN);
  y_max = digitalRead(Y_MAX_PIN);
  
  
    if((UP_step ==true) && (DOWN_step==false) && (RIGHT_step == false) && (LEFT_step == false)){
      enable_step();
      up();
    }
    else if((UP_step ==false) && (DOWN_step==true) && (RIGHT_step == false) && (LEFT_step == false)){
      enable_step();
      down();
    }
    else if((UP_step ==false) && (DOWN_step==false) && (RIGHT_step == true) && (LEFT_step == false)){
      enable_step();
      right();
    }
    else if((UP_step ==false) && (DOWN_step==false) && (RIGHT_step == false) && (LEFT_step == true)){
      enable_step();
      left();
    }else if((UP_step ==false) && (DOWN_step==false) && (RIGHT_step == false) && (LEFT_step == false))
    {
      stop_step();
    }
    
    // max position min position
    
      if(y_min != y_tin)
    {
      Serial.print("Y min push!\n");
          buffer[0] = 'd';
      buffer[1]='\0' ;
      y_tin = y_min;
      stop_y_step = true;
      
      break;
    
    }else if(y_max != y_tax)
    {
      Serial.print("Y max push!\n");
          buffer[0] = 'u';
    buffer[1]='\0' ;
      y_tax = y_max;
      stop_y_step = true;
      
      break;
    
    }
    
    // x min
    if(x_min != x_tin)
    {
      Serial.print("X min push!\n");
//      swSerial.write("X min push!\n");
  //    swSerial.available();
    buffer[0] = 'l';
    buffer[1]='\0' ; 
      x_tin = x_min;
      stop_x_step = true;
          
      break;
    } else if(x_max != x_tax)
    {
      Serial.print("X max push!\n");
    buffer[0] = 'r';
    buffer[1]='\0' ;
    
      x_tax = x_max;
      stop_x_step = true;
      
    break;
    
    }
    
  }
  while(swSerial.available()) {
//    data = swSerial.read();
//  inputdata  = swSerial.read();
  
    buffer[index++] = swSerial.read();

    // 버퍼가 꽉 찼거나 문자열이 끝났을 때,
    // 루프에서 나간다.
    if(index == BUFF_SIZE || data == '\0') break;
    // 9600bps 기준으로 delay 를 1ms 을 줘야 한다.
    delay(1);
  } 


  // 블루투스를 통하여 받은 데이터를 되돌려준다.
/*  for(uint8_t i = 0; i < index; ++i) {
    swSerial.write(buffer[i]);
  }
  index = 0;
*/
  send_message();
  
  if(buffer[0]=='u') // up
  {

    UP_step = true;
    DOWN_step = false;
    RIGHT_step = false;
    LEFT_step = false;
    
  }    
  else if(buffer[0]=='d') // down
  {
  //    digitalWrite(53, HIGH);

    UP_step = false;
    DOWN_step = true;
    RIGHT_step = false;
    LEFT_step = false;
    
  }    
    else if(buffer[0]=='r') // right
  {
  //    digitalWrite(53, HIGH);

    UP_step = false;
    DOWN_step = false;
    RIGHT_step = true;
    LEFT_step = false;

  }    
    else if(buffer[0]=='l') // up
  {
//      digitalWrite(53, HIGH);

    UP_step = false;
    DOWN_step = false;
    RIGHT_step = false;
    LEFT_step = true;

  }else if(buffer[0]=='s')
  {
      UP_step = false;
      DOWN_step = false;
      RIGHT_step = false;
      LEFT_step = false;
  }  
  // defualt_position
  // defualt_position();

} 
