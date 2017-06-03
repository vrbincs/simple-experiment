#ifndef IENGINEDEVICE_H
   #define IENGINEDEVICE_H

#include <list>
#include <csize.h>

class IVideoDevice;

class IEngineDevice
{
public:
   virtual ~IEngineDevice(){}
   
   virtual IVideoDevice *getVideoDevice() = 0;
   virtual std::list<CSizeI> getVideoModeList() = 0;
};

#endif // IENGINEDEVICE_H
