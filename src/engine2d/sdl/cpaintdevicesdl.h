#ifndef CPAINTDEVICESDL_H
   #define CPAINTDEVICESDL_H

#include <ipaintdevice.h>

class CPaintDeviceSDL : public IPaintDevice
{
public:
   IPaintDevice *create(CPixmap *pixmap);
};

#endif //CPAINTDEVICESDL_H
