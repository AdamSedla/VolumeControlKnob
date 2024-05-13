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
size_t appVol;
int move;
int lastClkState;
int currentClkState;
int click;
bool block;


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
void writeSpotify(){
  lcd.fillScreen(BLACK);
  lcd.setTextColor(GREEN);  
  lcd.setTextSize(5);
  lcd.setCursor(20,100);
  lcd.print("SPOTIFY");
}
void writeDiscord(){
  lcd.fillScreen(BLACK);
  lcd.setTextColor(BLUE);  
  lcd.setTextSize(5);
  lcd.setCursor(15,100);
  lcd.print("DISCORD");
}

enum states{
  VOLUME, SETTINGS, APP
};
enum states STATE, NEXT_STATE;

enum apps{
  GAME, DISCORD, SPOTIFY
};
enum apps CURRENT_APP;

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

  STATE = SETTINGS;
  NEXT_STATE = APP;

  CURRENT_APP = GAME;

  Serial.print("INIT done\n");

  lcd.setTextColor(WHITE);
  lcd.fillScreen(BLACK);

  appVol = 0;
  move = 0;
  lastClkState = 0;
  click = 0;
  block = false;
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
void printSettings(){
  lcd.fillScreen(BLACK);
  lcd.setTextColor(WHITE);  
  lcd.setTextSize(4);
  lcd.setCursor(10,10);
  lcd.print("NASTAVENI");
  lcd.setTextSize(3);
  lcd.setCursor(30, 50);
  lcd.print("Skupiny app");
  lcd.setCursor(30, 80);
  lcd.print("Jazyk");
  lcd.setCursor(30, 110);
  lcd.print("Barva");
  lcd.setCursor(30, 140);
  lcd.print("RickRoll");
  lcd.setCursor(30, 170);
  lcd.print("Restart");
  lcd.setCursor(30, 200);
  lcd.print("Info");

  lcd.setCursor(10,50);
  lcd.print(">");
}

void chooseArrow(){
    switch(CURRENT_APP){
    case GAME:
      lcd.setCursor(10,50);
      break;
    case SPOTIFY:
      lcd.setCursor(10,80);
      break;
    case DISCORD:
      lcd.setCursor(10,110);
      break;
  }
}

void printIcon(){
  switch(CURRENT_APP){
    case GAME:
      drawJoystick();
      break;
    case DISCORD:
      writeDiscord();
      break;
    case SPOTIFY:
      writeSpotify();
      break;
  }
}

int syncData;
enum apps MENU_APP, NEXT_MENU_APP;

void loop() {
  syncData = !digitalRead(SYNC);
  if (syncData)
    sync();
  if(STATE == VOLUME)
    appVolume();
  if(settData){
    goSett();
    POS_STATE = APPSK;
    POS_NEXT_STATE = APPSK;
  }
  if(NEXT_STATE != STATE){ //nastavení dalšího stavu
    switch(NEXT_STATE){
      case VOLUME:
      printIcon();
      break;
      case SETTINGS:
      printSettings();
      delay(100);
      break;
      case APP:
      printApps();
      MENU_APP = CURRENT_APP;
      NEXT_MENU_APP = CURRENT_APP;
      break;
    }
    STATE = NEXT_STATE;
  } 
  if(clickData)
    checkClick();

  switch(STATE){
    case VOLUME:
    lcd.fillScreen(RED);
    break;
    case SETTINGS:
    lcd.fillScreen(GREEN);
    break;
    case APP:
      switch(MENU_APP){
        case GAME: //0
          if(move > 0){
            printMenu1();
            NEXT_MENU_APP = SPOTIFY;
          }
          else if(move < 0){
            printMenu2();
            NEXT_MENU_APP = DISCORD;
          }
          if(click){
            CURRENT_APP = GAME;
            NEXT_STATE = VOLUME;
          }
          break;
        case SPOTIFY: //1
          if(move > 0){
            printMenu2();
            NEXT_MENU_APP = DISCORD;
          }
          else if(move < 0){
            printMenu0();
            NEXT_MENU_APP = GAME;
          }
          if(click){
            CURRENT_APP = SPOTIFY;
            NEXT_STATE = VOLUME;
          }
          break;
        case DISCORD: //2
          if(move > 0){
            printMenu0();
            NEXT_MENU_APP = GAME;
          }
          else if(move < 0){
            printMenu1();
            NEXT_MENU_APP = SPOTIFY;
          }
          if(click){
            CURRENT_APP = DISCORD;
            NEXT_STATE = VOLUME;
          }
          break;
      }
      move = 0;
      click = 0;
      MENU_APP = NEXT_MENU_APP;
    break;
  }
}
