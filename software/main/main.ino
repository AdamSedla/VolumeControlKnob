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
