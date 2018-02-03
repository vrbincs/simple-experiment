#include <unistd.h>

#include <cstddef>

#include "logging.h"
LOGGING_INIT("CEngine2D")

#include "cvideodevicesdl.h"
#include "cvideodevicepseudo.h"
#include "ieventfactory.h"
#include "cevent.h"
#include "cenginedevicelinux.h"
#include "cpainttool.h"
#include "ckeyeventfactorysdl.h"
#include "igamedelegate.h"

#include <tools/cdigitool.h>

#define FPS_TO_MICRO(fps) (1000000/((double)fps))

static IEngineDevice *l_engineDeviceInstance = NULL;

const int TICKS_PER_SECOND = 30;
const int SKIP_TICKS = 1000000 / TICKS_PER_SECOND;
const int MAX_CYCLES_SKIP = 5;
const int FPS = (1000000 / 60);

class CEngineDeviceLinuxPriv
{
public:
   uint64_t m_currentTicks;
   uint64_t m_deltaTicks;
   CDigiTool *m_digitool;
   
   uint64_t m_simulationTicks;
   
   IEventFactory *m_keyEventFactory;
   IGameDelegate *m_gameDelegate;
   
   CColour m_backgroundColour;
   
   CEngineDeviceLinuxPriv()
      : m_deltaTicks(0),
        m_digitool(NULL),
        m_keyEventFactory(new CKeyEventFactorySDL()),
        m_gameDelegate(NULL)
   {
      m_simulationTicks = m_currentTicks = getCurrentTicks();
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
      clock_gettime(CLOCK_REALTIME, &tp);
      
      ticks = ((uint64_t)tp.tv_sec * 1000000) + (tp.tv_nsec / 1000);
      return ticks;
   }
   
   inline uint64_t getDeltaTicks() const
   {
      return m_deltaTicks;
   }
   
   inline void cycle() 
   {
      uint64_t ticks = getCurrentTicks();
      m_deltaTicks = ticks - m_currentTicks;
      m_currentTicks = ticks;
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
         
         uint64_t fps = 0;
         if(m_deltaTicks > 0)
         {
            fps = (1000000 / m_deltaTicks);
         }
         
         m_digitool->drawDigits(*paintTool, fps);
      }
      paintTool->restore();
   }
   
   
   void updateLogic()
   {
      if(m_gameDelegate)
      {
         while(m_simulationTicks < m_currentTicks)
         {
            m_simulationTicks += SKIP_TICKS;
            m_gameDelegate->processLogic(SKIP_TICKS);
         }
      }
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

void CEngineDeviceLinux::run()
{
   m_engineRunning = true;
   
   while(m_engineRunning && m_videoDevice)
   {
      m_engineDevicePriv->cycle();
      
      // Poll keyboard events
      m_engineDevicePriv->m_keyEventFactory->poll();
      
      // Update game logic
      m_engineDevicePriv->updateLogic();
      
      // render graphics
      m_videoDevice->start();
      if(m_engineDevicePriv->m_gameDelegate)
      {
         m_engineDevicePriv->m_gameDelegate->render();
         
         if(m_showFps)
         {
            m_engineDevicePriv->drawFps();
         }
      }
      m_videoDevice->end();
   }
   
   m_engineRunning = false;
}

void CEngineDeviceLinux::exit()
{
   m_engineRunning = false;
}

uint64_t CEngineDeviceLinux::getDeltaTicks() const
{
   return m_engineDevicePriv->getDeltaTicks();
}

uint64_t CEngineDeviceLinux::getTimestamp() const
{
   return m_engineDevicePriv->getCurrentTicks();
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

void CEngineDeviceLinux::registerGameDelegate(IGameDelegate *gameDelegate)
{
   m_engineDevicePriv->m_gameDelegate = gameDelegate;
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
