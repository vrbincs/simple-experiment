#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cscene.h>
#include <csceneitem.h>

#include "gmockcsceneitem.h"

using ::testing::AtLeast;


class TestCScene : public CScene, public ::testing::Test
{
public:
   TestCScene(const CRectI &sceneRect = CRectI(0,0,800,600))
      : CScene(sceneRect)
   {
   }
   
};

TEST_F(TestCScene, TestAddItem)
{
   GMockCSceneItem sceneItem0;
   GMockCSceneItem sceneChildItem1(&sceneItem0);
   GMockCSceneItem sceneChildItem2(&sceneItem0);
   
   EXPECT_CALL(sceneItem0, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneChildItem1, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneChildItem2, itemRegion()).Times(AtLeast(1));
   
   addItem(&sceneItem0);
   
   EXPECT_EQ(getItems().size(), 1);
}

TEST_F(TestCScene, TestViewableItems)
{
   GMockCSceneItem sceneItem0;
   GMockCSceneItem sceneChildItem1(&sceneItem0);
   GMockCSceneItem sceneChildItem2(&sceneItem0);
   
   GMockCSceneItem sceneItem1;
   GMockCSceneItem sceneChildItem3(&sceneItem1);
   GMockCSceneItem sceneChildItem4(&sceneItem1);
   
   sceneItem0.DelegateToFake();
   sceneChildItem1.DelegateToFake();
   sceneChildItem2.DelegateToFake();
   
   sceneItem1.DelegateToFake();
   sceneChildItem3.DelegateToFake();
   sceneChildItem4.DelegateToFake();
   
   sceneItem0.setRect(100, 100, 100, 100);
   sceneChildItem1.setRect(-200, -200, 100, 100);
   sceneChildItem2.setRect(100, 100, 100, 100);
   
   sceneItem1.setRect(-100, -100, 100, 100);
   sceneChildItem1.setRect(0, 0, 10, 10);
   sceneChildItem2.setRect(0, 0, 100, 100);
   
   EXPECT_CALL(sceneItem0, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneItem1, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneChildItem3, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneChildItem4, itemRegion()).Times(AtLeast(1));
   
   addItem(&sceneItem0);
   addItem(&sceneItem1);
   
   EXPECT_EQ(getViewableItems().size(), 1);
}

TEST_F(TestCScene, TestZIndex)
{
   GMockCSceneItem sceneItem0;
   GMockCSceneItem sceneItem1;
   GMockCSceneItem sceneItem2;
   
   sceneItem0.DelegateToFake();
   sceneItem1.DelegateToFake();
   sceneItem2.DelegateToFake();
   
   EXPECT_CALL(sceneItem0, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneItem1, itemRegion()).Times(AtLeast(2));
   EXPECT_CALL(sceneItem2, itemRegion()).Times(AtLeast(1));
   
   sceneItem0.setRect(0, 0, 10, 10);
   sceneItem1.setRect(0, 0, 10, 10);
   sceneItem2.setRect(0, 0, 10, 10);
   
   addItem(&sceneItem0);
   addItem(&sceneItem1);
   addItem(&sceneItem2);
   
   sceneItem1.setZIndex(10);
   
   ASSERT_EQ(getViewableItems().size(), 2);
   auto item = getViewableItems().find(10);
   ASSERT_TRUE((item != getViewableItems().end()));
   EXPECT_TRUE((item->second.find(&sceneItem1) != item->second.end()));
}

TEST_F(TestCScene, TestGetCollisionItems)
{
   GMockCSceneItem sceneItem0(CRectF(0,0,100,100));
   GMockCSceneItem sceneItem1(CRectF(50,50,100,100));
   GMockCSceneItem sceneItem2(CRectF(-50,-5,100,100));
   GMockCSceneItem sceneItem3(CRectF(100,100,100,100));
   GMockCSceneItem sceneItem4(CRectF(50,50,100,100));
   
   sceneItem0.DelegateToFake();
   sceneItem1.DelegateToFake();
   sceneItem2.DelegateToFake();
   sceneItem3.DelegateToFake();
   sceneItem4.DelegateToFake();
   
   EXPECT_CALL(sceneItem0, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneItem1, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneItem2, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneItem3, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneItem4, itemRegion()).Times(AtLeast(1));
   
   sceneItem4.setZIndex(5);
   
   addItem(&sceneItem0);
   addItem(&sceneItem1);
   addItem(&sceneItem2);
   addItem(&sceneItem3);
   addItem(&sceneItem4);
   
   std::deque<CSceneItem *> collisionList = getCollisionItems(&sceneItem0);
   ASSERT_EQ(collisionList.size(), 3);
   
   for(auto it0=collisionList.begin(); it0 != collisionList.end(); it0++)
   {
      EXPECT_TRUE((*it0 = &sceneItem1) || (*it0 = &sceneItem2) || (*it0 = &sceneItem3));
   }
}
