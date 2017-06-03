#include <cengine2d.h>
#include <logging.h>

int main(int argc, char *argv[])
{
   IEngineDevice *device = CEngine2d::createDevice(IVideoDevice::DeviceTypeSdl,
                                                   CSizeI(1920, 1280));

   if(!device)
   {
      LOGGER_ERROR("Unable to create the device!");
   }

   return 0;
}
