#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
#include "logo.h"

//SD_reader
#define SD_CS 4
//display
#define TFT_DC 7
#define TFT_RST 8
#define SCR_WD 240
#define SCR_HT 240
//buttons
#define SYNC 5
#define SETT 3
#define APP_CHOOSE 2
//rotary
#define ROT_CLK 6
#define ROT_DT 9
#define ROT_SW 10
//linear
#define LINEAR A0

Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);
const int chipSelect = SD_CS;

Sd2Card card;

void lcdInit() {
  lcd.begin();
  lcd.fillScreen(BLUE);
  lcd.setTextSize(3);
  lcd.setCursor(10, 10);
  lcd.setTextColor(GREEN);
  lcd.write("LCD SUCC!");
  Serial.print("LCD_init DONE\n");
}

void sdInit() {
  lcd.setCursor(10, 50);

  if (true /* SD.begin() */) {  //program se zde bohužel zasekne při pokusu o inicializaci sd karty
    lcd.setTextColor(GREEN);
    lcd.write("SD SUCCES");
    Serial.print("O");
  } else {
    lcd.setTextColor(RED);
    lcd.write("SD FAIL");
  }
  Serial.print("SD_INIT DONE\n");
}

void setup() {
  Serial.begin(9600);
  pinMode(SYNC, INPUT_PULLUP);
  pinMode(SETT, INPUT_PULLUP);
  pinMode(APP_CHOOSE, INPUT_PULLUP);
  pinMode(ROT_CLK, INPUT);
  pinMode(ROT_DT, INPUT);
  pinMode(ROT_SW, INPUT);

  Serial.print("Serial_begin\n");

  lcdInit();
  sdInit();


  //attachInterrupt(digitalPinToInterrupt(APP_CHOOSE), drawJoystick, LOW);
  //attachInterrupt(digitalPinToInterrupt(SETT), drawDiscord, LOW);



  lcd.setTextColor(WHITE);
}



/* enum displayState {
  DISCORD, JOYSTICK, SPOTIFY
};

enum displayState DISP; */



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
      /* lcd.drawPixel(j + 2*(j-1) , i + i*2-1 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + 2*(j-1) , i + 2 * (i-1) , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + 2*(j-1) , i*3 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + j*2-1   , i + i*2-1 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + j*2-1   , i + 2 * (i-1) , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j + j*2-1   , i*3 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j * 3       , i + i*2-1 , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j * 3       , i + 2 * (i-1) , pgm_read_word(&discord[imagePos]));
      lcd.drawPixel(j * 3       , i*3 , pgm_read_word(&discord[imagePos])); */
  
    
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

void loop() {

lcd.fillScreen(CYAN);
delay(100);
}
