#ifndef CCOLOUR_H
   #define CCOLOUR_H

#include <cstdint>

class CColour
{
public:
   typedef uint32_t RGBA;
   typedef uint32_t RGB;
   
   CColour(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255);
   CColour(RGBA rgba);
   CColour(RGB rgb, uint8_t alpha);
   
   void setColour(RGBA rgba);
   
   inline void setRed(uint8_t red) { m_red = red; }
   inline void setGreen(uint8_t green) { m_green = green; }
   inline void setBlue(uint8_t blue) { m_blue = blue; }
   inline void setAlpha(uint8_t alpha) { m_alpha = alpha; }
   
   inline uint8_t getRed() const { return m_red; }
   inline uint8_t getGreen() const { return m_green; }
   inline uint8_t getBlue() const { return m_blue; }
   inline uint8_t getAlpha() const { return m_alpha; }
   
   friend bool operator==(const CColour &colour1, const CColour &colour2)
   {
      if(colour1.getRed()   == colour2.getRed() &&
         colour1.getGreen() == colour2.getGreen() &&
         colour1.getBlue()  == colour2.getBlue() &&
         colour1.getAlpha() == colour2.getAlpha())
      {
         return true;
      }
      else
      {
         return false;
      }
   }
private:
   uint8_t m_red;
   uint8_t m_green;
   uint8_t m_blue;
   uint8_t m_alpha;
};

#endif // CCOLOUR_H
