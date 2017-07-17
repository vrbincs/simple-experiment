#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Invoke;

#include <crect.h>
#include <csceneitem.h>
#include <cevent.h>

class GMockCSceneItem : public CSceneItem
{
public:
   GMockCSceneItem(CSceneItem *parent = NULL) : CSceneItem(parent){}
   GMockCSceneItem(const CRectF &rect, CSceneItem *parent = NULL) : CSceneItem(parent), m_rect(rect){}
   
   MOCK_CONST_METHOD0(itemRegion, CRectF());
   MOCK_METHOD1(onEvent, bool(const CEvent &));
   
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
      ON_CALL(*this, onEvent(_)).WillByDefault(Invoke(this, &GMockCSceneItem::mockOnEvent));
   }
protected:
   MOCK_METHOD2(repaint, void(CPaintTool *paintTool, const CRectF &updateRegion));
   
   CRectF getItemRegion() const
   {
      return m_rect;
   }
   
   bool mockOnEvent(const CEvent &event)
   {
      return CSceneItem::onEvent(event);
   }
   
   CRectF m_rect;
};
