#include <memory>

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
#include <unistd.h>
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
            m_leftDown = isKeyDown;
         }
         else if(event.message().keyCode == CEvent::KeyArrowRight)
         {
            m_rightDown = isKeyDown;
         }
         else if(event.message().keyCode == CEvent::KeyArrowUp)
         {
            m_upDown = isKeyDown;
         }
         else if(event.message().keyCode == CEvent::KeyArrowDown)
         {
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
   
   engineDevice->showFps();
   
   // Register event receiver
   CEventManager *eventManager = engineDevice->getEventManager();
   
   std::shared_ptr<CTestEventListener> eventListenerPtr(new CTestEventListener());
   eventManager->registerListener(eventListenerPtr.get());
   
   CPixmap ball("ball.bmp", "bmp");
   if(ball.isNull())
   {
      LOGGER_ERROR("Unable to load ball.bmp");
      return 1;
   }
   
   int speed = 4;
   while(engineDevice->run() && !l_endProgram)
   {      
      CPaintTool *painter = videoDevice->getScreenPaintTool();
      
      double ticks = ((double)engineDevice->getTicks()/25);
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
      
      painter->drawRect(CRectF(ballx+200, bally, 50, 50));
      painter->drawPixmap(ball, CPointF(ballx, bally));
   }
   
   LOGGER_INFO("Exiting the main game loop");

   eventManager->unregisterListener(eventListenerPtr.get());
   engineDevice->exit();
   
   return 0;
}
