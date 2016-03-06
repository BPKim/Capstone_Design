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

#define SPEED 1

//// swtich
#define START 25 // 안
#define END 27

// uart
#define rxPin 11
// Digital Pin 3
#define txPin 10

uint32_t start = 0, endend = 0;
uint32_t _start = 1, _endend = 1;

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

boolean move_start = false;
boolean move_endend = false;
int turn = 0;
// 1 2 3 4 
// u d r l 

/// tongshin
SoftwareSerial mySerial(11, 10); // RX, TX



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
 
             delay(SPEED);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}

void left(){
           // right
            digitalWrite(X_DIR_PIN    , LOW);
            digitalWrite(Y_DIR_PIN    , LOW);

             digitalWrite(X_STEP_PIN    , HIGH);
             digitalWrite(Y_STEP_PIN    , HIGH);
 
             delay(SPEED);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}


void up()
{
     digitalWrite(X_DIR_PIN    , LOW);
   digitalWrite(Y_DIR_PIN , HIGH);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   delay(SPEED);
   
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
}


void down()
{
     digitalWrite(X_DIR_PIN    , HIGH);
   digitalWrite(Y_DIR_PIN , LOW);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   delay(SPEED);
   
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
         move_start = false;
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
 
 // enable
 digitalWrite(X_ENABLE_PIN    , LOW);
 digitalWrite(Y_ENABLE_PIN    , LOW);

  
 pinMode(START, INPUT_PULLUP);
 pinMode(END, INPUT_PULLUP);
 
  pinMode(53    , OUTPUT);
    pinMode(51    , OUTPUT);
         digitalWrite(53, HIGH);
    digitalWrite(51, HIGH);    
    
}
 
void loop () {
  
    if(!move_start)
      while(digitalRead(START));
    
    move_start=true;
    
    while(move_start){
        x_min = digitalRead(X_MIN_PIN);
  x_max = digitalRead(X_MAX_PIN);
  y_min = digitalRead(Y_MIN_PIN);
  y_max = digitalRead(Y_MAX_PIN);
  
  
 
      defualt_position();
    }

} 
/////
/*
  
  
  switch(turn) {
case 1: // up
    UP_step = true;
    DOWN_step = false;
    RIGHT_step = false;
    LEFT_step = false;
    break;
case 2: // down
    UP_step = false;
    DOWN_step = true;
    RIGHT_step = false;
    LEFT_step = false;
    break;
case 3: // right
    UP_step = false;
    DOWN_step = false;
    RIGHT_step = true;
    LEFT_step = false;
    break;
case 4: /// left
    UP_step = false;
    DOWN_step = false;
    RIGHT_step = false;
    LEFT_step = true;
    break;
case 0 : 
      UP_step = false;
      DOWN_step = false;
      RIGHT_step = false;
      LEFT_step = false;
      break;
}
*/

///////////////
/*
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
    }else if((UP_step ==false) && (DOWN_step==false) && (RIGHT_step == false) && (LEFT_step == false)){
      stop_step();
    }
    
    // max position min position
    
      if(y_min != y_tin)
    {
      Serial.print("Y min push!\n");
          turn= 2;

      y_tin = y_min;
      stop_y_step = true;
      
      //break;
    
    }else if(y_max != y_tax)
    {
      Serial.print("Y max push!\n");
          turn = 1;

      y_tax = y_max;
      stop_y_step = true;
      
     /// break;
    
    }
    
    // x min
    if(x_min != x_tin)
    {
      Serial.print("X min push!\n");
//      swSerial.write("X min push!\n");
  //    swSerial.available();
        turn = 4;

      x_tin = x_min;
      stop_x_step = true;
          
     // break;
    } else if(x_max != x_tax)
    {
      Serial.print("X max push!\n");
        turn = 3;
   
      x_tax = x_max;
      stop_x_step = true;
      
//break;
    
    }
*/
