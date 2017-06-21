#include <cengine2d.h>
#include <cmath>
#include <logging.h>

static bool l_endProgram = false;   
static int ballx = 0;
static int bally = 0;

static bool m_leftDown  = false;
static bool m_rightDown = false;
static bool m_upDown    = false;
static bool m_downDown  = false;

class CTestEventListener : public IEventListener
{
public:
   bool onEvent(const CEvent &event)
   {
      bool isKeyDown = (event.type() == CEvent::EventTypeKeyDown);
      
      if(isKeyDown || event.type() == CEvent::EventTypeKeyUp )
      {
         if(event.message().keyCode == CEvent::KeyEscape)
         {
            LOGGER_INFO(event.message().keyCode);
            l_endProgram = true;
         }
         else if(event.message().keyCode == CEvent::KeyArrowLeft)
         {
            LOGGER_INFO("LEFT");
            m_leftDown = isKeyDown;
         }
         else if(event.message().keyCode == CEvent::KeyArrowRight)
         {
            LOGGER_INFO("RIGHT");
            m_rightDown = isKeyDown;
         }
         else if(event.message().keyCode == CEvent::KeyArrowUp)
         {
            LOGGER_INFO("UP");
            m_upDown = isKeyDown;
         }
         else if(event.message().keyCode == CEvent::KeyArrowDown)
         {
            LOGGER_INFO("DOWN");
            m_downDown = isKeyDown;
         }
      }
      
      return false;
   }
};

int main(int argc, char *argv[])
{
   IEngineDevice *engineDevice = CEngine2d::createDevice(IVideoDevice::DeviceTypeSdl,
                                                         CSizeI(1920, 1080));

   if(!engineDevice)
   {
      LOGGER_ERROR("Unable to create the engine device!");
      return false;
   }
   
   IVideoDevice *videoDevice = engineDevice->getVideoDevice();
   if(!videoDevice)
   {
      LOGGER_ERROR("No video device available.");
      return false;
   }
   
   // Register event receiver
   CEventManager *eventManager = engineDevice->getEventManager();
   CTestEventListener *eventListener = new CTestEventListener();
   eventManager->registerListener(eventListener);
   
   CPixmap ball("ball.bmp", "bmp");
   if(ball.isNull())
   {
      LOGGER_ERROR("Unable to load ball.bmp");
      return 1;
   }
   
   int speed = 4;
   while(engineDevice->run() && !l_endProgram)
   {
      videoDevice->start(CColour(0,0,100,255));      
      
      CPaintTool *painter = videoDevice->getScreenPaintTool();
      painter->drawRect(CRectI(ballx+200, bally, 50, 50));
      painter->drawPixmap(ball, CPointI(ballx, bally));
      
      double ticks = ((double)engineDevice->getTicks()/40);
      if(m_leftDown)
      {
         ballx -= ceil(ticks * speed);
      }
      if(m_rightDown)
      {
         ballx += ceil(ticks * speed);
      }
      if(m_upDown)
      {
         bally -= ceil(ticks * speed);
      }
      if(m_downDown)
      {
         bally += ceil(ticks * speed);
      }
      
      engineDevice->drawFps();
      
      videoDevice->end();
   }
   
   LOGGER_INFO("Exiting the main game loop");

   eventManager->unregisterListener(eventListener);
   engineDevice->exit();
   
   return 0;
}
