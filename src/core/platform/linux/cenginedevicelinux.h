#ifndef CENGINEDEVICESDL_H
   #define CENGINEDEVICESDL_H

#include <ienginedevice.h>
#include <ieventlistener.h>

class CEventManager;
class CEngineDeviceLinuxPriv;

class CEngineDeviceLinux : public IEngineDevice
{
public:
   CEngineDeviceLinux();
   virtual ~CEngineDeviceLinux();
   
   void run() override;
   void exit() override;
   
   uint64_t getDeltaTicks() const override;
   uint64_t getTimestamp() const override;
   
   IVideoDevice *getVideoDevice() override;
   
   bool init(IVideoDevice::DeviceType renderType,
             const CSizeI &resolution) override;

   void showFps(bool show = true) override;  
   
   void registerGameDelegate(IGameDelegate *gameDelegate) override; 
protected:
   IEventFactory *getKeyEventFactory() override;
private:
   CEngineDeviceLinuxPriv *m_engineDevicePriv;
   IVideoDevice *m_videoDevice;
   bool m_engineRunning;
   bool m_showFps;
   void releaseVideoDevice();
   
   friend class IEngineDevice;
};

#endif
