#include "logging.h"
#include "ccolour.h"

CColour::CColour(RGBA rgba)
   : m_red(0),
     m_green(0),
     m_blue(0),
     m_alpha(255)
{
   setColour(rgba);
}

CColour::CColour(RGB rgb, uint8_t alpha)
   : m_red(0),
     m_green(0),
     m_blue(0),
     m_alpha(255)
{
   setColour(rgb);
   setAlpha(alpha);
}

CColour::CColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
   : m_red(red),
     m_green(green),
     m_blue(blue),
     m_alpha(alpha)
{
}

void CColour::setColour(RGBA rgba)
{
#ifdef __ORDER_LITTLE_ENDIAN__
   m_alpha = ((rgba & 0xFF000000) >> 24);
   m_blue  = ((rgba & 0x00FF0000) >> 16);
   m_green = ((rgba & 0x0000FF00) >>  8);
   m_red   = ((rgba & 0x000000FF) >>  0);
#else
   m_red   = ((rgba & 0xFF000000) >> 24);
   m_green = ((rgba & 0x00FF0000) >> 16);
   m_blue  = ((rgba & 0x0000FF00) >>  8);
   m_alpha = ((rgba & 0x000000FF) >>  0);
#endif
}
