#include "cspritequeue.h"


CSpriteQueue::CSpriteQueue(const CPixmap *pixmap)
   : m_pixmap(pixmap),
     m_index(0),
     m_indexMax(0),
     m_width(0),
     m_height(0)
{
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

CSizeI CSpriteQueue::getSize() const
{
   return m_pixmap->getSize();
}
   
void CSpriteQueue::repaint(CPaintTool &paintTool, const CRectI &area)
{
   paintTool.save();
   paintTool.restore();
}
