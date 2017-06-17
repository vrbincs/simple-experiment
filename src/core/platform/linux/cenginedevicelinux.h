#ifndef CENGINEDEVICESDL_H
   #define CENGINEDEVICESDL_H

#include <ienginedevice.h>
#include <ieventlistener.h>

class CEventManager;

class CEngineDeviceLinux : public IEngineDevice, public IEventListener
{
public:
   CEngineDeviceLinux();
   virtual ~CEngineDeviceLinux();
   
   bool run();
   void exit();
   
   IVideoDevice *getVideoDevice();
   CEventManager *getEventManager();
   
   bool setRenderer(IVideoDevice::DeviceType renderType,
                    const CSizeI &resolution);

   bool onEvent(const CEvent &event);
private:
   IVideoDevice *m_videoDevice;
   CEventSourceSDL *m_eventSourceSDL;
   CEventManager *m_eventManager;   
   bool m_engineRunning;
   
   void releaseVideoDevice();
   
   friend class IEngineDevice;
};

#endif
