#include <FastLED.h>

#define LED_PIN     6
#define NUM_LEDS    256
#define BRIGHTNESS  48
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int quadrant = 1;

// Params for width and height
const uint8_t kMatrixWidth = 16;
const uint8_t kMatrixHeight = 16;

// Param for different pixel layouts
const bool    kMatrixSerpentineLayout = true;
const bool    kMatrixVertical = true;

void setup() 
{
    Serial.begin(115200);
    while (!Serial) ;

    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
}

uint16_t XY( uint8_t x, uint8_t y)
{
    uint16_t i;

    if( kMatrixSerpentineLayout == false)
    {
        if (kMatrixVertical == false)
        {
            i = (y * kMatrixWidth) + x;
        }
        else
        {
            i = kMatrixHeight * (kMatrixWidth - (x+1))+y;
        }
    }

    if( kMatrixSerpentineLayout == true)
    {
        if (kMatrixVertical == false)
        {
            if( y & 0x01)
            {
                // Odd rows run backwards
                uint8_t reverseX = (kMatrixWidth - 1) - x;
                i = (y * kMatrixWidth) + reverseX;
            }
            else
            {
                // Even rows run forwards
                i = (y * kMatrixWidth) + x;
            }
        }
        else 
        { // vertical positioning
            if ( x & 0x01)
            {
                i = kMatrixHeight * (kMatrixWidth - (x+1))+y;
            }
            else
            {
                i = kMatrixHeight * (kMatrixWidth - x) - (y+1);
            }
        }
    }
    Serial.print("LED # ");
    Serial.println(i);
    return i;
}

void loop()
{
    int x,y;
    switch (quadrant)
    {
        case 1:
            for (x=0; x<8; x++)
            {
                for (y=0; y<8; y++)
                {
                    Serial.print(x);
                    Serial.print(" , ");
                    Serial.println(y);
                    leds[XY(x,y)] = CRGB::Red;
                }
            }
 //           Serial.println("Quadrant 1 complete");
            break;
        case 2:
            for (x=0; x<8; x++)
            {
                for (y=8; y<16; y++)
                {
                    Serial.print(x);
                    Serial.print(" , ");
                    Serial.println(y);
                    leds[XY(x,y)] = CRGB::Red;
                }
            }
            // Serial.println("Quadrant 2 complete");
            break;
        case 3:
            for (x=8; x<16; x++)
            {
                for (y=0; y<8; y++)
                {
                    Serial.print(x);
                    Serial.print(" , ");
                    Serial.println(y);
                    leds[XY(x,y)] = CRGB::Red;
                }
            }
 //           Serial.println("Quadrant 1 complete");
            break;
        case 4:
            for (x=8; x<16; x++)
            {
                for (y=8; y<16; y++)
                {
                    Serial.print(x);
                    Serial.print(" , ");
                    Serial.println(y);
                    leds[XY(x,y)] = CRGB::Red;
                }
            }
 //           Serial.println("Quadrant 1 complete");
            break;
    }
    quadrant+=1;
    // Serial.println(quadrant);
    if (quadrant == 5) 
    {
        quadrant = 1;
        // Serial.println(quadrant);
    }
    FastLED.show();
    delay(1000);
    FastLED.clear(true);
    // Serial.println("should be changing quadrant");
}