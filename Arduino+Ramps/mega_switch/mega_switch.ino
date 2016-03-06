#define START 25 // 안
#define END 27

uint32_t start = 0, endend = 0;
uint32_t _start = 1, _endend = 1;

void setup() {
  
 pinMode(START, INPUT_PULLUP);
 pinMode(END, INPUT_PULLUP);
 
  pinMode(53    , OUTPUT);
    pinMode(51    , OUTPUT);
         digitalWrite(53, HIGH);
    digitalWrite(51, HIGH);    
}

void loop () {
  
  start = digitalRead(START);
  endend = digitalRead(END)
 
  if(digitalRead(START) == LOW)
    {
    digitalWrite(53, LOW);
    digitalWrite(51, HIGH);      
    
    }
  //맨 올
  if(digitalRead(END) == LOW)
    {
    digitalWrite(53, HIGH);     // RED
    digitalWrite(51, LOW);      //GREEN

    }
}
