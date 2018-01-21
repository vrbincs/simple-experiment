#include <unistd.h>

#include <cstddef>

#include "logging.h"

#include "cvideodevicesdl.h"
#include "cvideodevicepseudo.h"
#include "ieventfactory.h"
#include "cevent.h"
#include "cenginedevicelinux.h"
#include "cpainttool.h"
#include "ckeyeventfactorysdl.h"

#include <tools/cdigitool.h>

#define FPS_TO_MICRO(fps) (1000000/((double)fps))

static IEngineDevice *l_engineDeviceInstance = NULL;
static CColour l_backgroundColour;

class CEngineDeviceLinuxPriv
{
public:
   const uint32_t m_targetFps;
   uint64_t m_lastTick;
   uint64_t m_deltaTicks;
   uint32_t m_currentFps;
   CDigiTool *m_digitool;
   
   IEventFactory *m_keyEventFactory;
   
   CEngineDeviceLinuxPriv()
      : m_targetFps(FPS_TO_MICRO(60)),
        m_lastTick(0),
        m_deltaTicks(m_targetFps),
        m_currentFps(m_targetFps),
        m_digitool(NULL),
        m_keyEventFactory(new CKeyEventFactorySDL())
   {
      m_lastTick = getCurrentTicks();
   }
   
   ~CEngineDeviceLinuxPriv()
   {
      delete m_digitool;
      delete m_keyEventFactory;
   }
   
   uint64_t getCurrentTicks()
   {
      uint64_t ticks = 0;
      struct timespec tp;
      clock_gettime(CLOCK_MONOTONIC, &tp);
      
      ticks = ((uint64_t)tp.tv_sec * 1000000) + (tp.tv_nsec / 1000);
      return ticks;
   }
   
   inline uint64_t getDeltaTicks() const
   {
      return m_deltaTicks;
   }
   
   void maintainFPS()
   {
      uint64_t currentTicks = getCurrentTicks();
      uint64_t nextTicks = (m_lastTick + m_currentFps);
      uint64_t sleepDuration = 1;
      
      if(currentTicks < nextTicks)
      {
         sleepDuration = (nextTicks - currentTicks);
      }
      else
      {
         nextTicks += (currentTicks - nextTicks);
      }
      
      m_deltaTicks = (nextTicks - m_lastTick);
      m_lastTick = nextTicks;
      
      usleep(sleepDuration);
   }
   
   void drawFps()
   {
      CPaintTool *paintTool = l_engineDeviceInstance->getVideoDevice()->getScreenPaintTool();
      paintTool->save();
      if(paintTool)
      {
         if(m_digitool == NULL)
         {
            m_digitool = new CDigiTool(CColour(150,0,0,255));
         }
         m_digitool->drawDigits(*paintTool, 1000000/getDeltaTicks());
      }
      paintTool->restore();
   }
};

CEngineDeviceLinux::CEngineDeviceLinux()
   : m_engineDevicePriv(new CEngineDeviceLinuxPriv()),
     m_videoDevice(NULL),
     m_engineRunning(true),
     m_showFps(false)
{
}

CEngineDeviceLinux::~CEngineDeviceLinux()
{
   releaseVideoDevice();
   
   delete m_engineDevicePriv;
}

bool CEngineDeviceLinux::run()
{
   if(m_engineRunning && m_videoDevice)
   {
      if(m_showFps)
      {
         m_engineDevicePriv->drawFps();
      }
      
      m_videoDevice->end();
      m_engineDevicePriv->maintainFPS();
      
      // Poll keyboard events
      m_engineDevicePriv->m_keyEventFactory->poll();
      
      m_videoDevice->start(&l_backgroundColour);
      return true;
   }
   
   return false;
}

void CEngineDeviceLinux::exit()
{
   delete l_engineDeviceInstance;
   l_engineDeviceInstance = NULL;
}

uint64_t CEngineDeviceLinux::getDeltaTicks() const
{
   return m_engineDevicePriv->getDeltaTicks();
}

IVideoDevice *CEngineDeviceLinux::getVideoDevice()
{
   return m_videoDevice;
}

bool CEngineDeviceLinux::init(IVideoDevice::DeviceType renderType,
                              const CSizeI &resolution)
{
   releaseVideoDevice();
   
   switch(renderType)
   {
      case IVideoDevice::DeviceTypeSdl:
      {
         m_videoDevice = CVideoDeviceSDL::create(resolution);
         return true;
      }
      break;
      case IVideoDevice::DeviceTypePseudo:
         m_videoDevice = new CVideoDevicePseudo(resolution);
         return true;
      break;
      default:
         LOGGER_ERROR("The requested render type not supported. renderType=" << renderType);
      break;
   }
   
   return false;
}

void CEngineDeviceLinux::showFps(bool show)
{
   m_showFps = show;
}

IEventFactory *CEngineDeviceLinux::getKeyEventFactory()
{
   return m_engineDevicePriv->m_keyEventFactory;
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
