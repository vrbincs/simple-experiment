#include <cpixelbuffer.h>

CPixelBuffer::CPixelBuffer(uint8_t *ptr)
   : m_pixBuffer(ptr)
{
}

CPixelBuffer::~CPixelBuffer()
{
   delete [] m_pixBuffer;
}

void *CPixelBuffer::getBuffer()
{
   return m_pixBuffer;
}

void *CPixelBuffer::release()
{
   uint8_t *tmpBuffer = m_pixBuffer;
   m_pixBuffer = NULL;
   
   return tmpBuffer;
}

void CPixelBuffer::lock()
{
   // TODO
}

void CPixelBuffer::unlock()
{
   // TODO
}
