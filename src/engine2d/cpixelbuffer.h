#ifndef CPIXELBUFFER_H
   #define CPIXELBUFFER_H

#include <cstdint>
#include <cstddef>

class CPixelBuffer
{
public:
   CPixelBuffer(uint8_t *ptr = NULL);
   virtual ~CPixelBuffer();
   
   virtual void *getBuffer();
   virtual void *release();
   
   virtual void lock();
   virtual void unlock();
private:
   uint8_t *m_pixBuffer;
};

#endif // CPIXELBUFFER_H
