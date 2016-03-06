#include <SoftwareSerial.h>

#define PIN_RX 2
#define PIN_TX 3


SoftwareSerial gSoftSerial(PIN_TX, PIN_RX);

const char* gMenu = "HC-06 Settings.\n1) name\n2) pin\n3) baud rate\n4) Version\n";
const char* gMenuBaud = "1) 1200\n2) 2400\n3) 4800\n4) 9600\n5) 19200\n6) 38400\n7) 57600\n8) 115200\nNote: If you modify baud rate, must be modified together code.\n( gSoftSerial.begin(baud rate) in seting() function. )\n";
const char* gMsgName = "> Name : ";
const char* gMsgPin = "> pin(4 digits only) : ";
const char* gMsgInvalidCmd = "Please enter a valid command.\n\n";
const char* gMsgResponseError = "Error : No response from HC-06.\n\n";
const char* gCmdPin = "AT+PIN";
const char* gCmdName = "AT+NAME";
const char* gCmdBaud = "AT+BAUD";
const char* gCmdVer = "AT+VERSION";

char gInChar;
char gSelectMode = 0;
char gCharBuffer[256];
void setup() {
  gSoftSerial.begin(9600);
  Serial.begin(9600);
}


void loop() {
 
 Serial.print(gMenu);  
 Serial.print(">");  
 clearBuffer();
 gInChar = readStr(0)[0];
 if(gInChar < '1' || gInChar > '4') {
   Serial.print(gMsgInvalidCmd);   
   gSelectMode = 'a';
 } else {
   gSelectMode = gInChar;
 }
 if(gSelectMode == '1') {
   Serial.print(gMsgName);
   clearBuffer();
   strcat(gCharBuffer, gCmdName);
   readStr(strlen(gCmdName));
   Serial.println(gCharBuffer);
   sendCmd(gCharBuffer);
 }   
 else if(gSelectMode == '2') {
   Serial.print(gMsgPin);
   clearBuffer();
   strcat(gCharBuffer, gCmdPin);
   readStr(strlen(gCmdPin));
   Serial.println(gCharBuffer);
   sendCmd(gCharBuffer);
 } else if(gSelectMode == '4') {
   clearBuffer();
   strcat(gCharBuffer, gCmdVer);
   Serial.println(gCharBuffer);
   sendCmd(gCharBuffer);
 }else if(gSelectMode == '3') {
   Serial.print(gMenuBaud);  
   Serial.print(">");  
   clearBuffer();
   gInChar = readStr(0)[0];
   if(gInChar < '1' || gInChar > '8') {
     Serial.print(gMsgInvalidCmd);   
     gSelectMode = 'a';
   } else {
     clearBuffer(); 
     strcat(gCharBuffer, gCmdBaud);
     uint8_t len = strlen(gCharBuffer); 
     gCharBuffer[len] = gInChar;
     gCharBuffer[len + 1] = '\0';
     Serial.println(gCharBuffer);
     sendCmd(gCharBuffer);      
   }
 }
}




void sendCmd(char* cmd) {
  Serial.println(); 
  gSoftSerial.write(cmd);
  for(uint8_t i = 0; i < 5; ++i) {
    delay(200);
    Serial.print('.');
  }
  if(!gSoftSerial.available()) {
       Serial.print(gMsgResponseError);
  } else {
      while(gSoftSerial.available()) {
        delay(10);
        Serial.print((char)gSoftSerial.read());
      }
  }
  Serial.println("\n");  
}

char* readStr(uint8_t offset) {
    uint8_t index = offset;
    while(!Serial.available());
    while(Serial.available()) {
        delay(10);
        gInChar = Serial.read();
        gCharBuffer[index] = gInChar;
        Serial.print(gInChar);
        index++;
    }
    Serial.print("\n");
    return gCharBuffer;
}

void clearBuffer() {
  memset(gCharBuffer, '\0', 256);
}
/*
#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3

SoftwareSerial SwSerial(txPin, rxPin);
char data;

void setup() {
  Serial.begin(9600);
  SwSerial.begin(9600);
  Serial.println("Ready..");
}

void loop() {
   // 시리얼 버퍼를 비운다.
   Serial.flush();
   Serial.print("cmd : ");
   // 버퍼에 값이 들어올 때 까지 대기. 
   while(!Serial.available());
   // HC-06 으로 명령어를 날린다. 
   while(Serial.available()) {
      data = Serial.read();
      if(data == -1) break;
      SwSerial.print(data);
      Serial.print(data);
      // 시리얼 통신에서는 9600bps 기준으로
      // read 를 사용할 때 1ms 의 딜레이를 줘야 한다.
      delay(1);
   }   
   Serial.println();
   // HC-06에서 처리할 시간을 준다.
   delay(1000);
   Serial.print("return : ");
   // HC-06 으로 부터 받아온 리턴 값을 출력한다.
   while(SwSerial.available()) {
      data = SwSerial.read();
      if(data == -1) break;
      Serial.print(data);
      delay(1);
   }  
   Serial.print("\n\n");
}*/
