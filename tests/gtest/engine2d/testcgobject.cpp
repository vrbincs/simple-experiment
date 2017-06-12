#include <gtest/gtest.h>

#include <crect.h>
#include <cscene.h>
#include <csceneitem.h>


class TestCSceneItem : public CSceneItem
{
public:
   TestCSceneItem(TestCSceneItem *testcgobject = NULL) : CSceneItem(testcgobject){}
   ~TestCSceneItem(){}
   
   CRectI itemRegion() const
   {
      return CRectI();
   }
protected:
   void repaint(CPaintTool *)
   {
      
   }
};


TEST(TestCSceneItem, TestParentIsSet)
{
   TestCSceneItem parent;
   TestCSceneItem child1(&parent);
   TestCSceneItem child2;
   
   EXPECT_TRUE(child2.setParent(&child1));
   EXPECT_TRUE((child2.getParent() == &child1));
   EXPECT_TRUE((child1.getParent() == &parent));
   EXPECT_TRUE((parent.getParent() == NULL));
}
