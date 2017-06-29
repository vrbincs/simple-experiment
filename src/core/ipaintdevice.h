/** 
 * \file ipaintdevice.h
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
 * IPaintDevice provides an iterface for painting features, like 
 * drawing primitives (rectangles, circles, polygons, ...) and bliting
 * pixmaps.
 */

#ifndef IPAINTDEVICE_H
   #define IPAINTDEVICE_H

#include <string>

#include <crect.h>
#include <cpixmap.h>


class IVideoDevice;
class CColour;

class IPaintDevice
{
public:
   /**
    * \brief virtual destructor
    */
   virtual ~IPaintDevice() {}
   
   /**
    * \brief prepares everything for painting.
    * \param[in] destSurface - the surface on which all painting
    * operations will be carried out.
    * \return returns true if no errors; false otherwise.
    */
   virtual bool start(IPaintSurface *destSurface) = 0;
   
   /**
    * \brief draws rectangle at specifed position and size.
    * \param[in] rect - the position and size of the rectangle
    */
   virtual void drawRect(const CRectF &rect,
                         const CColour &colour) = 0;
   
   /**
    * \brief draw a surface. This function copies the source surface to
    * the destination surface.
    * \param[in] paintSurface - source surface
    */
   virtual void drawSurface(const IPaintSurface &paintSurface,
                            const CPointF &pos,
                            const CRectF *srcRect) = 0;

   virtual void drawText(const std::string &text,
                         const CRectF &rect,
                         const CColour &colour) = 0;
   /**
    * \brief finalizies the drawing.
    * \return returns true if no errors; false otherwise.
    */
   virtual bool end() = 0;
};

#endif // IPAINTDEVICE_H
