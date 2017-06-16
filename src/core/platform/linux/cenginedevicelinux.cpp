#include <unistd.h>

#include <cstddef>

#include "logging.h"

#include "cvideodevicesdl.h"
#include "ceventmanager.h"
#include "ieventsource.h"
#include "cevent.h"
#include "ceventsourcesdl.h"
#include "cenginedevicelinux.h"

static IEngineDevice *l_engineDeviceInstance = NULL;

CEngineDeviceLinux::CEngineDeviceLinux()
   : m_videoDevice(NULL),
     m_eventSourceSDL(new CEventSourceSDL()),
     m_eventManager(new CEventManager()),
     m_engineRunning(true)
{
   m_eventManager->registerEventSource(m_eventSourceSDL);
   m_eventManager->registerListener(this);
}

CEngineDeviceLinux::~CEngineDeviceLinux()
{
   m_eventManager->unregisterListener(this);
   m_eventManager->unregisterEventSource(m_eventSourceSDL);
   
   delete m_eventManager;
   m_eventManager = NULL;
   
   delete m_eventSourceSDL;
   m_eventSourceSDL = NULL;
   
   releaseVideoDevice();
}

bool CEngineDeviceLinux::run()
{
   m_eventManager->pollEvents();
   
   if(m_engineRunning)
   {
      usleep(40000);
      return true;
   }
   
   return false;
}

IVideoDevice *CEngineDeviceLinux::getVideoDevice()
{
   return m_videoDevice;
}

bool CEngineDeviceLinux::setRenderer(IVideoDevice::DeviceType renderType,
                                     const CSizeI &resolution)
{
   releaseVideoDevice();
   
   switch(renderType)
   {
      case IVideoDevice::DeviceTypeSdl:
      {
         if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
         {
            LOGGER_ERROR("Unable to initialize SDL. err=" << SDL_GetError());
            return false;
         }
         
         m_videoDevice = new CVideoDeviceSDL(resolution);
         return true;
      }
      break;
      default:
      break;
   }
   
   return false;
}

bool CEngineDeviceLinux::onEvent(const CEvent &event)
{
   if(event.type() == CEvent::EventTypeTerminate)
   {
      m_engineRunning = false;
      return true;
   }
   
   return false;
}

void CEngineDeviceLinux::releaseVideoDevice()
{
   if(m_videoDevice)
   {
      delete m_videoDevice;
      m_videoDevice = NULL;
   }
}

IEngineDevice *IEngineDevice::instance()
{
   if(l_engineDeviceInstance == NULL)
   {
      l_engineDeviceInstance = new CEngineDeviceLinux();
   }
   
   return l_engineDeviceInstance;
}
