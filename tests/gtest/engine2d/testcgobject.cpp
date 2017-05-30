#include <gtest/gtest.h>

#include <crect.h>
#include <cgobject.h>


class TestCGObject : public CGObject
{
public:
   TestCGObject(TestCGObject *testcgobject = NULL) : CGObject(testcgobject){}
   ~TestCGObject(){}
   
   CRectI objectRegion() const
   {
      return CRectI();
   }
protected:
   void repaint(CDrawingTool *)
   {
      
   }
};


TEST(TestCGObject, TestParentIsSet)
{
   TestCGObject parent;
   TestCGObject child1(&parent);
   TestCGObject child2;
   
   EXPECT_TRUE(child2.setParent(&child1));
   EXPECT_TRUE((child2.getParent() == &child1));
   EXPECT_TRUE((child1.getParent() == &parent));
   EXPECT_TRUE((parent.getParent() == NULL));
}
