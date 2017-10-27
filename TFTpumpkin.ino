// TFT Pumpkin Patch
// scruss - 2017-10 - for Elmwood Electronics
// https://elmwood.to/
// written for Arduino
//  and Adafruit 3.5" TFT 320x480 + Touchscreen Breakout Board
//  <https://www.adafruit.com/product/2050>

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include "pumpkin.h"

/*
   Wiring:

   TFT      Arduino
   =====    =========
   GND      GND
   3-5V     5V
   D0       8
   D1       9
   D2       2
   D3       3
   D4       4
   D5       5
   D6       6
   D7       7
   CS       A3
   C/D      A2
   WR       A1
   RD       A0

*/
// LCD Control Pins
#define LCD_CS A3 // Chip Select    → A3
#define LCD_CD A2 // Command/Data   → A2
#define LCD_WR A1 // LCD Write      → A1
#define LCD_RD A0 // LCD Read       → A0
#define LCD_RESET A4 // Not used here

// It's Halloween - we only need two colours …
#define  BLACK   0x0000
// orange is #ffa500 in RGB-888; RGB-565 conversion is 0xFD20
#define ORANGE  0xFD20

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

int width, height; // for screen size

struct point {
  int16_t x;
  int16_t y;
};

// array to keep track of pumpkin coordinates
//  > 50 is a bit overlappy
//  < 50 can look a bit sparse
#define PUMPCOUNT 50
struct point pumpkins[PUMPCOUNT];

void setup(void) {
  // get screen size
  width = tft.width();
  height = tft.height();

  // reset and clear the screen
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(identifier);
  tft.fillScreen(BLACK);

  // draw initial pumpkins
  for (int i = 0; i < PUMPCOUNT; i++) {
    pumpkins[i].x = (int16_t) 4 * random(width / 4);
    pumpkins[i].y = (int16_t) 4 * random(height / 4);
    tft.drawBitmap(pumpkins[i].x, pumpkins[i].y,
                   (const uint8_t *)pgm_read_word(&img_and_mask[1]),
                   (int16_t) 32,
                   (int16_t) 32, ORANGE);
  }
}

void loop(void) {
  // draw the pumpkins!
  for (int i = 0; i < PUMPCOUNT; i++) {
    // erase previous pumpkin position by drawing it black
    tft.drawBitmap(pumpkins[i].x, pumpkins[i].y,
                   (const uint8_t *)pgm_read_word(&img_and_mask[1]),
                   (int16_t) 32,
                   (int16_t) 32, BLACK);
    // pick new random(ish) location and draw it in orange
    pumpkins[i].x = (int16_t) 4 * random(width / 4);
    pumpkins[i].y = (int16_t) 4 * random(height / 4);
    tft.drawBitmap(pumpkins[i].x, pumpkins[i].y,
                   (const uint8_t *)pgm_read_word(&img_and_mask[1]),
                   (int16_t) 32,
                   (int16_t) 32, ORANGE);
  }
}

