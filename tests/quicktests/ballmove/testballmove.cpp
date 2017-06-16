#include <cengine2d.h>
#include <logging.h>

int main(int argc, char *argv[])
{
   IEngineDevice *engineDevice = CEngine2d::createDevice(IVideoDevice::DeviceTypeSdl,
                                                         CSizeI(1280, 800));

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
   
   CPixmap ball("ball.bmp", "bmp");
   if(ball.isNull())
   {
      LOGGER_ERROR("Unable to load ball.bmp");
      return 1;
   }
   
   int ballx = 0;
   int bally = 0;
   while(engineDevice->run())
   {
      videoDevice->start(CColour(0,0,100,255));
      
      ballx++;
      bally++;
      
      CPaintTool *painter = videoDevice->getScreenPaintTool();
      painter->drawRect(CRectI(ballx+200, bally, 50, 50));
      painter->drawPixmap(ball, CPointI(ballx, bally));
      
      videoDevice->end();
   }

   return 0;
}
