#ifndef CPAINTTOOL_H
   #define CPAINTTOOL_H

#include <crect.h>
#include <cpixmap.h>

class IPaintDevice;

class CPaintTool
{
public:
   CPaintTool(CPixmap *pixmap);
   virtual ~CPaintTool();
   
   bool start(CPixmap *pixmap);
   void drawRect(const CRectI &rect);
   bool end();
private:
   IPaintDevice *m_pPaintDevice;
};

#endif // CPAINTTOOL_H
