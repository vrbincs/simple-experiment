#include <memory>

#include <cengine2d.h>
#include <cmath>
#include <logging.h>

#include <input/ckeylistener.h>

static bool l_endProgram = false;   
static double ballx = 0;
static double bally = 0;

static bool m_leftDown  = false;
static bool m_rightDown = false;
static bool m_upDown    = false;
static bool m_downDown  = false;
#include <unistd.h>

class CTestEventListener : public CKeyListener
{
public:
   CTestEventListener()
   {
      connect();
   }
   
   bool keyDown(const CEvent *event)
   {
      if(event->message().keyCode == CEvent::Key_Escape)
      {
         LOGGER_INFO(event->message().keyCode);
         l_endProgram = true;
      }
      else if(event->message().keyCode == CEvent::Key_ArrowLeft)
      {
         m_leftDown = true;
      }
      else if(event->message().keyCode == CEvent::Key_ArrowRight)
      {
         m_rightDown = true;
      }
      else if(event->message().keyCode == CEvent::Key_ArrowUp)
      {
         m_upDown = true;
      }
      else if(event->message().keyCode == CEvent::Key_ArrowDown)
      {
         m_downDown = true;
      }
      else
      {
         return false;
      }
      
      return true;
   }
   
   bool keyUp(const CEvent *event)
   {
      if(event->message().keyCode == CEvent::Key_Escape)
      {
         LOGGER_INFO(event->message().keyCode);
         l_endProgram = false;
      }
      else if(event->message().keyCode == CEvent::Key_ArrowLeft)
      {
         m_leftDown = false;
      }
      else if(event->message().keyCode == CEvent::Key_ArrowRight)
      {
         m_rightDown = false;
      }
      else if(event->message().keyCode == CEvent::Key_ArrowUp)
      {
         m_upDown = false;
      }
      else if(event->message().keyCode == CEvent::Key_ArrowDown)
      {
         m_downDown = false;
      }
      else
      {
         return false;
      }
      
      return true;
   }
};

int main(int argc, char *argv[])
{
   IEngineDevice *engineDevice = CEngine2d::createDevice(IVideoDevice::DeviceTypeSdl);

   if(!engineDevice)
   {
      LOGGER_ERROR("Unable to create the engine device!");
      return 1;
   }
   
   IVideoDevice *videoDevice = engineDevice->getVideoDevice();
   if(!videoDevice)
   {
      LOGGER_ERROR("No video device available.");
      return 1;
   }
   
   CTestEventListener keyEventListener;
   
   engineDevice->showFps();
   
   CPixmap ball("ball.bmp", "bmp");
   if(ball.isNull())
   {
      LOGGER_ERROR("Unable to load ball.bmp");
      return 1;
   }
   
   double speed = 0.00050;
   
   while(engineDevice->run() && !l_endProgram)
   {
      CPaintTool *painter = videoDevice->getScreenPaintTool();
      
      double ticks = ((double)engineDevice->getDeltaTicks());
      if(m_leftDown)
      {
         ballx -= (ticks * speed);
      }
      if(m_rightDown)
      {
         ballx += (ticks * speed);
      }
      if(m_upDown)
      {
         bally -= (ticks * speed);
      }
      if(m_downDown)
      {
         bally += (ticks * speed);
      }
      
      painter->drawRect(CRectF(ballx+200, bally, 50, 50));
      painter->drawPixmap(ball, CPointF(ballx, bally));
   }
   
   LOGGER_INFO("Exiting the main game loop");
   engineDevice->exit();
   
   return 0;
}
