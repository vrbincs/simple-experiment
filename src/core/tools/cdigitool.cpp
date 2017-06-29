#include <cstring>
#include <string>

#include <logging.h>
#include <cpixmap.h>
#include <cpainttool.h>

#include "cdigitool.h"

extern uint32_t cdigitsbitmap_width;
extern uint32_t cdigitsbitmap_height;
extern uint8_t cdigitsbitmap_bits[];

uint32_t digitWidth = (cdigitsbitmap_width / 10);


CDigiTool::CDigiTool(const CColour &colour)
   : m_colour(colour),
     m_pixmap(NULL)
{
   loadXBMPixmap();
}

CDigiTool::~CDigiTool()
{
   delete m_pixmap;
}
   
bool CDigiTool::isNull() const
{
   return (m_pixmap == NULL);
}

bool CDigiTool::drawDigits(CPaintTool &paintTool, uint32_t number)
{
   if(m_pixmap)
   {
      std::string numberStr = std::to_string(number);
      int digit;
      
      CPointF digitPosition;
      for(auto it=numberStr.begin(); it!=numberStr.end(); it++)
      {
         digit = (*it - '0');
         CRectF srcRect((digit * digitWidth),
                        0,
                        digitWidth,
                        cdigitsbitmap_height);
         
         paintTool.drawPixmap(*m_pixmap, digitPosition, &srcRect);
         digitPosition.m_x += digitWidth;
      }
      
      return true;
   }
   
   return false;
}

void CDigiTool::loadXBMPixmap()
{
   const uint32_t size = (cdigitsbitmap_width * cdigitsbitmap_height * 3);
   uint8_t *pixels = new uint8_t[size];
   memset(pixels, 0, size);
   
   uint8_t *pixelTmp = pixels;
   uint8_t *pixelVal = cdigitsbitmap_bits;
   
   for(uint32_t i=0; i<((cdigitsbitmap_width * cdigitsbitmap_height) / 8); i++)
   {
      for(int j=0; j<8; j++)
      {
         if(((*pixelVal >> j) & 0x1) == 0)
         {
            *(pixelTmp++) = (m_colour.getRed());
            *(pixelTmp++) = (m_colour.getGreen());
            *(pixelTmp++) = (m_colour.getBlue());
         }
         else
         {
            pixelTmp += 3;
         }
      }
      pixelVal++;
   }
   
   m_pixmap = new CPixmap(pixels,
                          cdigitsbitmap_width,
                          cdigitsbitmap_height,
                          24);
}
