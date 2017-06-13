#ifndef CPAINTTOOL_H
   #define CPAINTTOOL_H

#include <crect.h>
#include <cpixmap.h>

class IPaintDevice;

class CPaintTool
{
public:
   CPaintTool(IPaintSurface *surface);
   virtual ~CPaintTool();
   
   bool start(IPaintSurface *surface);
   void drawRect(const CRectI &rect);
   void drawPixmap(const CPixmap &pixmap, const CPointI &pos);
   bool end();
private:
   IPaintDevice *m_pPaintDevice;
};

#endif // CPAINTTOOL_H
