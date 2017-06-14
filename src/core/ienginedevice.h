#ifndef IENGINEDEVICE_H
   #define IENGINEDEVICE_H

#include <list>
#include <csize.h>
#include <ivideodevice.h>

class IVideoDevice;

class IEngineDevice
{
public:
   virtual ~IEngineDevice(){}
   
   virtual bool run() = 0;
   virtual IVideoDevice *getVideoDevice() = 0;
   virtual std::list<CSizeI> getVideoModeList() = 0;
private:
   virtual bool setRenderer(IVideoDevice::DeviceType renderType,
                            const CSizeI &resolution) = 0;
   
   /**
    * \brief return an instance of the IEngineDevice. This class is 
    * singeton, so this function should always return the same instance
    * of the object
    * 
    * \return returns a pointer of IEngineDevice
    */
   static IEngineDevice *instance();
   friend class CEngine2d;
};

#endif // IENGINEDEVICE_H
