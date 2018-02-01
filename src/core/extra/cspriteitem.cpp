#include <logging.h>
LOGGING_INIT("CEngine2D")

#include "cspritequeue.h"
#include "cspriteitem.h"

CSpriteItem::CSpriteItem(CSpriteQueue *spriteQueue)
   : m_spriteQueue(spriteQueue)
{
}

CSpriteItem::~CSpriteItem()
{
}

bool CSpriteItem::changeSprite(int index)
{
   return m_spriteQueue->changeSprite(index);
}

CRectF CSpriteItem::itemRegion() const
{
   return CRectF(getPosition(), m_spriteQueue->getSize().toFloat());
}

void CSpriteItem::repaint(CPaintTool *paintTool,
                          const CRectF &updateRegion)
{
   CPixmap *sprite = NULL;
   CRectF rect;
   m_spriteQueue->getSprite(&sprite, rect);
   
   if(sprite)
   {
      paintTool->save();
      
      paintTool->drawPixmap(*sprite, getPosition(), &rect);
      paintTool->restore();
   }
   else
   {
      LOGGER_WARN("Sprite is NULL");
   }
}
