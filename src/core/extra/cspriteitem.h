#ifndef CSPRITEITEM_H
   #define CSPRITEITEM_H

#include <csceneitem.h>

class CSpriteQueue;

class CSpriteItem : public CSceneItem
{
public:
   CSpriteItem(CSpriteQueue *spriteQueue);
   virtual ~CSpriteItem();
   
   bool changeSprite(int index);
   
   CRectF itemRegion() const override;
protected:
   void repaint(CPaintTool *paintTool, const CRectF &updateRegion) override;
private:
   CSpriteQueue *m_spriteQueue;
};

#endif
