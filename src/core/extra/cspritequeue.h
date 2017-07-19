#ifndef CSPRITEQUEUE_H
   #define CSPRITEQUEUE_H

#include <csceneitem.h>
#include <cpixmap.h>
#include <cpainttool.h>
#include <csize.h>

class CSpriteQueue
{
public:
   CSpriteQueue(const CPixmap *pixmap);
   virtual ~CSpriteQueue();
   
   bool isValid() const;
   
   bool changeSprite(uint16_t index);
   uint16_t spriteIndex() const;
   
   CSizeI getSize() const;
   
   void repaint(CPaintTool &paintTool, const CRectI &area);
private:
   const CPixmap *m_pixmap;
   uint16_t m_index;
   uint16_t m_indexMax;
   uint32_t m_width;
   uint32_t m_height;
};

#endif // CSPRITEQUEUE_H
