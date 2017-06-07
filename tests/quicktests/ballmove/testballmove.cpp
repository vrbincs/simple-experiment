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
   
   while(engineDevice->run())
   {
      videoDevice->start();
      LOGGER_INFO("Runnig at FPS =");
      videoDevice->end();
   }

   return 0;
}
