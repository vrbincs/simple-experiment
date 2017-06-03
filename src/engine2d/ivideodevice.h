#ifndef IVIDEODEVICE_H
   #define IVIDEODEVICE_H

class IVideoDevice
{
public:
   enum DeviceType
   {
      DeviceTypeSdl
   };
   
   virtual ~IVideoDevice(){}
   
   virtual DeviceType type() const = 0;
   
   /**
    * \brief Draw image on the device
    */
   //virtual void drawImage() = 0;
};

#endif // IVIDEODEVICE_H
