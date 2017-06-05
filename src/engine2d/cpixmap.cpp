#include "cpixmap.h"

CPixmap::CPixmap(int width, int height, int bpp)
   : m_size(width, height),
     m_bpp(bpp)
{
   allocateBuffer();
}

CPixmap::CPixmap(const CSizeI &size, int bpp)
   : m_size(size),
     m_bpp(bpp)
{
   allocateBuffer();
}

CPixmap::~CPixmap()
{
   delete [] m_pPixelBuffer;
}

void *CPixmap::getBuffer()
{
   return m_pPixelBuffer;
}
   
CSizeI CPixmap::getSize() const
{
   return m_size;
}

int CPixmap::getWidth() const
{
   return m_size.getWidth();
}

int CPixmap::getHeight() const
{
   return m_size.getHeight();
}

int CPixmap::getBpp() const
{
   return m_bpp;
}

bool CPixmap::allocateBuffer()
{
   unsigned int bufferSize = (getWidth() * getHeight() * getBpp());
   m_pPixelBuffer = new uint8_t[bufferSize];
}

