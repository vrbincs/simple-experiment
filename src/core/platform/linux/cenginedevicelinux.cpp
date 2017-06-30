#include <unistd.h>

#include <cstddef>

#include "logging.h"

#include "cvideodevicesdl.h"
#include "ceventmanager.h"
#include "ieventsource.h"
#include "cevent.h"
#include "ceventsourcesdl.h"
#include "cenginedevicelinux.h"
#include "cpainttool.h"

#include <cdigitool.h>

#define FPS_TO_MILIS(fps) (1000/((uint64_t)fps))

static IEngineDevice *l_engineDeviceInstance = NULL;
static CColour l_backgroundColour;

class CEngineDeviceLinuxPriv
{
public:
   const uint32_t m_targetFps;
   uint64_t m_lastTick;
   uint64_t m_elapsedTicks;
   uint32_t m_currentFps;
   CDigiTool *m_digitool;
   
   CEngineDeviceLinuxPriv()
      : m_targetFps(FPS_TO_MILIS(64)),
        m_lastTick(0),
        m_elapsedTicks(m_targetFps),
        m_currentFps(m_targetFps),
        m_digitool(NULL)
   {
      m_lastTick = getCurrentTicks();
   }
   
   ~CEngineDeviceLinuxPriv()
   {
      delete m_digitool;
   }
   
   uint64_t getCurrentTicks()
   {
      uint64_t ticks = 0;
      struct timespec tp;
      clock_gettime(CLOCK_MONOTONIC, &tp);
      
      ticks = ((uint64_t)tp.tv_sec * 1000) + (tp.tv_nsec / 1000000);
      return ticks;
   }
   
   void cycle()
   {
      uint64_t currentTicks = getCurrentTicks();
      m_elapsedTicks = (currentTicks - m_lastTick);
      m_lastTick = currentTicks;
   }
   
   inline uint64_t getTicks() const
   {
      return m_elapsedTicks;
   }
   
   void maintainFPS()
   {
      uint64_t currentTicks = getCurrentTicks();
      uint64_t nextTicks =  (m_lastTick + m_currentFps);
      uint64_t sleepDuration = 1;
      
      if(currentTicks < nextTicks)
      {
         sleepDuration = (nextTicks - currentTicks);
      }
      
      //TODO: the execution of the main thread is blocked at this point,
      // so a potential of one core is wasted. Something needs to be
      // done about it. ;)
      usleep(sleepDuration*1000);
      cycle();
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
         m_digitool->drawDigits(*paintTool, 1000/getTicks());
      }
      paintTool->restore();
   }
};

CEngineDeviceLinux::CEngineDeviceLinux()
   : m_engineDevicePriv(new CEngineDeviceLinuxPriv()),
     m_videoDevice(NULL),
     m_eventSourceSDL(new CEventSourceSDL()),
     m_eventManager(new CEventManager()),
     m_engineRunning(true),
     m_showFps(false)
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
      
      m_engineDevicePriv->maintainFPS();
      m_videoDevice->end();
      
      m_eventManager->pollEvents();
      
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

uint64_t CEngineDeviceLinux::getTicks() const
{
   return m_engineDevicePriv->getTicks();
}

IVideoDevice *CEngineDeviceLinux::getVideoDevice()
{
   return m_videoDevice;
}

CEventManager *CEngineDeviceLinux::getEventManager()
{
   return m_eventManager;
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

void CEngineDeviceLinux::showFps(bool show)
{
   m_showFps = show;
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
