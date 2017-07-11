#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Invoke;

#include <crect.h>
#include <csceneitem.h>

class GMockCSceneItem : public CSceneItem
{
public:
   GMockCSceneItem(CSceneItem *parent = NULL) : CSceneItem(parent){}
   MOCK_CONST_METHOD0(itemRegion, CRectF());
   
   inline void setRect(uint32_t posx,
                       uint32_t posy,
                       uint32_t width,
                       uint32_t height)
   {
      m_rect = CRectF(posx, posy, width, height);
   }
   
   void DelegateToFake()
   {
      ON_CALL(*this, itemRegion()).WillByDefault(Invoke(this, &GMockCSceneItem::getItemRegion));
   }
protected:
   MOCK_METHOD2(repaint, void(CPaintTool *paintTool, const CRectF &updateRegion));
   
   CRectF getItemRegion() const
   {
      return m_rect;
   }
   
   CRectF m_rect;
};
