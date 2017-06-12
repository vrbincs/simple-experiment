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
   
   int ballx = 0;
   int bally = 0;
   while(engineDevice->run())
   {
      videoDevice->start();
      
      IPaintDevice *paintDevice = videoDevice->getScreenPaintDevice();
      if(paintDevice)
      {
         paintDevice->drawRect(CRectI(ballx,bally,100,100));
      }
      else
      {
         LOGGER_WARN("Paint device associated with the screed not available.");
      }
      
      ballx++;
      bally++;
      
      LOGGER_INFO("Runnig at FPS =");
      videoDevice->end();
   }

   return 0;
}
