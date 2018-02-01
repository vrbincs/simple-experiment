/** 
 * \file cengine2d.cpp
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
 * SEEngine2d is a small library that enapsulates a simple 2D gaming 
 * engine.
 *
 */

#include <cstddef>

#include "logging.h"
LOGGING_INIT("CEngine2D")


#include "cengine2d.h"

CEngine2d::~CEngine2d()
{
}

IEngineDevice *CEngine2d::createDevice(IVideoDevice::DeviceType renderType,
                                       const CSizeI &resolution)
{
   IEngineDevice *pEngineDevice = IEngineDevice::instance();
   if(pEngineDevice)
   {
      if(!pEngineDevice->init(renderType, resolution))
      {
         LOGGER_WARN("The render type=" << renderType << " not supported on your device.");
         pEngineDevice->exit();
         return NULL;
      }
   }
   else
   {
      LOGGER_WARN("Engine device is not available.");
   }
   
   return pEngineDevice;
}

IEngineDevice *CEngine2d::instance()
{
   return IEngineDevice::instance();
}

CEngine2d::CEngine2d()
{
}
