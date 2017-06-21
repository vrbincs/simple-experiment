#ifndef CDIGITOOL_H
   #define CDIGITOOL_H

#include <ccolour.h>

class CPaintTool;
class CPixmap;

class CDigiTool
{
public:
   CDigiTool(const CColour & colour);
   ~CDigiTool();
   
   bool isNull() const;
   bool drawDigits(CPaintTool &paintTool, uint32_t number);
private:
   CColour m_colour;
   CPixmap *m_pixmap;
   
   void loadXBMPixmap();
};

#endif //CDIGITOOL_H
