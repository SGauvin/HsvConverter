# HsvConverter
Fast HSV to RGB conversion library. The conversion does not make use of
floating-point arithmetic, so it is useful and significantly faster than
other libraries for hardware with no FPU like Arduinos.

Unlike the CHSV color of the FastLED librairy, the HSVConverter librairy does
not limit the hue value to a single byte to reprensent the whole 360 degrees,
but instead has a byte per 60 degrees, making it 6 times more accurate, but at a
speed cost for 8-bit architectures. This speed cost becomes negligeable in
minimally complex programs.

Here is a simple Arduino example to get started:

~~~~
#include "HsvConverter.h"

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    uint16_t hue = 0;
    while (true)
    {
        hue %= HsvConverter::maxHue;
        uint32_t color = HsvConverter::getColorFromHSV(hue++, 255, 255);
        uint8_t r = HsvConverter::getRedValueFromColor(color);
        uint8_t g = HsvConverter::getGreenValueFromColor(color);
        uint8_t b = HsvConverter::getBlueValueFromColor(color);

        Serial.print("Red: ");
        Serial.print(r);
        Serial.print(" Green: ");
        Serial.print(g);
        Serial.print(" Blue: ");
        Serial.print(b);
        Serial.print(" Color value: ");
        Serial.print(color);
        Serial.print("\n");
        
        delay(5);
    }
}
~~~~
