#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimedAction.h>
#include <SoftwareSerial.h>
#define MAX_STRINGLEN 69
// If using software SPI (the default case):
#define OLED_SDA   9
#define OLED_SCL   10
#define OLED_DC    11
#define OLED_RESET 12
#define OLED_CS    13  

Adafruit_SSD1306 display(OLED_SDA, OLED_SCL, OLED_DC, OLED_RESET, OLED_CS);
#define LOGO16_GLCD_HEIGHT 40 
#define LOGO16_GLCD_WIDTH  56 
SoftwareSerial BT(0,1);
byte btStrBuff[MAX_STRINGLEN];
char btStr[MAX_STRINGLEN];
int Strlen = 0;
int flag = 0;

static const unsigned char PROGMEM right_draw[] =
{ 
  B00000000, B00000000,B00000000,B00000000, B00000000,B00001000,B00000000,
  B00000000, B00000000,B00000000,B00000000, B00000000,B00001100,B00000000, 
  B00000000, B00000000,B00000000,B00000000, B00000000,B00001110,B00000000,
  B00000000, B00000000,B00000000,B00000000, B00000000,B00001111,B00000000, 
  B00000000, B00000000,B00000000,B00000000, B00000000,B00001111,B10000000,
  B00000000, B00000000,B00000000,B00000000, B00000000,B00001111,B11000000, 
  B00000000, B00000000,B00000000,B00000000, B00000000,B00001111,B11100000,
  B00000000, B01111111,B11111111,B11111111, B11111111,B11111111,B11110000, 
  B00000001, B11111111,B11111111,B11111111, B11111111,B11111111,B11111000,
  B00000111, B11111111,B11111111,B11111111, B11111111,B11111111,B11111100, 
  B00011111, B11111111,B11111111,B11111111, B11111111,B11111111,B11111110,
  B00111111, B11111111,B11111111,B11111111, B11111111,B11111111,B11111111, 
  B00111111, B11111111,B11111111,B11111111, B11111111,B11111111,B11111110,
  B00111111, B11111111,B11111111,B11111111, B11111111,B11111111,B11111100, 
  B00111111, B11111111,B11111111,B11111111, B11111111,B11111111,B11111000,
  B00111111, B11111111,B11111111,B11111111, B11111111,B11111111,B11110000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00001111,B11100000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00001111,B11000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00001111,B10000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00001111,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00001110,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00001100,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00001000,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000, 
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000,
  B00111111, B11111100,B00000000,B00000000, B00000000,B00000000,B00000000};
static const unsigned char PROGMEM left_draw[] =
{ 
  B00000000, B00010000,B00000000,B00000000, B00000000, B00000000,B00000000,
  B00000000, B00110000,B00000000,B00000000, B00000000, B00000000,B00000000, 
  B00000000, B01110000,B00000000,B00000000, B00000000, B00000000,B00000000,
  B00000000, B11110000,B00000000,B00000000, B00000000, B00000000,B00000000, 
  B00000001, B11110000,B00000000,B00000000, B00000000, B00000000,B00000000,
  B00000011, B11110000,B00000000,B00000000, B00000000, B00000000,B00000000, 
  B00000111, B11110000,B00000000,B00000000, B00000000, B00000000,B00000000,
  B00001111, B11111111,B11111111,B11111111, B11111111, B11111110,B00000000, 
  B00011111, B11111111,B11111111,B11111111, B11111111, B11111111,B10000000,
  B00111111, B11111111,B11111111,B11111111, B11111111, B11111111,B11100000, 
  B01111111, B11111111,B11111111,B11111111, B11111111, B11111111,B11111000,
  B11111111, B11111111,B11111111,B11111111, B11111111, B11111111,B11111100, 
  B01111111, B11111111,B11111111,B11111111, B11111111, B11111111,B11111100,
  B00111111, B11111111,B11111111,B11111111, B11111111, B11111111,B11111100, 
  B00011111, B11111111,B11111111,B11111111, B11111111, B11111111,B11111100,
  B00001111, B11111111,B11111111,B11111111, B11111111, B11111111,B11111100, 
  B00000111, B11110000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000011, B11110000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000001, B11110000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B11110000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000000, B01110000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00110000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000000, B00010000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100, 
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100,
  B00000000, B00000000,B00000000,B00000000, B00000000, B00111111,B11111100 };
static const unsigned char PROGMEM straight_draw[] =
{ 
  B00000000, B00000000,B00000000,B00010000, B00000000,B00000000,B00000000,
  B00000000, B00000000,B00000000,B00111000, B00000000,B00000000,B00000000, 
  B00000000, B00000000,B00000000,B01111100, B00000000,B00000000,B00000000,
  B00000000, B00000000,B00000000,B11111110, B00000000,B00000000,B00000000, 
  B00000000, B00000000,B00000001,B11111111, B00000000,B00000000,B00000000,
  B00000000, B00000000,B00000011,B11111111, B10000000,B00000000,B00000000, 
  B00000000, B00000000,B00000111,B11111111, B11000000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00011111,B11111111, B11110000,B00000000,B00000000,
  B00000000, B00000000,B00111111,B11111111, B11111000,B00000000,B00000000, 
  B00000000, B00000000,B01111111,B11111111, B11111100,B00000000,B00000000,
  B00000000, B00000000,B11111111,B11111111, B11111110,B00000000,B00000000, 
  B00000000, B00000001,B11111111,B11111111, B11111111,B00000000,B00000000,
  B00000000, B00000011,B11111111,B11111111, B11111111,B10000000,B00000000, 
  B00000000, B00000111,B11111111,B11111111, B11111111,B11000000,B00000000,
  B00000000, B00001111,B11111111,B11111111, B11111111,B11100000,B00000000, 
  B00000000, B00011111,B11111111,B11111111, B11111111,B11110000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000, 
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000,
  B00000000, B00000000,B00001111,B11111111, B11100000,B00000000,B00000000 };

int STR = 0;
int jack=0;
void Continue(char B[MAX_STRINGLEN]){                                           //  Continue : 0.01m+form(1) + RD
  STR=0;
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE); // 'inverted' text
  display.setCursor(0,30);
  display.println("Continue");
   for(;;){
    if(B[STR] == '+'){
            break;
     }
    else{
    STR++;
    }
   }
  for(int num =0;num<MAX_STRINGLEN;num++){
           STR++;
           if(B[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              B[STR]=0;
              }
           }
            B[num]=B[STR];
            }
   //Serial.println(B);
  display.setCursor(0,45);
  display.println(B);
  Serial.setTimeout(0.001);
  display.drawBitmap(62,0,straight_draw,LOGO16_GLCD_WIDTH,LOGO16_GLCD_HEIGHT,WHITE );
  display.display();
  memset(B, 0, MAX_STRINGLEN);
  return;
  }

void Head(char C[MAX_STRINGLEN]){                                            // Head     : 0.2+form(0) + Direction(north 0, northeast 1, e 2, se 3, ...) + RD
  STR=0;
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE); // 'inverted' text
  display.setCursor(0,15);
  display.println("Head");
   for(;;){
    if(C[STR] == '+'){
      if(C[STR+1]=='0'){
    display.setCursor(0,30);
    display.println("North");
        STR+=2;
          for(int num =0;num<MAX_STRINGLEN;num++){
            STR++;
            if(C[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              C[STR]=0;
              }
            }
            C[num]=C[STR];
          }
            break;
    }
      if(C[STR+1]=='1'){
      display.setCursor(0,30);
      display.println("Northeast");
          STR+=2;
          for(int num =0;num<MAX_STRINGLEN;num++){
            STR++;
            if(C[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              C[STR]=0;
              }
            }
            C[num]=C[STR];
          }
          
            break;
    }
      if(C[STR+1]=='2'){
    display.setCursor(0,30);
    display.println("East");
          STR+=2;
          for(int num =0;num<MAX_STRINGLEN;num++){
            STR++;
            if(C[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              C[STR]=0;
              }
            }
            C[num]=C[STR];
          }
            break;
    }
      if(C[STR+1]=='3'){
      display.setCursor(0,30);
      display.println("SouthEast");
         STR+=2;
          for(int num =0;num<MAX_STRINGLEN;num++){
            STR++;
            if(C[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              C[STR]=0;
              }
            }
            C[num]=C[STR];
          }
            break;
    }
      if(C[STR+1]=='4'){
      display.setCursor(0,30);
      display.println("South");
         STR+=2;
           for(int num =0;num<MAX_STRINGLEN;num++){
            STR++;
            if(C[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              C[STR]=0;
              }
            }
            C[num]=C[STR];
          }
            break;
    }
      if(C[STR+1]=='5'){
      display.setCursor(0,30);
      display.println("Southwest");
         STR+=2;
          for(int num =0;num<MAX_STRINGLEN;num++){
            STR++;
            if(C[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              C[STR]=0;
              }
            }
            C[num]=C[STR];
          }
            break;
    }
      if(C[STR+1]=='6'){
      display.setCursor(0,30);
      display.println("West");
         STR+=2;
          for(int num =0;num<MAX_STRINGLEN;num++){
            STR++;
            if(C[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              C[STR]=0;
              }
            }
            C[num]=C[STR];
          }
            break;
    }
      if(C[STR+1]=='7'){
      display.setCursor(0,30);
      display.println("NorthWest");
          STR+=2;
          for(int num =0;num<MAX_STRINGLEN;num++){
            STR++;
            if(C[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              C[STR]=0;
              }
            }
            C[num]=C[STR];
          }
     }
     break;
    }
    else{
    STR++;
    }
   }
  display.setCursor(0,45);
  display.println(C); 
  Serial.setTimeout(0.001);
  display.drawBitmap(62,0,straight_draw,LOGO16_GLCD_WIDTH,LOGO16_GLCD_HEIGHT,WHITE );
  Serial.println(C);
  display.display();
  return;
  }
 void Turn(char D[MAX_STRINGLEN]){                                                //Turn     : 0.01 m +form(2) + direction(left 0, right 1,X) + prep(onto 0, to stay on 1) + RD
  STR=0;
  display.clearDisplay();
  display.display();                                                          
  display.setTextSize(1);
  display.setTextColor(WHITE); // 'inverted' text
  display.setCursor(0,0);
  display.println("Turn");
   for(;;){
    if(D[STR] == '+'){
      if(D[STR+1]=='0'){
        display.drawBitmap(70,0,left_draw,LOGO16_GLCD_WIDTH,LOGO16_GLCD_HEIGHT,WHITE );
        if(D[STR+3]=='0'){
         display.setCursor(0,15);
          display.println("Left");
          display.setCursor(0,30);
          display.println("onto");
            STR+=5;
          for(int num =0;num<MAX_STRINGLEN;num++){
            D[num]=D[STR];
            STR++;
            if(D[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              D[STR]=0;
              }
            }
          }
              break;
        }
        if(D[STR+3]=='1'){
          display.setCursor(0,15);
          display.println("Left");
          display.setCursor(0,30);
          display.println("to stay on");
            STR+=5;
          for(int num =0;num<MAX_STRINGLEN;num++){
            D[num]=D[STR];
            STR++;
             if(D[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              D[STR]=0;
              }
             }
          }
              break;
        }
        break;
      }
      if(D[STR+1]=='1'){
        display.drawBitmap(70,0,right_draw,LOGO16_GLCD_WIDTH,LOGO16_GLCD_HEIGHT,WHITE );
        if(D[STR+3]=='0'){
          display.setCursor(0,15);
          display.println("Right");
          display.setCursor(0,30);
          display.println("onto");
            STR+=5;
          for(int num =0;num<MAX_STRINGLEN;num++){
            D[num]=D[STR];
            STR++;
             if(D[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              D[STR]=0;
              }
             }
          }
              break;
        }
        if(D[STR+3]=='1'){
           display.setCursor(0,15);
          display.println("Right");
          display.setCursor(0,30);
          display.println("onto");
            STR+=5;
          for(int num =0;num<MAX_STRINGLEN;num++){
            D[num]=D[STR];
            STR++;
            if(D[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              D[STR]=0;
              }
            }
          }
              break;
        }
        break;
      }
      break;  
    }
    else{
    STR++;
    }
  }
  display.setCursor(0,45);
  display.println(D); 
  Serial.setTimeout(0.001);
  display.display();
  return;
 }
 
 void Slight(char E[MAX_STRINGLEN]){
   STR=0;
  display.clearDisplay();
  display.display();                                                          
  display.setTextSize(1);
  display.setTextColor(WHITE); // 'inverted' text
  display.setCursor(0,0);
  display.println("Slight");
   for(;;){
    if(E[STR] == '+'){
      if(E[STR+1]=='0'){
        display.drawBitmap(70,0,left_draw,LOGO16_GLCD_WIDTH,LOGO16_GLCD_HEIGHT,WHITE );
        if(E[STR+3]=='0'){
         display.setCursor(0,15);
          display.println("Left");
          display.setCursor(0,30);
          display.println("onto");
            STR+=5;
          for(int num =0;num<MAX_STRINGLEN;num++){
            E[num]=E[STR];
            STR++;
            if(E[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              E[STR]=0;
              }
            }
          }
              break;
        }
        if(E[STR+3]=='1'){
          display.setCursor(0,15);
          display.println("Left");
          display.setCursor(0,30);
          display.println("to stay on");
            STR+=5;
          for(int num =0;num<MAX_STRINGLEN;num++){
            E[num]=E[STR];
            STR++;
            if(E[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              E[STR]=0;
              }
            }
          }
              break;
        }
        break;
      }
      if(E[STR+1]=='1'){
        display.drawBitmap(70,0,right_draw,LOGO16_GLCD_WIDTH,LOGO16_GLCD_HEIGHT,WHITE );
        if(E[STR+3]=='0'){
          display.setCursor(0,15);
          display.println("Right");
          display.setCursor(0,30);
          display.println("onto");
            STR+=5;
          for(int num =0;num<MAX_STRINGLEN;num++){
            E[num]=E[STR];
            STR++;
            if(E[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              E[STR]=0;
              }
            }
          }
              break;
        }
        if(E[STR+3]=='1'){
          display.setCursor(0,15);
          display.println("Right");
          display.setCursor(0,30);
          display.println("onto");
            STR+=5;
          for(int num =0;num<MAX_STRINGLEN;num++){
            E[num]=E[STR];
            STR++;
            if(E[STR]=='+'){
            for(STR;STR<MAX_STRINGLEN;STR++){
              E[STR]=0;
              }
            }
          }
              break;
        }
        break;
      }
      break;  
    }
    else{
    STR++;
    }
  }
  display.setCursor(0,45);
  display.println(E); 
  Serial.setTimeout(0.001);
  display.display();
  return;
 }
  void Kilo(char H[MAX_STRINGLEN]){
 // Serial.println(H);
  display.setTextSize(0.5);
  display.setTextColor(WHITE); // 'inverted' text
  display.setCursor(95,55);
  display.println(H);
  Serial.setTimeout(0.001);
  display.display();
  return;
  }
  /*Format of four minor instructions:
  Head     : form(0) + Direction(north 0, northeast 1, e 2, se 3, ...) + RD
  Continue : form(1) + RD
  Turn     : form(2) + direction(left 0, rirht 1,X) + prep(onto 0, to stay on 1) + RD
  Slight   : form(3) + direction(left 0, rirht 1) + prep(onto 0, to stay on 1) + RD
ex: "Turn <b>left</b> to stay on <b>深井路</b>", will be formed into "2+0+1+深井路".*/
  int c =0;
  char KM[MAX_STRINGLEN];
void Direction(char str[MAX_STRINGLEN]){
  STR=0;
  Serial.println(str);
    for(;;){
     if(str[STR]=='+'){
      if(str[STR+1] == '0'){
        STR+=2;
        for(int num =0;num<MAX_STRINGLEN;num++){
             str[num]=str[STR];
              STR++;
             }
      Head(str);
      Kilo(KM);
      memset(KM, 0, MAX_STRINGLEN);
      memset(str, 0, MAX_STRINGLEN);
       break;
      }
      if(str[STR+1] == '1'){
        STR+=2;
       for(int num =0;num<MAX_STRINGLEN;num++){
             str[num]=str[STR];
             STR++;
             }
              Serial.println(str[0]);
      Continue(str);
      Kilo(KM);
      memset(KM, 0, MAX_STRINGLEN);
      memset(str, 0, MAX_STRINGLEN);
      break;
      }
      if(str[STR+1] == '2'){
        STR+=2;
        for(int num =0;num<MAX_STRINGLEN;num++){
             str[num]=str[STR];
              STR++;
             }
      Turn(str);
      Kilo(KM);
      memset(KM, 0, MAX_STRINGLEN);
      memset(str, 0, MAX_STRINGLEN);
      break;
      }
      if(str[STR+1] == '3'){
        STR+=2;
        for(int num =0;num<MAX_STRINGLEN;num++){
             str[num]=str[STR];
              STR++;
             }
      Slight(str);
      Kilo(KM);
      memset(KM, 0, MAX_STRINGLEN);
      memset(str, 0, MAX_STRINGLEN);
      break;
      }
      memset(KM, 0, MAX_STRINGLEN);
      memset(str, 0, MAX_STRINGLEN);
      break;
      }
    
    else{
    KM[STR]=str[STR];
    STR++;
    }
   }
 }
   
  

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  BT.begin(9600);
  Serial.setTimeout(50);
  BT.setTimeout(50);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
   }

char pre = '1';
void BTlisten(){
byte tmp;

  memset(btStr, 0, MAX_STRINGLEN);
  while( BT.available()>0 )
  {
    tmp = BT.read();
    
    if( (tmp == '0')&&(pre == '/') )
    {
      flag = 1;
      btStrBuff[Strlen-1] = 0; 
      sprintf(btStr, "%s", btStrBuff);
      memset(btStrBuff, 0, MAX_STRINGLEN);
      Strlen = 0;
      return;
    }
    btStrBuff[Strlen++] = tmp; 
    pre = tmp;
    
  }
  
}

TimedAction BL = TimedAction(0.1,BTlisten);
void loop() {

 BL.check(); 
  
  if(flag == 1)
  {
    Direction(btStr);
    Serial.println(btStr);
    memset(btStr, 0, MAX_STRINGLEN);
    flag = 0;
  }
}

 
