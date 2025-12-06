#include <ezButton.h>
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 6 // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 24

ezButton buttonOFF(2); // create ezButton object that attach to pin 6;
ezButton buttonR(3);   // create ezButton object that attach to pin 7;
ezButton buttonB(4);   // create ezButton object that attach to pin 8;
ezButton buttonG(5);   // create ezButton object that attach to pin 8;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

byte colorR = 0;
byte colorG = 0;
byte colorB = 0;
byte modo = 0;
byte pixel = 1;
byte modos = 4;
byte memorypixel = 0;

void setup()
{
  // put your setup code here, to run once:
  buttonOFF.setDebounceTime(50); // set debounce time to 50 milliseconds
  buttonR.setDebounceTime(50);   // set debounce time to 50 milliseconds
  buttonG.setDebounceTime(50);   // set debounce time to 50 milliseconds
  buttonB.setDebounceTime(50);   // set debounce time to 50 milliseconds
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'.
  //  Serial.begin(9600);
}

void loop()
{
  buttonOFF.loop();
  buttonR.loop(); // MUST call the loop() function first
  buttonG.loop(); // MUST call the loop() function first
  buttonB.loop(); // MUST call the loop() function first
  checkbreak();
  switch (modo)
  {
  case 0:
    selector();
    break;
  case 1:
    agregacolor();
    break;
  case 2:
    rainbow(20);
    break;
  case 3:
    theaterChaseRainbow(50);
    break;
  case 4:
    memory();
    break;
  }
}

void selector()
{
  strip.setPixelColor(pixel, 50, 50, 50);
  strip.show();
  delay(10);
  if (buttonR.isReleased())
  {
    if (pixel == modos)
    {
      pixel = 0;
      colorWipe(strip.Color(0, 0, 0), 10);
    }
    pixel++;
  }
  if (buttonG.isReleased())
  {
    strip.setPixelColor(pixel, 100, 0, 0);
    strip.show();
    delay(1500);
    modo = pixel;
    pixel = 1;
    colorWipe(strip.Color(0, 0, 0), 10);
  }
}

void agregacolor()
{
  if (buttonR.isReleased())
  {
    if (colorR < 250)
    {
      colorR = colorR + 50;
    }
    else
    {
      colorR = 0;
    }
    colorWipe(strip.Color(colorR, colorG, colorB), 10);
  }
  if (buttonG.isReleased())
  {
    if (colorG < 250)
    {
      colorG = colorG + 50;
    }
    else
    {
      colorG = 0;
    }
    colorWipe(strip.Color(colorR, colorG, colorB), 10);
  }
  if (buttonB.isReleased())
  {
    if (colorB < 250)
    {
      colorB = colorB + 50;
    }
    else
    {
      colorB = 0;
    }
    colorWipe(strip.Color(colorR, colorG, colorB), 10);
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait)
{
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void checkbreak()
{
  if (digitalRead(3) == LOW && digitalRead(4) == LOW && digitalRead(5) == LOW)
  {
    colorWipe(strip.Color(0, 0, 0), 10); // all off
    colorR = 0;
    colorG = 0;
    colorB = 0;
    modo = 0;
    pixel = 1;
    delay(1000);
    asm volatile("jmp 0");
  }
}

void rainbow(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++)
  { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++)
    {
      checkbreak();
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos)
{
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85)
  {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170)
  {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void theaterChaseRainbow(uint8_t wait)
{
  for (int j = 0; j < 256; j++)
  { // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++)
    {
      for (int i = 0; i < strip.numPixels(); i = i + 3)
      {
        checkbreak();
        strip.setPixelColor(i + q, Wheel((i + j) % 255)); // turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i = 0; i < strip.numPixels(); i = i + 3)
      {
        strip.setPixelColor(i + q, 0); // turn every third pixel off
      }
    }
  }
}

void memory()
{
  checkbreak();
  if (memorypixel < PIXEL_COUNT)
  {
    if (buttonR.isReleased())
    {
      strip.setPixelColor(memorypixel, 100, 0, 0);
      strip.show();
      memorypixel++;
    }
    if (buttonG.isReleased())
    {
      strip.setPixelColor(memorypixel, 0, 100, 0);
      strip.show();
      memorypixel++;
    }
    if (buttonB.isReleased())
    {
      strip.setPixelColor(memorypixel, 0, 0, 100);
      strip.show();
      memorypixel++;
    }
  }
  if (memorypixel == PIXEL_COUNT)
  {
    memorypixel = 0;
    colorWipe(strip.Color(0, 0, 0), 10); // all off
  }
}
