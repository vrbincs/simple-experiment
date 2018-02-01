/** 
 * \file ienginedevice.h
 * \author  Sasho Vrbinc <righteous11@gmail.com>
 * \version 1.0
 * 
 * \section LICENSE
 * 
 * Copyright (C) 2017 Sasho Vrbinc
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or any
 * later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 
 * 02110-1301 USA.
 * 
 * \section DESCRIPTION
 * 
 * IEngineDevice declares an iterface for platform specific resources.
 * Like, renderer backend, file system operations, events, ...
 * 
 * There can only be one engine device, so it implements the singleton
 * pattern.
 */

#ifndef IENGINEDEVICE_H
   #define IENGINEDEVICE_H

#include <list>
#include <csize.h>
#include <ivideodevice.h>

class IVideoDevice;
class IEventFactory;
class IGameDelegate;

class IEngineDevice
{
public:
   /**
    * \brief virtual destructor
    */
   virtual ~IEngineDevice(){}
   
   /**
    * \brief select the rendering backend. This function is used by the
    * CEngine2d object.
    * 
    * \param[in] renderType - the type of the rendering back-end
    * \param[in] resolution - selected resolution
    * 
    * \return returns true if the selected renderer has been
    * successfully initialzed; false otherwise.
    */
   virtual bool init(IVideoDevice::DeviceType renderType,
                     const CSizeI &resolution) = 0;
   
   /**
    * \brief the purpose of this function is to maintain a steady frame
    * rate. A call to this function should be made in every iteration of
    * the main game loop.
    * 
    * \return returns false when the program should terminate; true
    * otherwise.
    */
   virtual void run() = 0;
   
   virtual void registerGameDelegate(IGameDelegate *gameDelegate) = 0;
   
   /**
    * \brief Call to this function will exit the engine and free-up all
    * allocated resources.
    */
   virtual void exit() = 0;
   
   /**
    * \brief get number of miliseconds from the last cycle.
    * \return returns number of miliseconds from the last cycle.
    */
   virtual uint64_t getDeltaTicks() const = 0;
   
   virtual uint64_t getTimestamp() const = 0;
   
   /**
    * \brief returns a pointer to the video device.
    * \return returns a pointer to the video device. NULL if no video
    * device is available.
    */
   virtual IVideoDevice *getVideoDevice() = 0;
   
   /**
    * \brief show/hide FPS counter on the top-left corner
    * \param[in] show: show/hide FPS counter
    */
   virtual void showFps(bool show = true) = 0;
   
   /**
    * \brief return an instance of the IEngineDevice. This class is 
    * singleton, so this function should always return the same instance
    * of the object
    * 
    * \return returns a pointer of IEngineDevice
    */
   static IEngineDevice *instance();

   virtual IEventFactory *getKeyEventFactory() = 0;
protected:
   friend class IKeyListener;
   friend class CEngine2d;
   
};

#endif // IENGINEDEVICE_H
