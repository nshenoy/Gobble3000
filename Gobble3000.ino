#include <Adafruit_NeoPixel.h>

#define PIN 2

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);
int onBoardLed = 1;

void setup() 
{
  pinMode(onBoardLed, OUTPUT);
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  int neoPixelBrightness = 0;
  int onBoardLedValue = LOW;
  
  for(int i = 0; i < 510; i++)
  {
    // Set NeoPixel brightness
    if (i > 255)
    {
      neoPixelBrightness = 255 - (i - 255);
      onBoardLedValue = LOW;
    }
    else
    {
      neoPixelBrightness = i;
      onBoardLedValue = HIGH;
    }
    
    strip.setPixelColor(0, strip.Color(neoPixelBrightness, 0, 0));
    
    // Set NeoPixel to Yellow
    strip.setPixelColor(1, strip.Color(255, 255, 0));
    
    strip.show();
    digitalWrite(onBoardLed, onBoardLedValue);
    
    delay(2);
  }
}

