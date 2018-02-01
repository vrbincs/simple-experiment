/** 
 * \file cengine2d.h
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

#ifndef CENGINE2D_H
   #define CENGINE2D_H

#include <csize.h>
#include <ienginedevice.h>
#include <ivideodevice.h>
#include <cevent.h>
#include <ieventlistener.h>
#include <ieventfactory.h>
#include <igamedelegate.h>
#include <cpainttool.h>
#include <cpixmap.h>
#include <celement.h>
#include <input/ckeylistener.h>

#include <csceneitem.h>
#include <cscene.h>
#include <csceneview.h>

/**
 * \class The main class of the engine. It provides the API to 
 * instatiate the engine and initializes all necessary to prepare a
 * functional engine.
 */
class CEngine2d
{
public:
   /**
    * \brief virtual destructor.
    */
   virtual ~CEngine2d();
   
   /**
    * \brief create an engine for the given platform.
    * \param[in] renderType - selects the rendering backend.
    * \param[in] resolution - resolution of the video output.
    * 
    * \return returns a pointer to the engine; false if the device 
    * cannot be created.
    */
   static IEngineDevice *createDevice(IVideoDevice::DeviceType renderType,
                                      const CSizeI &resolution = CSizeI());
   /**
    * \brief return the instance ot the engine.
    * \return return the instance ot the engine.
    */
   static IEngineDevice *instance();
private:
   /**
    * \brief default constructor is private as we do not want to allow
    * to create multiple instances of the engine.
    */
   CEngine2d();
};

#endif // CENGINE2D_H
