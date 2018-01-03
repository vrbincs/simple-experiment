#ifndef CENGINEDEVICESDL_H
   #define CENGINEDEVICESDL_H

#include <ienginedevice.h>
#include <ieventlistener.h>

class CEventManager;
class CEngineDeviceLinuxPriv;

class CEngineDeviceLinux : public IEngineDevice, public IEventListener
{
public:
   CEngineDeviceLinux();
   virtual ~CEngineDeviceLinux();
   
   bool run();
   void exit();
   
   uint64_t getDeltaTicks() const;
   
   IVideoDevice *getVideoDevice();
   CEventManager *getEventManager();
   
   bool init(IVideoDevice::DeviceType renderType,
             const CSizeI &resolution);

   bool onEvent(const CEvent &event);
   
   void showFps(bool show = true);
private:
   CEngineDeviceLinuxPriv *m_engineDevicePriv;
   IVideoDevice *m_videoDevice;
   CEventSourceSDL *m_eventSourceSDL;
   CEventManager *m_eventManager;   
   bool m_engineRunning;
   bool m_showFps;
   void releaseVideoDevice();
   
   friend class IEngineDevice;
};

#endif
