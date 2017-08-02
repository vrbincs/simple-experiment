/** 
 * \file ipaintsurface.h
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
 * IPaintSurface is an abstraction of the pixel buffer that represents
 * an image. An size of the buffer is defined by the image size and its
 * color depth.
 */

#ifndef IPAINTSURFACE_H
   #define IPAINTSURFACE_H

#include <string>
#include <crect.h>
#include <ccolour.h>

class CPixmap;
class IVideoDevice;

class IPaintSurface
{
public:
   /**
    * \brief virtual destructor
    */
   virtual ~IPaintSurface() {}
   
   /**
    * \brief get the color depth of the pixel buffer
    * \return returns the color depth of the pixel buffer
    */
   virtual uint8_t getBitsPerPixels() const = 0;
   
   /**
    * \brief get height of the image
    * \return returns height of the image
    */
   virtual uint32_t getHeight() const = 0;
   
   /**
    * \brief get width of the image
    * \return returns width of the image
    */
   virtual uint32_t getWidth() const = 0;
   
   /**
    * \brief every read/write to the pixel buffer must be protected.
    */
   virtual void lock() = 0;
   
   /**
    * \brief every call to lock() must have corresponding call to 
    * unlock after the access to pixel buffer is no longer needed.
    */
   virtual void unlock() = 0;
   
   virtual bool isNull() const = 0;
   
   virtual CColour getPixelAt(const CPointI &pos) const = 0;
private:
   /**
    * \brief pointer to the video device that has created the surface.
    * This is ultimately used by CPaintTool in order to create
    * coresponding paint device.
    * 
    * \return return the pointer to the video device associated with the
    * surface.
    */
   virtual IVideoDevice *getVideoDevice() const = 0;

   /**
    * \brief this function transforms pixelBuffer into the buffer
    * compatible by the renderer. The object takes the ownership of
    * the input buffer and destroys it when surface is destroyed.
    * 
    * The size of the buffer must match the parameters (width, height 
    * and depth)
    * 
    * \param[in] pixelBuffer - a pointer to the source of pixel buffer 
    * from which a new surface is allocated.
    * \param[in] width - width of the image
    * \param[in] height - height of the image
    * \param[in] depth - color depth of the image.
    * 
    * \return returns true if the buffer has been successfully 
    * allocated; false if an error occured.
    */
   virtual bool allocateFromBuffer(uint8_t *pixelBuffer,
                                   uint32_t width,
                                   uint32_t height,
                                   uint8_t depth) = 0;

   /**
    * \brief set pixel buffer from a file.
    * \param[in] fileName - file name of the image.
    * \param[in] type - the type of the image. The set supported types
    * depends on the renderer backend.
    * 
    * \return returns true if surface has been successfully created from
    * the file; false otherwise.
    */
   virtual bool allocateFromFile(const std::string &fileName,
                                 const std::string &type) = 0;
   
   friend class CPixmap;
   friend class CPaintTool;
};

#endif // IPAINTSURFACE_H
