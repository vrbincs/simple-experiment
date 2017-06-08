#ifndef CPAINTTOOL_H
   #define CPAINTTOOL_H

#include <crect.h>
#include <cpixmap.h>

class CPaintTool
{
public:
   CPaintTool(CPixmap *pixmap);
   virtual ~CPaintTool();
   
   bool start(CPixmap *pixmap);
   void drawRect(const CRectI &rect);
   bool end();
private:
   CPixmap *m_pPixmap;
};

#endif // CPAINTTOOL_H
