#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>

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

  if (/* !card.init(SPI_HALF_SPEED, SD_CS) */false) {
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

  lcd.setTextColor(WHITE);
}

int btn_app;
int btn_sync;
int btn_sett;

void loop() {
  btn_app = !(digitalRead(APP_CHOOSE));
  btn_sync = !(digitalRead(SYNC));
  btn_sett = !(digitalRead(SETT));

  if (btn_app) {
    lcd.setCursor(10, 100);
    lcd.write("X");
  } else
    lcd.fillRect(5, 95, 30, 30, BLUE);

  if (btn_sync) {
    lcd.setCursor(105, 100);
    lcd.write("X");
  } else
    lcd.fillRect(100, 95, 30, 30, BLUE);

  if (btn_sett) {
    lcd.setCursor(210, 100);
    lcd.write("X");
  } else
    lcd.fillRect(205, 95, 30, 30, BLUE);
}