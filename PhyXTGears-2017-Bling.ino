#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <EEPROM.h>

//  ---------------------------------------  begin define  ---------------------------------------  //

#define MATRIX              6
#define pixyRingPin         8
#define gearStringPin       7

#define potentiometerPIN    A0
#define gearSensePin        41 // =========

#define pixyRingNum         00
#define gearStringNum       16

#define WIDTH               40  // each
#define HEIGHT              8   // each
#define NUMBER              2   // number of panels

#define PROGS               15  // programs that exist
#define ToRUN               10   // # to run (if oneOfEach is false) (if true, must equal number of progams being run)
const bool oneOfEach =      true;

#define OVER                true
//#define BRIGHT              55
#define BRIGHT              75

#define FONT                FreeSerif12pt7b
#define FIRST_FONT          FreeSansBoldOblique9pt7b

#define RED                 matrix.Color(255, 0, 0)
#define GREEN               matrix.Color(0, 255, 0)
#define BLUE                matrix.Color(0, 0, 255)
#define YELLOW              matrix.Color(255, 255, 0)
#define AQUA                matrix.Color(0, 255, 255)
#define VIOLET              matrix.Color(255, 0, 255)
#define WHITE               matrix.Color(255, 255, 255)
#define BLACK               matrix.Color(0, 0, 0)

#define TESTING             false

#define ROBORIO_SPEED       9600
#define SERIAL_SPEED        250000

//#define VERTICAL_FONT

//  ----------------------------------------  end define  ----------------------------------------  //

bool testing = true;
bool turnOff = false;

// int BRIGHT = 25;

//Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, 1, NUMBER, MATRIX, NEO_TILE_TOP + NEO_TILE_LEFT + NEO_TILE_COLUMNS + NEO_TILE_ZIGZAG + NEO_MATRIX_COLUMNS + NEO_MATRIX_TOP + NEO_MATRIX_BOTTOM + NEO_MATRIX_ZIGZAG  + NEO_GRB + NEO_KHZ800);

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(WIDTH, HEIGHT, 1, NUMBER, MATRIX, NEO_TILE_BOTTOM + NEO_TILE_RIGHT + NEO_TILE_COLUMNS + NEO_TILE_ZIGZAG + NEO_MATRIX_COLUMNS + NEO_MATRIX_TOP + NEO_MATRIX_BOTTOM + NEO_MATRIX_ZIGZAG  + NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixyRing   = Adafruit_NeoPixel(pixyRingNum, pixyRingPin,   NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel gearString = Adafruit_NeoPixel(gearStringNum, gearStringPin, NEO_GRB + NEO_KHZ800);

int ledNumber;
//bool noSerial = true;

String subteams[23] = {"Shout-", " out", "to our", "sub-", " teams", "Media", "Chair-", " mans", "CAD", "Anim-", " ation",
                       "Wood-", " work-", "  ing", "Fund-", " rais-", "  ing", "Out-", " reach", "Scout-", " ing", "Spirit"
                      };

/*
   sound bars
   reversing sine wave / moving sine wave
   fire
*/

// bitmaps

unsigned char firstLogo[40 * 16 * 3];
int firstLogoL;
int firstLogoW;

// ---Selection---
// 0 and 2
/*
  0: Dots
  1: Rectangle zoom (disabled)
  2: name
  3: fill for 0.25 sec (disabled)
  4 : zig - zag
  5 : strobe multi
  6 : strobe white
  7 : sine
  8 : Logo (screensaver)
  9 : Spotlight
  10: 1720
  11: Honors
  12: Audio bar
  13: Team # display
  14: Ball shooting
*/

//                          // one of each true (false)
//                      0  1  2  3  4  5  6  7  8  9 10 11 12 13 14
int progLimit[PROGS] = {1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0};  // Limit for each program (or ratio)
int progRuns[PROGS];        // Number of times each has been selected (nothing)
int blingPrograms[ToRUN];   // order

// ----

bool progBright = false;
int bright;
String tN[] = {"", "", "1720"};
bool quitRun = false;

// ----

String ROBOT;

// ==============================================

void zigZag(unsigned long Stop, uint16_t color = matrix.Color(255, 255, 255), uint16_t color2 = matrix.Color(255, 255, 255), int d = 100, int gap = 1);
void printText(String phrase, int color[], int run_time = 0, bool scroll = true, bool upperCase = true, int Skip = 0, int pixOffset = 0); //run_time should be set to at least 100 if your font is at 12pt
void printBitMap(int b[], unsigned long Stop, bool scroll = false); //Prints from bitmap, "int b[]".
void rectangleZoom(int x, int y, int width, int height, int color, int Delay = 99, bool noFill = false); //Creates rectangles inside rectangle one by one.
void rainbow(); //Fills matrix with colors then cycles through color wheel. The rough time that this takes to execute is: 4 Seconds.
void strobePixel(unsigned long Time, int Delay, int color, int num, bool Rand); //Strobes random pixel on screen then clears screen and strobes another one.
void theaterChase(int Skips = 1, int Delay = 0, int color = matrix.Color(255, 255, 255), bool bow = false); //Goes through all pixels in matrix clearing screen every time a new pixel is shown.
void rDraw(unsigned long Stop, uint16_t color, int n = 3, int Delay = 10, bool Random = false); //Draws random pixels onto screen does NOT clear every time new pixel is shwon.
void theaterChaseRainbow(int Skips, int Delay = 10); //Does same thing as theater chase only this time it changes color from color wheel. The rough time that this takes to execute is: 3 Seconds.
void brightnessControl(); //Gets value from sensor then divides value by 8.6 sets brightness to that value.
void drawShape(int shape, int values[], int color[]); //Rectangle: 0, Circle: 1, Triangle: 2, Line: 3, Pixels: 4, RoundRectangle: 5.
void generateRGB(); //Randomizes values inside randomRGB.
void sinWave (uint16_t color, int Delay, int n = 1, float mult = float(10));
void screenSaver(unsigned long Stop, int tSize, int cSize, int sSize, int Speed = 35);
void creditsPrint(String message, uint16_t color, int Delay, bool twoText = false, String message2 = "", uint16_t color2 = matrix.Color(255, 255, 255), bool threeText = false, String message3 = "", uint16_t color3 = matrix.Color(255, 255, 255), bool allCaps = true, int endDelay = 0);
void credits (String Messages[], uint16_t colors[], int LoopSize, int Delay = 0, int scrollDelay = 25, bool randColor = false);
void explodingCircle(int x, int y, int r, uint16_t color = WHITE, bool fill = true);
void drawShipTL (int x, int y, float s, uint16_t color, bool Show = true);
void drawShip(int x, int y, float s, uint16_t color = WHITE, bool Show = true);
String serialIn(int s = 0);
void ballShoot (uint16_t rCol, int n = 1, int s = 0);
void error (String message, int code = 1);

// ==============================================

// put your setup code here, to run once:
void setup() {
  Serial.begin(SERIAL_SPEED);
  Serial.setTimeout(25);
  Serial.println('\n');
  //
  Serial1.begin(ROBORIO_SPEED);
  Serial1.setTimeout(100);
  // -----
  ledNumber = WIDTH * HEIGHT * NUMBER;
  setupPins();
  // load bitmap doesn't work
  // loadBitmap();
  matrix.begin();
  matrix.show();
  gearString.begin();
  gearString.show();
  matrix.setTextWrap(false); //Does weird things if you don't include this.
  matrix.setTextColor(matrix.Color(255, 0, 0));
  matrix.setFont(&FONT);
  matrix.setBrightness(100);
  Serial.println("Microseconds: " + String(micros()));
  brightnessControl();
  randSeed();
  //  if (testing) {
  //    noSerial = false;
  //  }
}

// put your main code here, to run repeatedly:
void loop() {
  // if running bling
  bool testBool = (testing != TESTING);
  if (turnOff) {
    delay(100);
  } else if (!testBool) {
    Reset();
    Serial.println("Starting Bling...");
    bling();
    Reset();
  } else {  // if testing
    Serial.println("Starting Test...");
    test();
  }
  if (Serial.available() > 0) {
    serialInterp();
  }
  Reset();
}

// for running bling
void bling () {
  blingSelect();
  runBling(blingPrograms);
  Reset();
  delay(100);
}

int tempB = BRIGHT;

// for running test code
void test () {
  //  sinWaveM(matrix.Color(255, 255, 255), 0, 2500, 25, 2);
  //  Reset();
  //  delay(2000);

  //  gear(20, 7, YELLOW);
  matrix.fillScreen(WHITE);
  matrix.setBrightness(tempB);
  matrix.show();
  delay(1000);
  Serial.println(tempB);
  if (Serial.available() > 0) {
    tempB = serialInt();
    Serial.println("Using brightness " + String(tempB) + ".");
  }
}

void drawDeath (int x, int y, uint16_t color, uint16_t color2, uint16_t color3) {
  matrix.fillCircle(x, y, 20, color);
  matrix.fillCircle(x - 12, y + 9, 2, color2);
  matrix.drawPixel(x - 12, y + 9, color3);
}

void drawRay (int xI, int yI, uint16_t color) {
  const int x = 28;
  const int y = 8;
  matrix.drawLine(37, 7, x, y, color);
  matrix.drawLine(33, 3, x, y, color);
  matrix.drawLine(x, y, xI, yI, color);
}

//void doShip () {
//  drawDeath(47, -4, BLUE, BLACK, WHITE);
//  drawShip(8, 11, 1.5, RED);
//  drawRay(GREEN, 8, 11);
//  updateScreen();
//  delay(99999);

void doShip () {
  const uint16_t shipColor = RED;
  const uint16_t planetColor = BLUE;
  const uint16_t insetColor = BLACK;
  const uint16_t middleDot = WHITE;
  const uint16_t rayColor = GREEN;

  for (float i = 0; i <= 2; i += 0.1) {
    drawShip(20, 7, i, shipColor);
    matrix.clear();
    delay(25);
  }
  for (int i = 0; i < (ceil(matrix.width() / 2.0) + 9); i += 1) {
    drawShip(ceil(matrix.width() / 2.0) + i, 7 + floor(i / 2.0), 2.0, shipColor);
    matrix.clear();
    delay(10);
  }
  const int maxS = 12;
  for (int i = 0; i < (maxS - 2); i++) {
    drawDeath((matrix.width() + 16) - i, i - 13, planetColor, insetColor, middleDot);
    //    Serial.println("circle draw");
    //    matrix.drawPixel(39, 15, WHITE);
    updateScreen();
    matrix.clear();
    delay(500);
  }
  for (int i = 0; i < 18; i++) {
    drawDeath(matrix.width() + 7, -4, planetColor, insetColor, middleDot);
    drawShip(25 - i, matrix.height() - floor(i / 3.0), 1.5, shipColor, false);
    drawRay(25 - i, matrix.height() - floor(i / 3.0), GREEN);
    matrix.show();
    matrix.clear();
    delay(50);
  }
  //                                    18                 15
  //  explodingCircle((matrix.width() + 16) - maxS, maxS - 13, 20, planetColor);
  delay(500);
  Reset();
  delay(2500);

  //explodingCircle(20, 8, WHITE);
  //Reset();
  //delay(2500);

  //  brightOver(255);
  //  matrix.fillCircle(20, 8, 1.5f, matrix.Color(200, 230, 0));
  //  ball(RED);
  explodingCircle(20, 7, 4, BLUE, true);
}

