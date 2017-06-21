#ifndef CPAINTTOOL_H
   #define CPAINTTOOL_H

#include <crect.h>
#include <cpoint.h>

class IPaintDevice;
class CPixmap;

class CPaintTool
{
public:
   CPaintTool(CPixmap *pixmap);
   CPaintTool(IPaintDevice *paintDevice);
   virtual ~CPaintTool();
   
   bool start(CPixmap *pixmap);
   void drawRect(const CRectI &rect);
   void drawPixmap(const CPixmap &pixmap, const CPointI &pos, const CRectI *srcRect = NULL);
   void drawText(const std::string &text,
                 const CRectI &rect);
   bool end();
private:
   IPaintDevice *m_pPaintDevice;
};

#endif // CPAINTTOOL_H
