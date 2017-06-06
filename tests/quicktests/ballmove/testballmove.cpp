#include <cengine2d.h>
#include <logging.h>

int main(int argc, char *argv[])
{
   IEngineDevice *engineDevice = CEngine2d::createDevice(IVideoDevice::DeviceTypeSdl,
                                                         CSizeI(1920, 1280));

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
   
   IPaintDevice *paintDevice = videoDevice->getPaintDevice();
   while(engineDevice->run() && paintDevice)
   {
      LOGGER_INFO("Runnig at FPS =");
   }

   return 0;
}
