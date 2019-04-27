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

#ifndef HSVCONVERTER_H
#define HSVCONVERTER_H

#include <stdint.h>

namespace HsvConverter
{
    /// \brief Get the RGB values from hue, saturation and value.
    /// \param hue          The hue of the color. The hue goes from 0 to 1529, 0 beeing 0 degrees and 1529 beeing 359.764... degrees.
    ///                     This means that each slice of 60 degrees has 255 values.
    /// \param saturation   The saturation of the color. The saturation goes from 0 to 255, 0 beeing 0% and 255 beeing 100%.
    /// \param value        The value of the color. The value goes from 0 to 255, 0 beeing 0% and 255 beeing 100%.
    /// \param [out] red    The variable in which the red value will be written.
    /// \param [out] green  The variable in which the green value will be written.
    /// \param [out] blue   The variable in which the blue value will be written.
    void getRgbFromHSV(uint16_t hue, uint8_t saturation, uint8_t value,
                       uint8_t& red, uint8_t& green, uint8_t& blue);

    /// \brief Get the color from hue, saturation and value.
    /// \param hue          The hue of the color. The hue goes from 0 to 1529, 0 beeing 0 degrees and 1529 beeing 359.764... degrees.
    ///                     This means that each slice of 60 degrees has 255 values.
    /// \param saturation   The saturation of the color. The saturation goes from 0 to 255, 0 beeing 0% and 255 beeing 100%.
    /// \param value        The value of the color. The value goes from 0 to 255, 0 beeing 0% and 255 beeing 100%.
    /// \return The concatenated RGB values organised like so: 0#R#G#B, where each component is 8 bits.
    ///         This is also known as the HEX of a color.
    uint32_t getColorFromHSV(uint16_t hue, uint8_t saturation, uint8_t value);

    /// \brief Concatenate the RGB values into a single variable.
    /// \param red      The red component of the color.
    /// \param green    The green component of the color.
    /// \param blue     The blue component of the color.
    /// \return The concatenated RGB values organised like so: 0#R#G#B, where each component is 8 bits.
    ///         This is also known as the HEX of a color.
    uint32_t getColorFromRgb(uint8_t red, uint8_t green, uint8_t blue);

    /// \brief Extract the red component of a color
    /// \param color The color from which the extraction is made.
    /// \return The red component of the color.
    uint8_t getRedValueFromColor(const uint32_t& color);

    /// \brief Extract the green component of a color
    /// \param color The color from which the extraction is made.
    /// \return The green component of the color.
    uint8_t getGreenValueFromColor(const uint32_t& color);

    /// \brief Extract the blue component of a color
    /// \param color The color from which the extraction is made.
    /// \return The blue component of the color.
    uint8_t getBlueValueFromColor(const uint32_t& color);

    static constexpr uint16_t maxHue = 6 * 255 - 1;
    static constexpr uint8_t maxSaturation = 255;
    static constexpr uint8_t maxValue = 255;
} // namespace HsvConverter

#endif // HSVCONVERTER_H
