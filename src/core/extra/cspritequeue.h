#ifndef CSPRITEQUEUE_H
   #define CSPRITEQUEUE_H

#include <csceneitem.h>
#include <cpainttool.h>
#include <csize.h>

class CPixmap;

class CSpriteQueue
{
public:
   CSpriteQueue(CPixmap *pixmap, uint32_t width, uint32_t height);
   virtual ~CSpriteQueue();
   
   bool isValid() const;
   
   bool changeSprite(uint16_t index);
   uint16_t spriteIndex() const;
   uint16_t spriteCount() const;
   
   CSizeI getSize() const;
   bool getSprite(CPixmap **pixmap, CRectF &rect);
private:
   CPixmap *m_pixmap;
   uint16_t m_index;
   uint16_t m_indexMax;
   uint32_t m_width;
   uint32_t m_height;
};

#endif // CSPRITEQUEUE_H
