#ifndef CCOLOUR_H
   #define CCOLOUR_H

#include <cstdint>

class CColour
{
public:
   typedef uint32_t RGBA;
   
   CColour(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255);
   CColour(RGBA rgba);
   
   inline uint8_t getRed() const { return m_red; }
   inline uint8_t getGreen() const { return m_green; }
   inline uint8_t getBlue() const { return m_blue; }
   inline uint8_t getAlpha() const { return m_alpha; }
private:
   uint8_t m_red;
   uint8_t m_green;
   uint8_t m_blue;
   uint8_t m_alpha;
};

#endif // CCOLOUR_H
