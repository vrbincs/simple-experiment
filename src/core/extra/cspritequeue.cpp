#include <cpixmap.h>

#include "cspritequeue.h"

CSpriteQueue::CSpriteQueue(CPixmap *pixmap,
                           uint32_t spriteWidth,
                           uint32_t spriteHeight)
   : m_pixmap(pixmap),
     m_index(0),
     m_indexMax(0),
     m_spriteWidth(spriteWidth),
     m_spriteHeight(spriteHeight)
{
   m_indexMax = (pixmap->getWidth() / m_spriteWidth);
   m_rect = CRectF(0,0,spriteWidth,spriteHeight);
}

CSpriteQueue::~CSpriteQueue()
{
}

bool CSpriteQueue::isValid() const
{
   return (m_pixmap != NULL);
}

bool CSpriteQueue::changeSprite(uint16_t index)
{
   if(isValid())
   {
      if(index < m_indexMax)
      {
         m_index = index; 
         m_rect.setPosition((m_index * m_spriteWidth), 0);
                 
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
   if(isValid())
   {
      *pixmap = m_pixmap;
      rect = m_rect;
      return true;
   }
   else
   {
      return false;
   }
}
