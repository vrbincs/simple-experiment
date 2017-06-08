#ifndef CPAINTDEVICESDL_H
   #define CPAINTDEVICESDL_H

#include <SDL.h>

#include <ipaintdevice.h>

class CPaintDeviceSDL : public IPaintDevice
{
public:
   CPaintDeviceSDL(CPixmap *destPixmap);
   ~CPaintDeviceSDL();
   
   bool start(CPixmap *destPixmap);
   void drawRect(const CRectI &rect);
   bool end();
   
   IPaintSurface *createPaintSurface() const;
   IPaintDevice *getPaintDevice() const;
private:
   CPixmap *m_pDestPixmap;
};

#endif //CPAINTDEVICESDL_H
