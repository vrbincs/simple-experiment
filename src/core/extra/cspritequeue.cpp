#include <cpixmap.h>

#include "cspritequeue.h"

CSpriteQueue::CSpriteQueue(CPixmap *pixmap,
                           uint32_t width,
                           uint32_t height)
   : m_pixmap(pixmap),
     m_index(0),
     m_indexMax(0),
     m_width(width),
     m_height(height)
{
   if((pixmap->getWidth() % width) == 0 &&
      (pixmap->getHeight() % height) == 0)
   {
      m_indexMax = ((pixmap->getWidth() / width) * 
                    (pixmap->getHeight() / height));
   }
}

CSpriteQueue::~CSpriteQueue()
{
}

bool CSpriteQueue::isValid() const
{
   return (m_indexMax > 0);
}

bool CSpriteQueue::changeSprite(uint16_t index)
{
   if(isValid())
   {
      if(index <= m_indexMax)
      {
         m_index = index;
         return true;
      }
   }
   
   return false;
}

uint16_t CSpriteQueue::spriteIndex() const
{
   return m_index;
}

uint16_t CSpriteQueue::spriteCount() const
{
   return m_indexMax;
}

CSizeI CSpriteQueue::getSize() const
{
   return m_pixmap->getSize();
}
   
bool CSpriteQueue::getSprite(CPixmap **pixmap, CRectF &rect)
{
   return false;
}
