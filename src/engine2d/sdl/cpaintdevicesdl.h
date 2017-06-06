#ifndef CPAINTDEVICESDL_H
   #define CPAINTDEVICESDL_H

#include <SDL.h>

#include <ipaintdevice.h>

class CPaintDeviceSDL : public IPaintDevice
{
public:
   CPaintDeviceSDL(CPixmap *pixmap);
   ~CPaintDeviceSDL();
   
   bool start(CPixmap *pixmap);
   void drawRect(const CRectI &rect);
   bool end();
private:
   CPixmap *m_pPixmap;
};

#endif //CPAINTDEVICESDL_H
