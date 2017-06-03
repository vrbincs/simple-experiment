#ifndef IVIDEODEVICE_H
   #define IVIDEODEVICE_H

class IVideoDevice
{
public:
   enum DeviceType
   {
      DeviceTypeSdl
   };
   
   virtual ~IVideoDevice();
};

#endif // IVIDEODEVICE_H
