#include <SoftwareSerial.h>
 
SoftwareSerial shotSerial(11, 10); // RX, TX

/*
#define X_STEP_PIN 54
#define X_DIR_PIN 55
#define X_ENABLE_PIN 38*/
#define X_STEP_PIN 46
#define X_DIR_PIN 48
#define X_ENABLE_PIN 62

/* 원래 min max // 지금 반전
#define X_MIN_PIN 3
#define X_MAX_PIN 2
*/
#define X_MIN_PIN 2
#define X_MAX_PIN 3

#define Y_STEP_PIN 60
#define Y_DIR_PIN 61
#define Y_ENABLE_PIN 56

/* 상동
#define Y_MIN_PIN 14
#define Y_MAX_PIN 15
*/
#define Y_MIN_PIN 15
#define Y_MAX_PIN 14

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

#define SPEED 100 //400
#define SPEED2 50 //300
#define SHOTSHOT 1000

//// swtich
#define NORMAL 25 // 안
#define FAST 27

// uart
#define rxPin 11
// Digital Pin 3
#define txPin 10


uint32_t curVal, lastVal = 1;

uint32_t x_min = 0, x_max = 0, y_min = 0, y_max = 0;
uint32_t x_tin = 1, x_tax = 1, y_tin = 1, y_tax = 1;

uint32_t mornal = 0, fast = 0;
uint32_t _mornal = 1, _fast = 1;
uint32_t button_n = 0;

boolean goUp = true;
boolean turn_di = false;

boolean move_start = false;
boolean move_endend = false;

boolean default_endend = false;
boolean default_start = false;

//boolean goLeft = true;

int endendend = 0;

boolean mode = true; //true mornal false fast
/// tongshin

long goLeft =0;

boolean UP_step = false;
boolean DOWN_step = true;
boolean RIGHT_step = false;
boolean LEFT_step = false;
boolean turn_turn = false;


boolean endflag = false;

void init_flag(){
  goUp = true;
  turn_di = false;

  move_start = false;
  move_endend = false;

  default_endend = false;
  default_start = false;

//boolean goLeft = true;

  endendend = 0;

  mode = true; 
/// tongshin

  goLeft =0;

  UP_step = false;
  DOWN_step = true;
  RIGHT_step = false;
  LEFT_step = false;
  turn_turn = false;
  
  endflag = false;
 
}


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

void left(){ // bef right
           // right
            digitalWrite(X_DIR_PIN    , HIGH);
            digitalWrite(Y_DIR_PIN    , HIGH);

             digitalWrite(X_STEP_PIN    , HIGH);
             digitalWrite(Y_STEP_PIN    , HIGH);
 
             //delay(SPEED);
             delayMicroseconds(SPEED);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}

void right(){
           // right
            digitalWrite(X_DIR_PIN    , LOW);
            digitalWrite(Y_DIR_PIN    , LOW);

             digitalWrite(X_STEP_PIN    , HIGH);
             digitalWrite(Y_STEP_PIN    , HIGH);
 
             //delay(SPEED);
             delayMicroseconds(SPEED);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}


void down() // bef up
{
     digitalWrite(X_DIR_PIN    , LOW);
   digitalWrite(Y_DIR_PIN , HIGH);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   //delay(SPEED2);
   delayMicroseconds(SPEED2);
   
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
}


void up()
{
     digitalWrite(X_DIR_PIN    , HIGH);
   digitalWrite(Y_DIR_PIN , LOW);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   //delay(SPEED2);
   delayMicroseconds(SPEED2);
   
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
}

void setup() {
  
  // end stop switch setup
  pinMode(X_MIN_PIN, INPUT_PULLUP);
  pinMode(X_MAX_PIN, INPUT_PULLUP);
  pinMode(Y_MIN_PIN, INPUT_PULLUP);
  pinMode(Y_MAX_PIN, INPUT_PULLUP);
  
  Serial.begin(9600);
  shotSerial.begin(9600); //소프트 시리얼로 라즈베리 파이와 통신하게 됩니다.

  //x_min = digitalRead(X_MIN_PIN);
  //x_max = digitalRead(X_MAX_PIN);
  //y_min = digitalRead(Y_MIN_PIN);
  //y_max = digitalRead(Y_MAX_PIN);
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

  
 pinMode(NORMAL, INPUT_PULLUP);
 pinMode(FAST, INPUT_PULLUP);
 
  pinMode(53    , OUTPUT);
    pinMode(51    , OUTPUT);
  
    
    
}
 
void loop () {

    ////////////////////////////////////// switch wait
  if((!default_start)&&(!default_endend)){
      Serial.println("Default Wait");  // PC의 시리얼 모니터에 표시합니다.

    digitalWrite(53, HIGH); // RED
    digitalWrite(51, HIGH); //GREEN
      
    while(mornal=digitalRead(NORMAL)){}

    default_start = true;
    delay(1);
    
  }
  ////////////////////////////////////////// default position
    while(default_start){
      
    digitalWrite(53, HIGH); // RED
    digitalWrite(51, LOW); //GREEN
     
      x_min = digitalRead(X_MIN_PIN);
      x_max = digitalRead(X_MAX_PIN);
      y_min = digitalRead(Y_MIN_PIN);
      y_max = digitalRead(Y_MAX_PIN);

      while(!digitalRead(NORMAL)){} // green btn 눌렀을때 정지
      
      // up t
      if(y_min != y_tin){
        Serial.print("Y min push!\n");
        y_tin = y_min;
        goUp = false;
        while(goLeft<100){
         down();
         goLeft++;
        }
      goLeft=0;
      
      }
      // right t
      if(x_min != x_tin){
        Serial.print("X min push!\n");
        x_tin = x_min;
        default_start = false;
        default_endend = true;
          
      //while(goLeft<150){
      while(goLeft<400){
         left();
         goLeft++;
      }
      goLeft=0;
      
        stop_step();
        
      }
    
      if(goUp){
       up();
      }else{
        right();
      }     
    } 
  }////////////////////////// 기본 위치로 끝
  


  while(digitalRead(NORMAL) == HIGH ){}
      
   shotSerial.write('a'); //////shot
   delay(SHOTSHOT);
        
  while(mode)   
  {
            digitalWrite(53, LOW); // RED
          digitalWrite(51, HIGH); //GREEN
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


      while(!digitalRead(NORMAL)){
        endendend = 3 ;
        endflag = true;
      }
    

      if(y_min != y_tin)
      {
        Serial.print("Y min push!\n");
        //y_tin = y_min;

        Serial.print("y tin = ");
        Serial.print(y_tin);
        Serial.print("\n y min = ");
        Serial.print(y_min);

        while(goLeft<1000){
           down();
           goLeft++;
        }
        Serial.print("out of down \n");
        goLeft=0;
        /////////////////////////////////////////////////
//        delay(SHOTSHOT);
                shotSerial.write('a'); //////shot
        delay(SHOTSHOT);
        ///////////////////////////////////////
        while((goLeft<27600)&&((x_max = digitalRead(X_MAX_PIN))==HIGH)){
           left();
           goLeft++;
        }
        goLeft=0;
        ///////////////////////////////////////////////
                delay(SHOTSHOT);
        shotSerial.write('a'); //////shot
                delay(SHOTSHOT);
    /////////////////////////////////////////
        UP_step = false;
        DOWN_step = true;
        RIGHT_step = false;
        LEFT_step = false;
    
      }else if(y_max != y_tax){
            endendend++;
        Serial.print("Y max push!\n");
        Serial.print(endendend+" \n");

        Serial.print("y tax = ");
        Serial.print(y_tax);
        Serial.print("\n y max = ");
        Serial.print(y_max);
        
        //y_tax = y_max;

        if(y_max != y_tax){}

      /////
        while(goLeft<2500){
           up();
           goLeft++;
         
        }
        Serial.print("\n out of up \n");
        goLeft=0;
      ///////////////////////////////////////////////////
              //delay(SHOTSHOT);
              
        shotSerial.write('a'); //////shot
      
              delay(SHOTSHOT);
              //////////////////////////////////
        while(goLeft<28600&&((x_max = digitalRead(X_MAX_PIN))==HIGH)){
  
           left();
           goLeft++;

           while(!digitalRead(NORMAL)){
              endendend = 3 ;
              endflag = true;
           }
           
        }
        Serial.print("out of left ");
        Serial.print(goLeft);
        Serial.print(" ");
        Serial.print(y_min);
        Serial.print("\n");
        
        goLeft=0;
        ////////////////////////////////////////
         //       delay(SHOTSHOT);
        shotSerial.write('a'); //////shot

        delay(SHOTSHOT);
        ///////////////////////////////////////
        UP_step = true;
        DOWN_step = false;
        RIGHT_step = false;
        LEFT_step = false;
      }
    
      // x min
      if(x_min != x_tin){
        Serial.print("X min push!\n");
        x_tin = x_min;

      } else if(x_max != x_tax){
        Serial.print("X max push!\n");
      
        x_tax = x_max;
        endflag = true;
        
         while(goLeft<100){
           right();
           goLeft++;
        }
           goLeft=0;

      }

    
    //endend
    if(endendend > 2 )
    endflag = true;
          
    if(endflag){
        stop_step();
        enable_step();
        init_flag();   
        endflag = false;    
        break;        
    }
  }
//////
