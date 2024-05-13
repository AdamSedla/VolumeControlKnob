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
  Serial.print("SYNC ");
  Serial.print(appVol);
  Serial.print("\n");
}


void appVolume(){
  size_t currentVol = analogRead(LINEAR);
  currentVol = map(currentVol, 1023, 0, 0, 100);
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

    Serial.print(appVol);
    Serial.print("\n");
  }
}
void readVolume(){
  currentClkState = digitalRead(ROT_CLK);
  if (currentClkState != lastClkState) {
    if (digitalRead(ROT_DT) != currentClkState)
      move++;
    else
      move--;
  }
  lastClkState = currentClkState;
}

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

void printApps(){
  lcd.fillScreen(BLACK);
  lcd.setTextColor(WHITE);  
  lcd.setTextSize(4);
  lcd.setCursor(10,10);
  lcd.print("APLIKACE");
  lcd.setTextSize(3);
  lcd.setCursor(30, 50);
  lcd.setTextColor(RED);
  lcd.print("Hry");
  lcd.setTextColor(GREEN);
  lcd.setCursor(30, 80);
  lcd.print("Spotify");
  lcd.setTextColor(BLUE);
  lcd.setCursor(30, 110);
  lcd.print("Discord");

  chooseArrow();

  lcd.setTextColor(WHITE);  
  lcd.print(">");
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

void printMenu0(){
  lcd.fillRect(0,50,30,180,BLACK);
  lcd.setTextSize(3);
  lcd.setTextColor(WHITE);
  lcd.setCursor(10,50); //+30
  lcd.print(">");
}
void printMenu1(){
  lcd.fillRect(0,50,30,180,BLACK);
  lcd.setTextSize(3);
  lcd.setTextColor(WHITE);
  lcd.setCursor(10,80); //+30
  lcd.print(">");
}
void printMenu2(){
  lcd.fillRect(0,50,30,180,BLACK);
  lcd.setTextSize(3);
  lcd.setTextColor(WHITE);
  lcd.setCursor(10,110); //+30
  lcd.print(">");
}
void printMenu3(){
  lcd.fillRect(0,50,30,180,BLACK);
  lcd.setTextSize(3);
  lcd.setTextColor(WHITE);
  lcd.setCursor(10,140); //+30
  lcd.print(">");
}
void printMenu4(){
  lcd.fillRect(0,50,30,180,BLACK);
  lcd.setTextSize(3);
  lcd.setTextColor(WHITE);
  lcd.setCursor(10,170); //+30
  lcd.print(">");
}
void printMenu5(){
  lcd.fillRect(0,50,30,180,BLACK);
  lcd.setTextSize(3);
  lcd.setTextColor(WHITE);
  lcd.setCursor(10,200); //+30
  lcd.print(">");
}

void checkClick(){
  while(!digitalRead(ROT_SW));
  click = 1;
}

int syncData;
int clickData;
int settData;

enum settPos{
  APPSK, LANG, CLR, RR, RST, INFO
};
enum settPos POS_STATE, POS_NEXT_STATE; 

enum apps MENU_APP, NEXT_MENU_APP;

void loop() {
  syncData = !digitalRead(SYNC);
  clickData = !digitalRead(ROT_SW);
  settData = !digitalRead(SETT);
  if (syncData && STATE == VOLUME)
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
      if (move > 0){
        Serial.print("VOL +\n");
        move = 0;
      }
      if (move < 0){
        Serial.print("VOL -\n");
        move = 0;
      }
      if(click){
        Serial.print("MUTE\n");
        click = 0;
      }
      break;
    case SETTINGS:
      switch(POS_STATE){
        case APPSK: //0
          if(!block){
            if(move > 0){
              printMenu1();
              POS_NEXT_STATE = LANG;
            }
            else if(move < 0){
              printMenu5();
              POS_NEXT_STATE = INFO;
            }
          }
          if(click){
            // vybrat skupiny aplikací
            if(!block){
              lcd.fillScreen(BLACK);
              lcd.setTextColor(WHITE);  
              lcd.setTextSize(5);
              lcd.setCursor(20,100);
              lcd.print("skupiny");
              block = true;
            }
            else{
              printSettings();
              block = false;
            }
          }
          break;
        case LANG: //1
          if(!block){
            if(move > 0){
              printMenu2();
              POS_NEXT_STATE = CLR;
            }
            else if(move < 0){
              printMenu0();
              POS_NEXT_STATE = APPSK;
            }
          }
          if(click){
            // vybrat výběr jazyka
            if(!block){
            lcd.fillScreen(BLACK);
            lcd.setTextColor(WHITE);  
            lcd.setTextSize(5);
            lcd.setCursor(20,100);
            lcd.print("jazyk");
            block = true;
            }
            else{
              printSettings();
              printMenu1();
              block = false;
            }
          }
          break;
        case CLR: //2
          if(!block){
            if(move > 0){
              printMenu3();
              POS_NEXT_STATE = RR;
            }
            else if(move < 0){
              printMenu1();
              POS_NEXT_STATE = LANG;
            }
          }
          if(click){
            if(!block){
              // vybrat výběr barvy
              lcd.fillScreen(BLACK);
              lcd.setTextColor(WHITE);  
              lcd.setTextSize(5);
              lcd.setCursor(20,100);
              lcd.print("barvy");
              block = true;
            } else{
              printSettings();
              printMenu2();
              block = false;
            }
          }
          break;
        case RR: //3
          if(!block){
            if(move > 0){
              printMenu4();
              POS_NEXT_STATE = RST;
            }
            else if(move < 0){
              printMenu2();
              POS_NEXT_STATE = CLR;
            }
          }
          if(click){
            if(!block){
              // vybrat rickRoll
              lcd.fillScreen(BLACK);
              lcd.setTextColor(WHITE);  
              lcd.setTextSize(2);
              lcd.setCursor(0,100);
              lcd.print("NeverGonnaGiveYouUp");
              block = true;
            }
            else{
              printSettings();
              printMenu3();
              block = false;
            }
          }
          break;
        case RST: //4
          if(!block){
            if(move > 0){
              printMenu5();
              POS_NEXT_STATE = INFO;
            }
            else if(move < 0){
              printMenu3();
              POS_NEXT_STATE = RR;
            }
          }
          if(click){
            if(!block){
              // vybrat reset
              lcd.fillScreen(BLACK);
              lcd.setTextColor(WHITE);  
              lcd.setTextSize(5);
              lcd.setCursor(20,100);
              lcd.print("RESET");
              block = true;
            }
            else{
              printSettings();
              printMenu4();
              block = false;
            }
          }
          break;
        case INFO: //5
          if(!block){
            if(move > 0){
              printMenu0();
              POS_NEXT_STATE = APPSK;
            }
            else if(move < 0){
              printMenu4();
              POS_NEXT_STATE = RST;
            }
          }  
          if(click){
            if(!block){
              // vybrat info
              lcd.fillScreen(BLACK);
              lcd.setTextColor(WHITE);  
              lcd.setTextSize(5);
              lcd.setCursor(20,100);
              lcd.print("info");
              block = true;
            }
            else{
              printSettings();
              printMenu5();
              block = false;
            }
          }
          break;
      }
      POS_STATE = POS_NEXT_STATE;
      move = 0;
      click = 0;
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
