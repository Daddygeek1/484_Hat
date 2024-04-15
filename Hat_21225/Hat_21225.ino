// Include 
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include "smileyTongue24.h"
// #include "21225.h"       need smaller
// #include "shearForce.h"  need smaller 
#include "linux32.h"

// NeoMatrix configuration
//Adafruit_NeoMatrix *matrix;

// Define
// Define full matrix
#define CHIPSET       WS2812B
#define COLOR_ORDER   GRB
#define PIN           10
//#define leds        484
#define MW            44   
#define MH            11
#define BRIGHTNESS    25
#define BM32
Adafruit_NeoMatrix *matrix = new Adafruit_NeoMatrix(MW, MH, PIN,
  NEO_MATRIX_BOTTOM   + NEO_MATRIX_RIGHT +
  NEO_MATRIX_ROWS     + NEO_MATRIX_ZIGZAG,
  NEO_GRB             + NEO_KHZ800 );

//#define PSTR // Make Arduino Due happy

// defined as matrix->color(255,0,0) 
// main adafruit_gfx backends that lack color()
#define LED_BLACK		0

#define LED_RED_VERYLOW 	(15 << 11)
#define LED_RED_LOW 		  (20 << 11)
#define LED_RED_MEDIUM 		(26 << 11)
#define LED_RED_HIGH 		  (31 << 11)

#define LED_GREEN_VERYLOW	(15 << 5)   
#define LED_GREEN_LOW 		(25 << 5) 
#define LED_GREEN_MEDIUM 	(35 << 5)  
#define LED_GREEN_HIGH 		(63 << 5)  

#define LED_BLUE_VERYLOW	10
#define LED_BLUE_LOW 		  15
#define LED_BLUE_MEDIUM 	20
#define LED_BLUE_HIGH 		30

#define LED_ORANGE_VERYLOW	(LED_RED_VERYLOW + LED_GREEN_VERYLOW)
#define LED_ORANGE_LOW		  (LED_RED_LOW     + LED_GREEN_LOW)
#define LED_ORANGE_MEDIUM	  (LED_RED_MEDIUM  + LED_GREEN_MEDIUM)
#define LED_ORANGE_HIGH		  (LED_RED_HIGH    + LED_GREEN_HIGH)

#define LED_PURPLE_VERYLOW	(LED_RED_VERYLOW + LED_BLUE_VERYLOW)
#define LED_PURPLE_LOW		  (LED_RED_LOW     + LED_BLUE_LOW)
#define LED_PURPLE_MEDIUM	  (LED_RED_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_PURPLE_HIGH		  (LED_RED_HIGH    + LED_BLUE_HIGH)

#define LED_CYAN_VERYLOW	  (LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_CYAN_LOW		    (LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_CYAN_MEDIUM		  (LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_CYAN_HIGH		    (LED_GREEN_HIGH    + LED_BLUE_HIGH)

#define LED_WHITE_VERYLOW	  (LED_RED_VERYLOW + LED_GREEN_VERYLOW + LED_BLUE_VERYLOW)
#define LED_WHITE_LOW		    (LED_RED_LOW     + LED_GREEN_LOW     + LED_BLUE_LOW)
#define LED_WHITE_MEDIUM	  (LED_RED_MEDIUM  + LED_GREEN_MEDIUM  + LED_BLUE_MEDIUM)
#define LED_WHITE_HIGH		  (LED_RED_HIGH    + LED_GREEN_HIGH    + LED_BLUE_HIGH)
uint32_t colors[] = {matrix->Color(255, 0, 0),   // Red
                       matrix->Color(0, 255, 0),   // Green
                       matrix->Color(0, 0, 255),   // Blue
                       matrix->Color(255, 255, 0), // Yellow
                       matrix->Color(255, 0, 255), // Magenta
                       matrix->Color(0, 255, 255), // Cyan
                       matrix->Color(255, 128, 0), // Orange
                       matrix->Color(128, 0, 255), // Purple
                       matrix->Color(255, 255, 255), // White
                       matrix->Color(128, 128, 128)}; // Gray

void setup() {
    Serial.begin(115200);
    matrix->begin();
    matrix->setTextWrap(false);
    matrix->setBrightness(BRIGHTNESS);
    matrix->fillScreen(LED_GREEN_HIGH);
    matrix->setBrightness(15);
    matrix->setTextSize(1);
    matrix->show();
    matrix->clear();
       
}


//progmem
static const uint8_t PROGMEM
    mono_bmp[][11] =
    {
	{   // 0: checkered 1
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
      B10101010,
	    B01010101,
	    B10101010
			},

	{   // 1: checkered 2
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
	    B01010101,
	    B10101010,
      B01010101,
	    B10101010,
	    B01010101
			},

	{   // 2: smiley
	    B00111100,
	    B01000010,
	    B10100101,
	    B10000001,
	    B10100101,
	    B10011001,
	    B01000010,
	    B00111100 },

	{   // 3: neutral
	    B00111100,
	    B01000010,
	    B10100101,
	    B10000001,
	    B10111101,
	    B10000001,
	    B01000010,
	    B00111100 },

	{   // 4; frowny
	    B00111100,
	    B01000010,
	    B10100101,
	    B10000001,
	    B10011001,
	    B10100101,
	    B01000010,
	    B00111100 },
    };
static const uint16_t PROGMEM
    // These bitmaps were written for a backend that only supported
    // 4 bits per color with Blue/Green/Red ordering while neomatrix
    // uses native 565 color mapping as RGB.  
    // I'm leaving the arrays as is because it's easier to read
    // which color is what when separated on a 4bit boundary
    // The demo code will modify the arrays at runtime to be compatible
    // with the neomatrix color ordering and bit depth.
    RGB_bmp[][64] = {
      // 00: blue, blue/red, red, red/green, green, green/blue, blue, white
      {	0x100, 0x200, 0x300, 0x400, 0x600, 0x800, 0xA00, 0xF00, 
	0x101, 0x202, 0x303, 0x404, 0x606, 0x808, 0xA0A, 0xF0F, 
      	0x001, 0x002, 0x003, 0x004, 0x006, 0x008, 0x00A, 0x00F, 
	0x011, 0x022, 0x033, 0x044, 0x066, 0x088, 0x0AA, 0x0FF, 
	0x010, 0x020, 0x030, 0x040, 0x060, 0x080, 0x0A0, 0x0F0, 
	0x110, 0x220, 0x330, 0x440, 0x660, 0x880, 0xAA0, 0xFF0, 
	0x100, 0x200, 0x300, 0x400, 0x600, 0x800, 0xA00, 0xF00, 
	0x111, 0x222, 0x333, 0x444, 0x666, 0x888, 0xAAA, 0xFFF, },

      // 01: grey to white
      {	0x111, 0x222, 0x333, 0x555, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x222, 0x222, 0x333, 0x555, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x333, 0x333, 0x333, 0x555, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x555, 0x555, 0x555, 0x555, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x777, 0x777, 0x777, 0x777, 0x777, 0x999, 0xAAA, 0xFFF, 
	0x999, 0x999, 0x999, 0x999, 0x999, 0x999, 0xAAA, 0xFFF, 
	0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xAAA, 0xFFF, 
	0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, 0xFFF, },

      // 02: low red to high red
      {	0x001, 0x002, 0x003, 0x005, 0x007, 0x009, 0x00A, 0x00F, 
	0x002, 0x002, 0x003, 0x005, 0x007, 0x009, 0x00A, 0x00F, 
	0x003, 0x003, 0x003, 0x005, 0x007, 0x009, 0x00A, 0x00F, 
	0x005, 0x005, 0x005, 0x005, 0x007, 0x009, 0x00A, 0x00F, 
	0x007, 0x007, 0x007, 0x007, 0x007, 0x009, 0x00A, 0x00F, 
	0x009, 0x009, 0x009, 0x009, 0x009, 0x009, 0x00A, 0x00F, 
	0x00A, 0x00A, 0x00A, 0x00A, 0x00A, 0x00A, 0x00A, 0x00F, 
	0x00F, 0x00F, 0x00F, 0x00F, 0x00F, 0x00F, 0x00F, 0x00F, },

      // 03: low green to high green
      {	0x010, 0x020, 0x030, 0x050, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x020, 0x020, 0x030, 0x050, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x030, 0x030, 0x030, 0x050, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x050, 0x050, 0x050, 0x050, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x070, 0x070, 0x070, 0x070, 0x070, 0x090, 0x0A0, 0x0F0, 
	0x090, 0x090, 0x090, 0x090, 0x090, 0x090, 0x0A0, 0x0F0, 
	0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0A0, 0x0F0, 
	0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, 0x0F0, },

      // 04: low blue to high blue
      {	0x100, 0x200, 0x300, 0x500, 0x700, 0x900, 0xA00, 0xF00, 
	0x200, 0x200, 0x300, 0x500, 0x700, 0x900, 0xA00, 0xF00, 
	0x300, 0x300, 0x300, 0x500, 0x700, 0x900, 0xA00, 0xF00, 
	0x500, 0x500, 0x500, 0x500, 0x700, 0x900, 0xA00, 0xF00, 
	0x700, 0x700, 0x700, 0x700, 0x700, 0x900, 0xA00, 0xF00, 
	0x900, 0x900, 0x900, 0x900, 0x900, 0x900, 0xA00, 0xF00, 
	0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xA00, 0xF00, 
	0xF00, 0xF00, 0xF00, 0xF00, 0xF00, 0xF00, 0xF00, 0xF00, },

      // 05: 1 black, 2R, 2O, 2G, 1B with 4 blue lines rising right
      {	0x000, 0x200, 0x000, 0x400, 0x000, 0x800, 0x000, 0xF00, 
      	0x000, 0x201, 0x002, 0x403, 0x004, 0x805, 0x006, 0xF07, 
	0x008, 0x209, 0x00A, 0x40B, 0x00C, 0x80D, 0x00E, 0xF0F, 
	0x000, 0x211, 0x022, 0x433, 0x044, 0x855, 0x066, 0xF77, 
	0x088, 0x299, 0x0AA, 0x4BB, 0x0CC, 0x8DD, 0x0EE, 0xFFF, 
	0x000, 0x210, 0x020, 0x430, 0x040, 0x850, 0x060, 0xF70, 
	0x080, 0x290, 0x0A0, 0x4B0, 0x0C0, 0x8D0, 0x0E0, 0xFF0,
	0x000, 0x200, 0x000, 0x500, 0x000, 0x800, 0x000, 0xF00, },

      // 06: 4 lines of increasing red and then green
      { 0x000, 0x000, 0x001, 0x001, 0x002, 0x002, 0x003, 0x003, 
	0x004, 0x004, 0x005, 0x005, 0x006, 0x006, 0x007, 0x007, 
	0x008, 0x008, 0x009, 0x009, 0x00A, 0x00A, 0x00B, 0x00B, 
	0x00C, 0x00C, 0x00D, 0x00D, 0x00E, 0x00E, 0x00F, 0x00F, 
	0x000, 0x000, 0x010, 0x010, 0x020, 0x020, 0x030, 0x030, 
	0x040, 0x040, 0x050, 0x050, 0x060, 0x060, 0x070, 0x070, 
	0x080, 0x080, 0x090, 0x090, 0x0A0, 0x0A0, 0x0B0, 0x0B0, 
	0x0C0, 0x0C0, 0x0D0, 0x0D0, 0x0E0, 0x0E0, 0x0F0, 0x0F0, },

      // 07: 4 lines of increasing red and then blue
      { 0x000, 0x000, 0x001, 0x001, 0x002, 0x002, 0x003, 0x003, 
	0x004, 0x004, 0x005, 0x005, 0x006, 0x006, 0x007, 0x007, 
	0x008, 0x008, 0x009, 0x009, 0x00A, 0x00A, 0x00B, 0x00B, 
	0x00C, 0x00C, 0x00D, 0x00D, 0x00E, 0x00E, 0x00F, 0x00F, 
	0x000, 0x000, 0x100, 0x100, 0x200, 0x200, 0x300, 0x300, 
	0x400, 0x400, 0x500, 0x500, 0x600, 0x600, 0x700, 0x700, 
	0x800, 0x800, 0x900, 0x900, 0xA00, 0xA00, 0xB00, 0xB00, 
	0xC00, 0xC00, 0xD00, 0xD00, 0xE00, 0xE00, 0xF00, 0xF00, },

      // 08: criss cross of green and red with diagonal blue.
      {	0xF00, 0x001, 0x003, 0x005, 0x007, 0x00A, 0x00F, 0x000, 
	0x020, 0xF21, 0x023, 0x025, 0x027, 0x02A, 0x02F, 0x020, 
	0x040, 0x041, 0xF43, 0x045, 0x047, 0x04A, 0x04F, 0x040, 
	0x060, 0x061, 0x063, 0xF65, 0x067, 0x06A, 0x06F, 0x060, 
	0x080, 0x081, 0x083, 0x085, 0xF87, 0x08A, 0x08F, 0x080, 
	0x0A0, 0x0A1, 0x0A3, 0x0A5, 0x0A7, 0xFAA, 0x0AF, 0x0A0, 
	0x0F0, 0x0F1, 0x0F3, 0x0F5, 0x0F7, 0x0FA, 0xFFF, 0x0F0, 
	0x000, 0x001, 0x003, 0x005, 0x007, 0x00A, 0x00F, 0xF00, },

      // 09: 2 lines of green, 2 red, 2 orange, 2 green
      { 0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, 
	0x0F0, 0x0F0, 0x0FF, 0x0FF, 0x00F, 0x00F, 0x0F0, 0x0F0, },

      // 10: multicolor smiley face
      { 0x000, 0x000, 0x00F, 0x00F, 0x00F, 0x00F, 0x000, 0x000, 
	0x000, 0x00F, 0x000, 0x000, 0x000, 0x000, 0x00F, 0x000, 
	0x00F, 0x000, 0xF00, 0x000, 0x000, 0xF00, 0x000, 0x00F, 
	0x00F, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x00F, 
	0x00F, 0x000, 0x0F0, 0x000, 0x000, 0x0F0, 0x000, 0x00F, 
	0x00F, 0x000, 0x000, 0x0F4, 0x0F3, 0x000, 0x000, 0x00F, 
	0x000, 0x00F, 0x000, 0x000, 0x000, 0x000, 0x00F, 0x000, 
	0x000, 0x000, 0x00F, 0x00F, 0x00F, 0x00F, 0x000, 0x000, },
};

//void fun stuff
//setTextSize lets you set the size to 1 (8 pixel high) or 2 (16 pixel high for really big text!)
void display_boxes_Blue() {
    matrix->clear();
    matrix->drawRect(0,0, MW,  MH,   LED_BLUE_VERYLOW);
    matrix->drawRect(1,1, MW-2,MH-2, LED_BLUE_LOW);
    matrix->fillRect(2,2, MW-4,MH-4, LED_BLUE_MEDIUM);
    matrix->fillRect(3,3, MW-6,MH-6, LED_BLUE_HIGH);
    matrix->show();
  }

void display_boxes_Red() {
    matrix->clear();
    matrix->drawRect(0,0, MW,  MH,   LED_RED_VERYLOW);
    matrix->drawRect(1,1, MW-2,MH-2, LED_RED_LOW);
    matrix->fillRect(2,2, MW-4,MH-4, LED_RED_MEDIUM);
    matrix->fillRect(3,3, MW-6,MH-6, LED_RED_HIGH);
    matrix->show();
  }

void display_boxes_Green() {
    matrix->clear();
    matrix->drawRect(0,0, MW,  MH,   LED_GREEN_VERYLOW);
    matrix->drawRect(1,1, MW-2,MH-2, LED_GREEN_LOW);
    matrix->fillRect(2,2, MW-4,MH-4, LED_GREEN_MEDIUM);
    matrix->fillRect(3,3, MW-6,MH-6, LED_GREEN_HIGH);
    matrix->show();
  }
// Convert a BGR 4/4/4 bitmap to RGB 5/6/5 used by Adafruit_GFX
void fixdrawRGBBitmap(int16_t x, int16_t y, const uint16_t *bitmap, int16_t w, int16_t h) {
    // work around "a15 cannot be used in asm here" compiler bug when using an array on ESP8266
    // uint16_t RGB_bmp_fixed[w * h];
    static uint16_t *RGB_bmp_fixed = (uint16_t *) malloc( w*h*2);
    for (uint16_t pixel=0; pixel<w*h; pixel++) {
	uint8_t r,g,b;
	uint16_t color = pgm_read_word(bitmap + pixel);

	//Serial.print(color, HEX);
	b = (color & 0xF00) >> 8;
	g = (color & 0x0F0) >> 4;
	r = color & 0x00F;
	//Serial.print(" ");
	//Serial.print(b);
	//Serial.print("/");
	//Serial.print(g);
	//Serial.print("/");
	//Serial.print(r);
	//Serial.print(" -> ");
	// expand from 4/4/4 bits per color to 5/6/5
	b = map(b, 0, 15, 0, 31);
	g = map(g, 0, 15, 0, 63);
	r = map(r, 0, 15, 0, 31);
	//Serial.print(r);
	//Serial.print("/");
	//Serial.print(g);
	//Serial.print("/");
	//Serial.print(b);
	RGB_bmp_fixed[pixel] = (r << 11) + (g << 5) + b;
	//Serial.print(" -> ");
	//Serial.println(RGB_bmp_fixed[pixel], HEX);
    }
    matrix->drawRGBBitmap(x, y, RGB_bmp_fixed, w, h);
  }

void display_panOrBounceBitmap (uint8_t bitmapSize) {
    // keep integer math, deal with values 16 times too big
    // start by showing upper left of big bitmap or centering if the display is big
    int16_t xf = max(0, (MW-bitmapSize)/2) << 4;
    int16_t yf = max(0, (MH-bitmapSize)/2) << 4;
    // scroll speed in 1/16th
    int16_t xfc = 6;
    int16_t yfc = 3;
    // scroll down and right by moving upper left corner off screen 
    // more up and left (which means negative numbers)
    int16_t xfdir = -1;
    int16_t yfdir = -1;

    for (uint16_t i=1; i<200; i++) {
	bool updDir = false;

	// Get actual x/y by dividing by 16.
	int16_t x = xf >> 4;
	int16_t y = yf >> 4;

	  matrix->clear();
	  // bounce 8x8 tri color smiley face around the screen
  	if (bitmapSize == 8) fixdrawRGBBitmap(x, y, RGB_bmp[10], 8, 8);
	  // pan 24x24 pixmap
 	  if (bitmapSize == 24) matrix->drawRGBBitmap(x, y, (const uint16_t *) bitmap24, bitmapSize, bitmapSize);
  #ifdef BM32
	if (bitmapSize == 32) matrix->drawRGBBitmap(x, y, (const uint16_t *) bitmap32, bitmapSize, bitmapSize);
  #endif
	matrix->show();
	 
	// Only pan if the display size is smaller than the pixmap
	// but not if the difference is too small or it'll look bad.
	if (bitmapSize-MW>2) {
	    xf += xfc*xfdir;
	    if (xf >= 0)                      { xfdir = -1; updDir = true ; };
	    // we don't go negative past right corner, go back positive
	    if (xf <= ((MW-bitmapSize) << 4)) { xfdir = 1;  updDir = true ; };
	}
	if (bitmapSize-MH>2) {
	    yf += yfc*yfdir;
	    // we shouldn't display past left corner, reverse direction.
	    if (yf >= 0)                      { yfdir = -1; updDir = true ; };
	    if (yf <= ((MH-bitmapSize) << 4)) { yfdir = 1;  updDir = true ; };
	}
	// only bounce a pixmap if it's smaller than the display size
	if (MW>bitmapSize) {
	    xf += xfc*xfdir;
	    // Deal with bouncing off the 'walls'
	    if (xf >= (MW-bitmapSize) << 4) { xfdir = -1; updDir = true ; };
	    if (xf <= 0)           { xfdir =  1; updDir = true ; };
	}
	if (MH>bitmapSize) {
	    yf += yfc*yfdir;
	    if (yf >= (MH-bitmapSize) << 4) { yfdir = -1; updDir = true ; };
	    if (yf <= 0)           { yfdir =  1; updDir = true ; };
	}
	
	if (updDir) {
	    // Add -1, 0 or 1 but bind result to 1 to 1.
	    // Let's take 3 is a minimum speed, otherwise it's too slow.
	    xfc = constrain(xfc + random(-1, 2), 3, 16);
	    yfc = constrain(xfc + random(-1, 2), 3, 16);
	}
	delay(10);
    }
  }

void display_balls() {  // Bounce three balls around
  }
//void text

void display_scrollText1() {    //  Welcome to 2_Worlds
    uint8_t size = max(int(44/8), 1);
    matrix->clear();
    matrix->setTextSize(1);
    matrix->setRotation(0);
    for (int8_t x=44; x>=-60; x--) {
	matrix->clear();
	matrix->setCursor(x,0);
	matrix->setTextColor(LED_GREEN_HIGH);
	matrix->print("Welcome to");
	if (MH>10) {
	    matrix->setCursor(-20-x,MH-7);
	    matrix->setTextColor(LED_ORANGE_HIGH);
	    matrix->print(" Worlds");
	}
	matrix->show();
       delay(100);
           }
  }  
void display_scrollText2() {    //  Steve vertical- not working
    matrix->setRotation(1);
    matrix->setTextSize(0);
    matrix->setTextColor(LED_BLUE_HIGH);
    for (int16_t x=8; x>=-44; x--) {
	matrix->clear();
	matrix->setCursor(0,0);
	matrix->print("STEVE");
	//matrix->show();
        //delay(50);
  if (MH>30) {
	    matrix->setCursor(0,16);
	    matrix->setTextColor(LED_ORANGE_HIGH);
	    matrix->print("STEVE");
      }
	    matrix->show();
        delay(50);
	    }
    }

void display_scrollText3() {    //  You can accomplish anything you put your mind too
  matrix->begin();
  matrix->setTextColor(matrix->Color(200, 85, 0));
  matrix->setTextSize(1);
  
  const char* text = "You can accomplish anything you put your mind too";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }

void display_scrollText4() {    //  The First Law: A robot may not injure a human being or, through inaction, allow a human being to come to harm.
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setTextColor(matrix->Color(150, 150, 150));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "The First Law: A robot may not injure a human being or, through inaction, allow a human being to come to harm.";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0); // Clear the screen
    matrix->setCursor(x, 2); // Set cursor position
    matrix->print(text); // Print the text
    matrix->show(); // Display the text
    delay(30); // Delay between frames for smooth scrolling
    x--; // Move the text to the left
    }
  }
    
void display_scrollText5() {    //  Shear Force FTC 
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 255, 0));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Shear Force FTC";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(50);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText6() {    //  Creative activity is one of the few self-rewarding activities. Being creative is like being in love! -Woodie Flowers
  matrix->begin();
  matrix->setTextColor(matrix->Color(255, 85, 125));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Creative activity is one of the few self-rewarding activities. Being creative is like being in love! -Woodie Flowers";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText7() {    //  First robotics is the hardest fun you will ever have
  matrix->begin();
  matrix->setTextColor(matrix->Color(200, 10, 25));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "First robotics is the hardest fun you will ever have";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText8() {    //  Wear your safety glasses
  matrix->begin();
  matrix->setTextColor(matrix->Color(255, 255, 0));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Wear your safety glasses";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(50);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText9() {    //  The city needs a car like a fish needs a bicycle. -Dean Kamen
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 85, 0));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "The city needs a car like a fish needs a bicycle. -Dean Kamen";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText10() {    // Steve Red
  matrix->fillScreen(0);
  matrix->setCursor(8, 2);
  matrix->setRotation(0);
  matrix->setTextSize(1);
  matrix->setTextColor(LED_RED_HIGH);
  matrix->print("STEVE");
  matrix->show();
    delay(10);
  matrix->setTextColor(LED_BLUE_HIGH);
  matrix->print("STEVE");
  matrix->show();
    delay(10);
    
  } 
void display_scrollText11() {    // FIRST is More Than Robots
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 85, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "FIRST is More Than Robots";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText12() {    // If it’s not on fire, it is a software problem
  matrix->begin();
  matrix->setTextColor(matrix->Color(255, 35, 35));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "If it is not on fire, it is a software problem";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText13() {    // Organized Chaos
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setTextColor(matrix->Color(255, 255, 255)); // Set text color to white
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Organized Chaos";

  // Display the text
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;
  while (x > -textLength) {
    matrix->fillScreen(0); // Clear the screen
    matrix->setCursor(x, 2); // Set cursor position
    matrix->print(text); // Print the text
    matrix->show(); // Display the text
    delay(50); // Delay between frames for smooth scrolling
    x--; // Move the text to the left
  }

  // Randomly change colors and display chaotic patterns
  for (int i = 0; i < 50; i++) { // Display for a fixed duration
    for (int j = 0; j < 10; j++) { // Update multiple times per frame for a chaotic effect
      int16_t xPos = random(MW); // Random x-coordinate
      int16_t yPos = random(MH); // Random y-coordinate
      uint32_t color = matrix->Color(random(256), random(256), random(256)); // Random color
      matrix->drawPixel(xPos, yPos, color); // Draw a pixel at the random position with random color
    }
    matrix->show(); // Display the updated matrix
    delay(50); // Delay between frames for a smooth animation
    }
  }
void display_scrollText14() {    // 21225 Shear Force 
    uint8_t size = max(int(44/8), 1);
    matrix->clear();
    matrix->setTextWrap(false);  // we don't wrap text so it scrolls nicely
    matrix->setTextSize(1);
    matrix->setRotation(0);
    for (int8_t x=7; x>=-44; x--) {
	matrix->clear();
	matrix->setCursor(x,0);
	matrix->setTextColor(LED_GREEN_HIGH);
	matrix->print("Sheer Force");
	if (MH>10) {
	    matrix->setCursor(-20-x,MH-7);
	    matrix->setTextColor(LED_ORANGE_HIGH);
	    matrix->print("21225");
	}
	matrix->show();
       delay(75);
           }
  }  
void display_scrollText15() {    // The Second Law: A robot must obey the orders given to it by human beings except where such orders would conflict with the First Law.
  matrix->begin();
  matrix->setTextColor(matrix->Color(150, 150, 150));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "The Second Law: A robot must obey the orders given to it by human beings except where such orders would conflict with the First Law.";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText16() {    // This is not your fathers science fair
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 85, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "This is Not your fathers science fair";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText17() {    // Soda + Pizza = Robot
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 0, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Soda + Pizza = Robot";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText18() {    // We will fix it in programming
  matrix->begin();
  matrix->setTextColor(matrix->Color(255, 200, 10));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "We will fix it in programming";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText19() {    // Gracious Professionalism
  matrix->begin();
  matrix->setTextColor(matrix->Color(20, 0, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Gracious Professionalism";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(50);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText20() {    // Steve Rainbow
  // draw some text!
  matrix->clear();
  matrix->setCursor(8, 1);   // start at top left, with one pixel of spacing
  matrix->setTextSize(1);    // size 1 == 8 pixels high
 
  // print each letter with a rainbow color
  matrix->setTextColor(matrix->Color(255,0,0)); 
  matrix->print('S');
  //matrix->show();
  matrix->setTextColor(matrix->Color(255,255,0)); 
  matrix->print('T');
  //matrix->show();
  matrix->setTextColor(matrix->Color(255,255,255)); 
  matrix->print('E');
  matrix->setTextColor(matrix->Color(0,255,255)); 
  matrix->print('V');
  matrix->setTextColor(matrix->Color(0,0,255));  
  matrix->print('E');
 
  matrix->setCursor(8, 9);   // next line
  matrix->setTextColor(matrix->Color(0,7,7)); 
  matrix->print('S');
  matrix->setTextColor(matrix->Color(0,4,7)); 
  matrix->print('T');
  matrix->setTextColor(matrix->Color(0,0,7));
  matrix->print('E');
  matrix->setTextColor(matrix->Color(4,0,7)); 
  matrix->print("V");
  matrix->setTextColor(matrix->Color(7,0,4)); 
  matrix->print("E");
  matrix->show();
    delay(1000);
  }
void display_scrollText21() {    // Inch by Inch, we are going metric. -Dean Kamens
  matrix->begin();
  matrix->setTextColor(matrix->Color(255, 0, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Inch by Inch, we are going metric. -Dean Kamens";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText22() {    // Got Bot ??
  matrix->begin();
  matrix->setTextColor(matrix->Color(255, 255, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Got Bot ??";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(50);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText23() {    // 21225
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 255, 0));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "21225";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(50);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText24() {    // Not forehead protectors
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 255, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Not forehead protectors";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText25() {    // WHAT DO YOU MEAN YOU DO NOT HAVE DUCT TAPE?!?!?
  matrix->begin();
  matrix->setTextColor(matrix->Color(255, 0, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "WHAT DO YOU MEAN YOU DO NOT HAVE DUCT TAPE?!?!?";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText26() {    // FIRST -
    uint8_t size = max(int(44/8), 1);
    matrix->clear();
    matrix->setTextSize(1);
    matrix->setRotation(0);
    for (int8_t x=6; x>=-60; x--) {
	matrix->clear();
	matrix->setCursor(x,0);
	matrix->setTextColor(LED_RED_HIGH);
	matrix->print("First");
	if (MH>10) {
	    matrix->setCursor(-20-x,MH-7);
	    matrix->setTextColor(LED_WHITE_HIGH);
	    matrix->print("  Robotics");
	}
	matrix->show();
       delay(50);
           }
  }  
void display_scrollText27() {   // The Third Law: A robot must protect \its own existence as long as such protection does not conflict with the First or Second Law.
  matrix->begin();
  matrix->setTextColor(matrix->Color(125, 125, 125));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "The Third Law: A robot must protect \its own existence as long as such protection does not conflict with the First or Second Law.";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText28() {    // Never Never Ever give up
  matrix->begin();
  matrix->setTextColor(matrix->Color(255, 200, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Never Never Ever give up";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText29() {    // FTC CENTERSTAGE FTC
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 85, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "FTC CENTERSTAGE FTC";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(50);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText30() {    // It is a Robotics thing.
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 85, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Is a Robotics thing.";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText31() {    // It is not what you do – it is what you are becoming. -Dean Kamen
  matrix->begin();
  matrix->setTextColor(matrix->Color(200, 200, 255));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Its not what you do – its what you are becoming. -Dean Kamen";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText32() {    // Never fear Steve is here
  matrix->begin();
  matrix->setTextColor(matrix->Color(0, 255, 100));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "Never fear Steve is here";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_scrollText33() {    // It is a hardware issue
  matrix->begin();
  matrix->setTextColor(matrix->Color(200, 85, 0));
  matrix->setTextSize(1);
  matrix->setTextWrap(false);
  
  const char* text = "It is a hardware issue";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels
  int16_t x = MW;

  while (x > -textLength) {
    matrix->fillScreen(0);    // Clear the screen
    matrix->setCursor(x, 2);  // Set cursor position
    matrix->print(text);      // Print the text
    matrix->show();           // Display the text
    delay(30);                // Delay between frames for smooth scrolling
    x--;                      // Move the text to the left
    }
  }
void display_chaoticText(uint32_t duration_ms) {    //21225
  matrix->begin();
  matrix->setTextWrap(false);
  matrix->setBrightness(50);

  // Colors for the text
  uint32_t colors[] = {matrix->Color(255, 0, 0),   // Red
                       matrix->Color(0, 255, 0),   // Green
                       matrix->Color(0, 0, 255),   // Blue
                       matrix->Color(255, 255, 0), // Yellow
                       matrix->Color(255, 0, 255), // Magenta
                       matrix->Color(0, 255, 255), // Cyan
                       matrix->Color(255, 128, 0), // Orange
                       matrix->Color(128, 0, 255), // Purple
                       matrix->Color(255, 255, 255), // White
                       matrix->Color(128, 128, 128)}; // Gray

  const char* text = "21225";
  int16_t textLength = strlen(text) * 6; // Estimate the text length in pixels

  unsigned long startTime = millis(); // Get the start time

  while (millis() - startTime < duration_ms) {
    matrix->fillScreen(0); // Clear the screen

    // Randomly select text color
    uint32_t textColor = colors[random(0, 10)];

    // Randomly select starting position
    int16_t x = random(0, MW - textLength);
    int16_t y = random(0, MH - 8); // Adjust as needed for vertical position

    // Randomly select movement direction and speed
    int16_t dx = random(-3, 4); // Random horizontal movement
    int16_t dy = random(-3, 4); // Random vertical movement

    // Display the text
    matrix->setCursor(x, y);
    matrix->setTextColor(textColor);
    matrix->print(text);
    matrix->show(); // Display the text

    // Delay for animation
    delay(100); // Adjust as needed for speed
  }
}

void display_scrollText34() {    // TEST AREA
  }



// Loop


void loop() {
  // put your main code here, to run repeatedly:
   // display_boxes_Blue();
   //delay(3000);

   //display_boxes_Red();
    //delay(3000);

   // display_boxes_Green();
    //delay(3000);
    
    display_scrollText1();  //Welcome to worlds
      delay(1000);
    //display_scrollText2();  //STEVE
      //delay(1000);
    display_scrollText3();  //You can accomplish anything you put your mind to 
      delay(1000);
    display_scrollText4();  //The First Law: A robot may not injure a human being or, through inaction, allow a human being to come to harm.
      delay(1000);
    //display_balls():          // Bounce three balls around
      //delay(1000);
    display_scrollText5();  //Shear Force FTC 
      delay(1000);
    //display_panOrBounceBitmap(21225_ram);
      //delay(1000);
    display_scrollText6();  //Creative activity is one of the few self-rewarding activities. Being creative is like being in love! -Woodie Flowers
      delay(1000);
    display_scrollText7();  //First robotics is the hardest fun you'll ever have
      delay(1000);
    display_scrollText8();  //Wear your safety glasses
      delay(1000);
    display_scrollText9();  //The city needs a car like a fish needs a bicycle. dean kamen
      delay(1000);
    display_scrollText10();  //Steve 
      delay(3000);
    display_boxes_Green();
      delay(3000);
    display_scrollText11();  //FIRST is More Than Robots
      delay(1000);
    display_scrollText12();  //If it’s not on fire, it’s a software problem
      delay(1000);
    display_scrollText13();  //Organized Chaos
      delay(1000);
    display_panOrBounceBitmap(24); //smileyTongue24
    delay(1000);
    display_scrollText14();  //21225 Shear Force 
      delay(1000);
    display_scrollText15();  //The Second Law: A robot must obey the orders given to it by human beings except where such orders would conflict with the First Law.
      delay(1000); 
    display_scrollText16();  //This isn’t your father’s science fair
      delay(1000);
    display_scrollText17();  //Soda + Pizza = Robot
      delay(1000);
    display_scrollText18();  //We’ll fix it in programming
      delay(1000);
    display_scrollText19();  //Gracious Professionalism
      delay(1000);
    display_scrollText20();  //STEVE
      delay(3000);
    display_scrollText21();  //Inch by Inch, we’re going metric.” -Dean Kamens
      delay(1000);
    display_scrollText22();  //Got Bot?
      delay(1000);
    display_scrollText23();  //21225
      delay(1000);
    display_scrollText24();  //not forehead protectors
      delay(1000);
    display_scrollText25();  //“WHAT DO YOU MEAN YOU DON’T HAVE DUCT TAPE?!?!?”
      delay(1000);
    display_scrollText26();  //FIRST -
      delay(3000);
     display_scrollText27();  //The Third Law: A robot must protect its own existence as long as such protection does not conflict with the First or Second Law.
      delay(1000);
    display_scrollText28();  //never never never give up
      delay(1000);
    display_panOrBounceBitmap(32);
      delay(1000);
    display_scrollText29();  //CENTERSTAGE FTC
      delay(1000);
    display_scrollText30();  //It’s a Robotics thing.
      delay(1000);
    display_scrollText31();  //It’s not what you do – it’s what you are becoming. -Dean Kamen
      delay(1000);
    display_scrollText32();  //Never fear Steve is here
      delay(1000);
    display_scrollText33();  //It's a hardware issue
      delay(1000);
    display_chaoticText(5000); //21225
      delay(1000);
    display_scrollText34();  //  Test code
      delay(1000);
    
}




