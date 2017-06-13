#ifndef CCOLOUR_H
   #define CCOLOUR_H

#include <cstdint>

class CColour
{
public:
   typedef uint32_t RGBA;
   
   CColour(RGBA rgba);
   CColour(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
   
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
