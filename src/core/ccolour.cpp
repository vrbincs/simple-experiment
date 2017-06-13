#include <ccolour.h>

CColour::CColour(RGBA rgba)
   : m_red(rgba >> 24 & 0x000000FF),
     m_green(rgba >> 16 & 0x000000FF),
     m_blue(rgba >>  8 & 0x000000FF),
     m_alpha(rgba & 0x000000FF)
{
}

CColour::CColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
   : m_red(red),
     m_green(green),
     m_blue(blue),
     m_alpha(alpha)
{
}
