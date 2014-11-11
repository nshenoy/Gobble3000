/// Gobble3000
/// Description: A silly first grade school project that manipulates a few LEDs using an Adafruit Gemma and Adafruit NeoPixels.
///                This is all to light up a picture of a turkey for Thanksgiving. Yes, really. The first NeoPixel will be red 
///                and fade with a breathing effect, while the second NeoPixel will hold a steady yellow. The onboard LED on the Gemma
///                is set to blink.

#include <Adafruit_NeoPixel.h>

#define PIN             2    // Pin used for communicating with the NewPixel chain
#define MAXBRIGHTNESS   255  // Maximum brightness value for the NeoPixel
const int _onBoardLed = 1;   // Pin used for communicating with the onboard LED

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel _strip = Adafruit_NeoPixel(2, PIN, NEO_GRB + NEO_KHZ800);

void setup() 
{
    pinMode(_onBoardLed, OUTPUT);

    // Setup the NeoPixels
    _strip.begin();
    _strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
    const int MAXLOOPCOUNT = 1;    // Adjust this value to set the breathing effect to your taste
    int neoPixelBrightness = 0;
    int onBoardLedValue = LOW;

    // Set the second NeoPixel to Yellow
    _strip.setPixelColor(1, _strip.Color(255, 150, 0));

    // This outer loop gives a better "breathing" effect when fading the first NeoPixel.
    // By skipping an iteration or two (configuraable via the MAXLOOPCOUNT value), it gives a nice
    //  pause between the "exhale" and the subsequent "inhale".
    for(int outerloop = 0; outerloop < MAXLOOPCOUNT; outerloop++)
    {
        // Set NeoPixel brightness for the breathing fade effect
        for(int i = 0; i < (MAXBRIGHTNESS * 2); i++)
        {
            if (i > MAXBRIGHTNESS)
            {
                // Inhale
                neoPixelBrightness = MAXBRIGHTNESS - (i - MAXBRIGHTNESS);
                onBoardLedValue = LOW;
            }
            else
            {
                // Exhale
                neoPixelBrightness = i;
                onBoardLedValue = HIGH;
            }

            // Only change the NeoPixel if we're on the first iteration of the outerloop
            if(outerloop == 0)
            {
                _strip.setPixelColor(0, _strip.Color(neoPixelBrightness, 0, 0));
            }

            _strip.show();

            digitalWrite(_onBoardLed, onBoardLedValue);

            delay(5);
        }
    }
}
