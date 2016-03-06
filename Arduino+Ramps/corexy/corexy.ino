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


uint32_t curVal, lastVal = 1;

uint32_t x_min = 0, x_max = 0, y_min = 0, y_max = 0;
uint32_t x_tin = 1, x_tax = 1, y_tin = 1, y_tax = 1;

boolean stop_y_step = false;
boolean stop_x_step = false;
boolean turn_di = false;


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
 
             delay(1);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}

void left(){
           // right
            digitalWrite(X_DIR_PIN    , LOW);
            digitalWrite(Y_DIR_PIN    , LOW);

             digitalWrite(X_STEP_PIN    , HIGH);
             digitalWrite(Y_STEP_PIN    , HIGH);
 
             delay(1);
 
             digitalWrite(X_STEP_PIN    , LOW);
             digitalWrite(Y_STEP_PIN    , LOW);
}


void up()
{
     digitalWrite(X_DIR_PIN    , LOW);
   digitalWrite(Y_DIR_PIN , HIGH);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   delay(1);
   
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
}


void down()
{
     digitalWrite(X_DIR_PIN    , HIGH);
   digitalWrite(Y_DIR_PIN , LOW);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);

   delay(1);
   
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
 
 // enable
 digitalWrite(X_ENABLE_PIN    , LOW);
 digitalWrite(Y_ENABLE_PIN    , LOW);

}
 
void loop () {

  x_min = digitalRead(X_MIN_PIN);
  x_max = digitalRead(X_MAX_PIN);
  y_min = digitalRead(Y_MIN_PIN);
  y_max = digitalRead(Y_MAX_PIN);
  
  // defualt_position
   defualt_position();

} 
  /*
  if (millis() %1000 <500) 
    digitalWrite(LED_PIN, HIGH);
   else
    digitalWrite(LED_PIN, LOW);
  
  if(millis() <35000){
  
    if(x_min != x_tin || x_max != x_tax || y_min != y_tin || y_max != y_tax){
      if(x_min != x_tin)
      {
         Serial.print("X min push!\n");
          x_tin = x_min;
          // right
          // right
          digitalWrite(X_DIR_PIN    , HIGH);
          digitalWrite(Y_DIR_PIN    , HIGH);

          digitalWrite(X_STEP_PIN    , HIGH);
          digitalWrite(Y_STEP_PIN    , HIGH);
     
          delay(1);
 
          digitalWrite(X_STEP_PIN    , LOW);
          digitalWrite(Y_STEP_PIN    , LOW);
    }
    else if(x_max != x_tax)
    {
        Serial.print("X max push!\n");
        x_tax = x_max;
      
      // left
       // left
        digitalWrite(X_DIR_PIN    , LOW);
        digitalWrite(Y_DIR_PIN    , LOW);

        digitalWrite(X_STEP_PIN    , HIGH);
        digitalWrite(Y_STEP_PIN    , HIGH);
     //Serial.println("f");
 
        delay(1);
 
        digitalWrite(X_STEP_PIN    , LOW);
        digitalWrite(Y_STEP_PIN    , LOW);
    }
    else if(y_min != y_tin)
    {
        Serial.print("Y min push!\n");
        y_tin = y_min;
      //up
      // up
        digitalWrite(X_DIR_PIN    , LOW);
        digitalWrite(Y_DIR_PIN    , HIGH);

       digitalWrite(X_STEP_PIN    , HIGH);
       digitalWrite(Y_STEP_PIN    , HIGH);
 
       delay(1);
 
       digitalWrite(X_STEP_PIN    , LOW);
       digitalWrite(Y_STEP_PIN    , LOW);
   
    }
    else if(y_max != y_tax)
    {
        Serial.print("Y max push!\n");
        y_tax = y_max;
        // down
        // down
      digitalWrite(X_DIR_PIN    , HIGH);
      digitalWrite(Y_DIR_PIN    , LOW);

       digitalWrite(X_STEP_PIN    , HIGH);
       digitalWrite(Y_STEP_PIN    , HIGH);
     //Serial.println("f");
 
       delay(1);
 
       digitalWrite(X_STEP_PIN    , LOW);
       digitalWrite(Y_STEP_PIN    , LOW);
      }
    }
  }
  */
   
    /*
 if (millis() %1000 <500) 
   digitalWrite(LED_PIN, HIGH);
 else
  digitalWrite(LED_PIN, LOW);
 
// if (millis() %10000 < 2500) {
if(millis() <35000){
//   Serial.println(millis() %10000);
   // up
   
   //digitalWrite(X_DIR_PIN    , LOW);
   //digitalWrite(Y_DIR_PIN    , HIGH);
   
   // left
  digitalWrite(X_DIR_PIN    , HIGH);
  digitalWrite(Y_DIR_PIN    , HIGH);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);
     //Serial.println("f");
 
 delay(1);
 
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
   
  
 }
 
// else if (millis() %10000 <5000 && millis() %10000 >=2500){
   
 }
 //else if (millis() %10000 <7500 && millis() %10000 >=5000){
 }
 //else{
 }
 
  else if(millis() >=35000 && millis()<500000){
  
  //  left
  digitalWrite(X_DIR_PIN    , HIGH);
  digitalWrite(Y_DIR_PIN    , HIGH);
  
   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);
     //Serial.println("f");
 
   delay(1);
 
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);

  }
  else if(millis()>=50000){ 
  }
  else{
  }
  */


/*

// up
  digitalWrite(X_DIR_PIN    , LOW);
  digitalWrite(Y_DIR_PIN    , HIGHT);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);
     //Serial.println("f");
 
 delay(1);
 
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
   
//////////////////////////////////////////

// down
  digitalWrite(X_DIR_PIN    , HIGH);
  digitalWrite(Y_DIR_PIN    , LOW);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);
     //Serial.println("f");
 
 delay(1);
 
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
   

/////////////////////////////////
   // right
  digitalWrite(X_DIR_PIN    , HIGH);
  digitalWrite(Y_DIR_PIN    , HIGH);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);
     //Serial.println("f");
 
 delay(1);
 
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
   
///////////////////////////////////

   // left
  digitalWrite(X_DIR_PIN    , LOW);
  digitalWrite(Y_DIR_PIN    , LOW);

   digitalWrite(X_STEP_PIN    , HIGH);
   digitalWrite(Y_STEP_PIN    , HIGH);
     //Serial.println("f");
 
 delay(1);
 
   digitalWrite(X_STEP_PIN    , LOW);
   digitalWrite(Y_STEP_PIN    , LOW);
*/
