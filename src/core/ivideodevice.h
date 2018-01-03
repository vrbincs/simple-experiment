/** 
 * \file ivideodevice.h
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
 * IVideoDevice is an abstraction of the video routines for the given
 * renderer.
 * 
 * This class should serve as a factory that creates IPaintSurface
 * and IPainDevice objects. 
 */

#ifndef IVIDEODEVICE_H
   #define IVIDEODEVICE_H

#include <ccolour.h>

class IPaintSurface;
class IPaintDevice;
class CPaintTool;

class IVideoDevice
{
public:
   enum DeviceType
   {
      DeviceTypePseudo,
      DeviceTypeSdl,
      DeviceTypeSoftware
   };
   
   virtual ~IVideoDevice(){}
   
   /**
    * \brief returns the type of the device.
    * \return returns the type of the device.
    */
   virtual DeviceType type() const = 0;
   
   /**
    * \brief returns an instance of IPaintSurface.
    * \return returns an instance of IPaintSurface.
    */
   virtual IPaintSurface *createPaintSurface() = 0;
   
   /**
    * \brief creates a paint device that can be used for performing
    * drawing routines on the paintSurface
    * 
    * \param[in] paintSurface - Pointer to the surface on which paiting
    * operations will be performed.
    * 
    * \return returns a poitner of IPaintDevice. Returns NULL if a device
    * cannot be constructed.
    */
   virtual IPaintDevice *createPaintDevice(IPaintSurface *paintSurface) const = 0;
   
   /**
    * \brief this function provides access to the screen renderer created
    * on the initialization of the IVideoDevice. It allows drawing 
    * directly to the framebuffer.
    * 
    * \return returns pointer of type IPaintSurface that warps the 
    * screen surface. Returns NULL if the screen has not been 
    * initialized.
    */
   virtual CPaintTool *getScreenPaintTool() const = 0;

   /**
    * \brief before you want to refresh the content on the screen, you
    * have to call this function. It will clear-up the framebuffer with
    * the color of your choice.
    * 
    * \param[in] colour - The colour used for clearing the framebuffer.
    * If the pointer is NULL, the framebuffer will no be cleared.
    * 
    * \return returns true if the wipe of the screen was successfull;
    * false otherwise.
    */
   virtual bool start(const CColour *colour = NULL) = 0;
   
   /**
    * \brief Once all the painting has been finished, we want the
    * framebuffer to display on the screen. This call does exactly that.
    * 
    * \return returns true if framebuffer has successfully been rendered
    * on the screen; false otherwise.
    */
   virtual bool end() = 0;
};

#endif // IVIDEODEVICE_H
