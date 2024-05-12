#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
#include "discord.h"
#include "joystick.h"
#include "spotify.h"

//SD_reader
#define SD_CS 4
//display
#define TFT_DC 7
#define TFT_RST 8
#define SCR_WD 240
#define SCR_HT 240
//buttons
#define SYNC 5
#define SETT 6
#define APP_CHOOSE 2
//rotary
#define ROT_CLK 3
#define ROT_DT 9
#define ROT_SW 10
//linear
#define LINEAR A0

Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);
const int chipSelect = SD_CS;
size_t appVol = 0;


Sd2Card card;

void lcdInit() {
  lcd.begin();
  lcd.fillScreen(BLUE);
  lcd.setTextSize(3);
  lcd.setCursor(10, 10);
  lcd.setTextColor(GREEN);
}

/* void sdInit() {
  lcd.setCursor(10, 50);

  if (true  SD.begin() ) {  //program se zde bohužel zasekne při pokusu o inicializaci sd karty
    lcd.setTextColor(GREEN);
    lcd.write("SD SUCCES");
    Serial.print("SD SUCCES");
  } else {
    lcd.setTextColor(RED);
    lcd.write("SD FAIL");
  }
  Serial.print("SD_INIT DONE\n");
} */

void drawDiscord() {
  lcd.fillScreen(BLACK);
  size_t imagePos = 0;
      /*
        1 - imagePos + 2*(imagePos-1)
        2 - imagePos + imagePos*2-1 
        3 - 3*imagePos
        */    

  for(size_t i = 0; i<80;i++){
    for(size_t j = 0;j<80;j++){
      lcd.drawPixel(j + 2*(j-1) , i + i*2-1 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + 2*(j-1) , i + 2 * (i-1) , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + 2*(j-1) , i*3 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + j*2-1   , i + i*2-1 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + j*2-1   , i + 2 * (i-1) , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + j*2-1   , i*3 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j * 3       , i + i*2-1 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j * 3       , i + 2 * (i-1) , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j * 3       , i*3 , pgm_read_word(&discord[imagePos])); 
  
      imagePos++;
    }
  }  
}
void drawJoystick() {
  lcd.fillScreen(BLACK);
  size_t imagePos = 0;

    /*
      1 - imagePos + 2*(imagePos-1)
      2 - imagePos + imagePos*2-1 
      3 - 3*imagePos
      */    

  for(size_t i = 0; i<80;i++){
    for(size_t j = 0;j<80;j++){
      lcd.drawPixel(j + 2*(j-1) , i + i*2-1 , pgm_read_word(&joystick[imagePos]));
      lcd.drawPixel(j + 2*(j-1) , i + 2 * (i-1) , pgm_read_word(&joystick[imagePos]));
      lcd.drawPixel(j + 2*(j-1) , i*3 , pgm_read_word(&joystick[imagePos]));
      lcd.drawPixel(j + j*2-1   , i + i*2-1 , pgm_read_word(&joystick[imagePos]));
      lcd.drawPixel(j + j*2-1   , i + 2 * (i-1) , pgm_read_word(&joystick[imagePos]));
      lcd.drawPixel(j + j*2-1   , i*3 , pgm_read_word(&joystick[imagePos]));
      lcd.drawPixel(j * 3       , i + i*2-1 , pgm_read_word(&joystick[imagePos]));
      lcd.drawPixel(j * 3       , i + 2 * (i-1) , pgm_read_word(&joystick[imagePos]));
      lcd.drawPixel(j * 3       , i*3 , pgm_read_word(&joystick[imagePos]));    
    
      imagePos++;
    }
  } 
}
void drawSpotify() {
  lcd.fillScreen(BLACK);
  size_t imagePos = 0;

      /*
        1 - imagePos + 2*(imagePos-1)
        2 - imagePos + imagePos*2-1 
        3 - 3*imagePos
        */    

     for(size_t i = 0; i<80;i++){
    for(size_t j = 0;j<80;j++){
      lcd.drawPixel(j + 2*(j-1) , i + i*2-1 , pgm_read_word(&spotify[imagePos]));
      lcd.drawPixel(j + 2*(j-1) , i + 2 * (i-1) , pgm_read_word(&spotify[imagePos]));
      lcd.drawPixel(j + 2*(j-1) , i*3 , pgm_read_word(&spotify[imagePos]));
      lcd.drawPixel(j + j*2-1   , i + i*2-1 , pgm_read_word(&spotify[imagePos]));
      lcd.drawPixel(j + j*2-1   , i + 2 * (i-1) , pgm_read_word(&spotify[imagePos]));
      lcd.drawPixel(j + j*2-1   , i*3 , pgm_read_word(&spotify[imagePos]));
      lcd.drawPixel(j * 3       , i + i*2-1 , pgm_read_word(&spotify[imagePos]));
      lcd.drawPixel(j * 3       , i + 2 * (i-1) , pgm_read_word(&spotify[imagePos]));
      lcd.drawPixel(j * 3       , i*3 , pgm_read_word(&spotify[imagePos]));    
    
      imagePos++;
    }
  } 
}

enum states{
  VOLUME, SETTINGS, APP
};
enum states STATE, NEXT_STATE;

void setup() {
  Serial.begin(9600);
  pinMode(SYNC, INPUT_PULLUP);
  pinMode(SETT, INPUT_PULLUP);
  pinMode(APP_CHOOSE, INPUT_PULLUP);
  pinMode(ROT_CLK, INPUT);
  pinMode(ROT_DT, INPUT);
  pinMode(ROT_SW, INPUT);

  lcdInit();
  //sdInit();

  attachInterrupt(digitalPinToInterrupt(APP_CHOOSE), goApp, LOW);
  attachInterrupt(digitalPinToInterrupt(ROT_CLK), readVolume, CHANGE);

  STATE = VOLUME;
  NEXT_STATE = VOLUME;

  Serial.print("INIT done\n");

  lcd.setTextColor(WHITE);
  lcd.fillScreen(BLACK);

  appVol = 0;
}

void goSett(){
  if (STATE != SETTINGS)
    NEXT_STATE = SETTINGS;
  else
    NEXT_STATE = VOLUME;
}
void goApp(){
  if(STATE!=APP)
    NEXT_STATE = APP;
  else
    NEXT_STATE = VOLUME;
}

void sync(){
  for(size_t i = 0; i<1000;i++){
    if (digitalRead(SYNC))
      return;
    delay(1);
  }
  Serial.print("SYNC\n");
}


void appVolume(){
  size_t currentVol = analogRead(LINEAR);
  currentVol = map(currentVol, 0, 1023, 0, 100);
  if (currentVol != appVol){
    appVol = currentVol;
    switch (CURRENT_APP){
      case GAME:
      Serial.print("GAME ");
      break;
      case DISCORD:
      Serial.print("DISCORD ");
      break;
      case SPOTIFY:
      Serial.print("SPOTIFY ");
      break;
    }

    Serial.print(appVol); //udělat print aplikace
    Serial.print("\n"); //udělat print aplikace
  }
}


int syncData;

void loop() {
  syncData = !digitalRead(SYNC);
  if (syncData)
    sync();
  //appVolume(); //bohužel nefunkční, protože HW blbne

  switch(STATE){
    case VOLUME:
    lcd.fillScreen(RED);
    break;
    case SETTINGS:
    lcd.fillScreen(GREEN);
    break;
    case APP:
    lcd.fillScreen(BLUE);
    break;
  }
  STATE = NEXT_STATE;
}
