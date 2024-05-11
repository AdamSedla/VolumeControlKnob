#include "discord.h"
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
