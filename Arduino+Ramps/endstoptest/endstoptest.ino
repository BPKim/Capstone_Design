// xmin 3 xmax 2 ymin 16 ymax 17
int xMinPin = 3;
int xMaxPin = 2;
int yMinPin = 14;
int yMaxPin = 15;

uint32_t curVal, lastVal = 1;

uint32_t x_min = 0, x_max = 0, y_min = 0, y_max = 0;
uint32_t x_tin = 1, x_tax = 1, y_tin = 1, y_tax = 1;
String str;

void setup() {
  pinMode(xMinPin, INPUT_PULLUP);
  pinMode(xMaxPin, INPUT_PULLUP);
  pinMode(yMinPin, INPUT_PULLUP);
  pinMode(yMaxPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  
  x_min = digitalRead(xMinPin);
  x_max = digitalRead(xMaxPin);
  y_min = digitalRead(yMinPin);
  y_max = digitalRead(yMaxPin);
/*
  curVal = digitalRead(xMinPin);

  if (curVal != lastVal) {
    Serial.print("Different! curVal = ");
    Serial.print(curVal);
    Serial.print(" lastVal: ");
    Serial.print(lastVal);
    Serial.print("\n");
    }
    
    lastVal = curVal;
    */
  if(x_min != x_tin || x_max != x_tax || y_min != y_tin || y_max != y_tax){
    if(x_min != x_tin)
    {
      Serial.print("X min push!\n");
      x_tin = x_min;
    }
    else if(x_max != x_tax)
    {
      Serial.print("X max push!\n");
      x_tax = x_max;
    }
    else if(y_min != y_tin)
    {
      Serial.print("Y min push!\n");
      y_tin = y_min;
    }
    else if(y_max != y_tax)
    {
      Serial.print("Y max push!\n");
      y_tax = y_max;
    }
    
  }
    
}
