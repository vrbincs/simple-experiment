#include <cstring>
#include <fstream>

#include "logging.h"
LOGGING_INIT("CEngine2D")

#include "cpixmap.h"
#include "ccolour.h"

#include "cxbmloader.h"

CXBMLoader::CXBMLoader(const CColour &colour)
   : m_colour(colour)
{
}

CPixmap *CXBMLoader::loadXBM(const std::string &file)
{
   LOGGER_ERROR("CXBMLoader::loadXBM() not implemented.");
   return NULL;
}

CPixmap *CXBMLoader::loadFromBuffer(void *buffer, int32_t width, int32_t height)
{
   const uint32_t image_dimension = (width * height);
   const uint32_t size = (image_dimension * 3);
   uint8_t *pixels = new uint8_t[size];
   memset(pixels, 0, size);
   
   uint8_t *pixelTmp = pixels;
   uint8_t *pixelVal = ((uint8_t *) buffer);
   
   const uint32_t image_dimension_bits = (image_dimension / 8);
   for(uint32_t i=0; i<image_dimension_bits; i++)
   {
      for(int j=0; j<8; j++)
      {
         if(((*pixelVal >> j) & 0x1) == 0)
         {
            *(pixelTmp++) = (m_colour.getRed());
            *(pixelTmp++) = (m_colour.getGreen());
            *(pixelTmp++) = (m_colour.getBlue());
         }
         else
         {
            pixelTmp += 3;
         }
      }
      pixelVal++;
   }
   
   CPixmap *pixmap = new CPixmap(pixels, width, height, 24);

   return pixmap;
}

CPixmap *CXBMLoader::loadRawImageFromFile(const std::string &file,
                                          int32_t width,
                                          int32_t height,
                                          int32_t depth)
{
   std::ifstream fileStream(file, std::ios_base::in);
   
   if(fileStream.is_open())
   {
      fileStream.seekg(0, std::ios_base::end);
      int fileSize = fileStream.tellg();
      fileStream.seekg(0, std::ios_base::beg);
      
      if(fileSize == (width * height * (depth/8)))
      {
         uint8_t *buffer = new uint8_t[fileSize];
         
         if(fileStream.read((char *)buffer, fileSize))
         {
            return new CPixmap(buffer, width, height, depth);
         }
         else
         {
            LOGGER_ERROR("Error while reading the file.");
         }
      }
      else
      {
         LOGGER_ERROR("The file size is incosistent with the expected image size.");
      }
   }
   else
   {
      LOGGER_WARN("Unable to open the file=" << file);
   }
   
   return NULL;
}
