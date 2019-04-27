////////////////////////////////////////////////////////////
//
// Copyright (c) <2019> Simon Gauvin (gauvinsimon@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
////////////////////////////////////////////////////////////

#include "HsvConverter.h"

namespace HsvConverter
{
    namespace
    {
        uint8_t getColorValueFromSaturation(uint8_t color, uint8_t saturation)
        {
            uint8_t colorAddition = static_cast<uint16_t>((255 - saturation)) * (255 - color) / 255;
            return color + colorAddition;
        }
    } // namespace

    void getRgbFromHSV(uint16_t hue, uint8_t saturation, uint8_t value,
                       uint8_t& red, uint8_t& green, uint8_t& blue)
    {
        static constexpr uint16_t maxHue = 6 * 255;
        hue %= maxHue;
    
        // This variable is to know on which part of the rgb graph we are
        // 0 = [0, 59], 1 = [60, 119] ... 5 = [0, 359]
        // https://en.wikipedia.org/wiki/HSL_and_HSV#/media/File:HSV-RGB-comparison.svg
        uint8_t graphSection = hue / 255;
    
        const uint8_t valueInGraphPortion = hue % 255; // Aka hue % 60
        uint32_t r, g, b;
        switch (graphSection)
        {
        case 0: // 0 to 59 degrees
            red = value;
            green = getColorValueFromSaturation(valueInGraphPortion, saturation) * static_cast<uint16_t>(value) / 255;
            blue = (255 - saturation) * static_cast<uint16_t>(value) / 255;
            break;
        case 1: // 60 to 119 degrees
            red = getColorValueFromSaturation(255 - valueInGraphPortion, saturation) * static_cast<uint16_t>(value) / 255;
            green = value;
            blue = (255 - saturation) * static_cast<uint16_t>(value) / 255;
            break;
        case 2: // 120 to 179 degrees
            red = (255 - saturation) * static_cast<uint16_t>(value) / 255;
            green = value;
            blue = getColorValueFromSaturation(valueInGraphPortion, saturation) * static_cast<uint16_t>(value) / 255;
            break;
        case 3: // 180 to 239 degrees
            red = (255 - saturation) * static_cast<uint16_t>(value) / 255;
            green = getColorValueFromSaturation(255 - valueInGraphPortion, saturation) * static_cast<uint16_t>(value) / 255;
            blue = value;
            break;
        case 4:// 240 to 299 degrees
            red = getColorValueFromSaturation(valueInGraphPortion, saturation) * static_cast<uint16_t>(value) / 255;
            green = (255 - saturation) * static_cast<uint16_t>(value) / 255;
            blue = value;
            break;
        case 5: // 300 to 360 degrees
            red = value;
            green = (255 - saturation) * static_cast<uint16_t>(value) / 255;
            blue = getColorValueFromSaturation(255 - valueInGraphPortion, saturation) * static_cast<uint16_t>(value) / 255;
            break;
        }
    }
    
    uint32_t getColorFromHSV(uint16_t hue, uint8_t saturation, uint8_t value)
    {
        uint8_t r, g, b;
        getRgbFromHSV(hue, saturation, value, r, g, b);
        return getColorFromRgb(r, g, b);
    }

    uint32_t getColorFromRgb(uint8_t red, uint8_t green, uint8_t blue)
    {
        return (static_cast<uint32_t>(red) << 16) | (static_cast<uint16_t>(green) << 8) | blue;
    }

    uint8_t getRedValueFromColor(const uint32_t& color)
    {
        return (color & 0xFF0000) >> 16;
    }

    uint8_t getGreenValueFromColor(const uint32_t& color)
    {
        return (color & 0xFF00) >> 8;
    }

    uint8_t getBlueValueFromColor(const uint32_t& color)
    {
        return color & 0xFF;
    }
} // namespace HsvConverter
