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
 * IPaintDevice is meant to provide an abstraction of the renderer
 * dependent drawing operations, such as draw pixmap, draw rectangle,
 * draw circle, ...
 */

#ifndef IPAINTDEVICE_H
   #define IPAINTDEVICE_H

#include <crect.h>
#include <cpixmap.h>

class IVideoDevice;

class IPaintDevice
{
public:
   virtual ~IPaintDevice() {}
   
   virtual bool start(IPaintSurface *destSurface) = 0;
   virtual void drawRect(const CRectI &rect) = 0;
   virtual void drawSurface(const IPaintSurface &paintSurface,
                            const CPointI &pos) = 0;
   virtual bool end() = 0;
};

#endif // IPAINTDEVICE_H
