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
   
   sceneItem0.DelegateToFake();
   sceneChildItem1.DelegateToFake();
   sceneChildItem2.DelegateToFake();
   
   sceneItem0.setRect(100, 100, 100, 100);
   sceneChildItem1.setRect(-200, -200, 100, 100);
   sceneChildItem2.setRect(100, 100, 100, 100);
   
   
   
   EXPECT_CALL(sceneItem0, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneChildItem1, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(sceneChildItem2, itemRegion()).Times(AtLeast(1));
   
   addItem(&sceneItem0);
   
   EXPECT_EQ(getViewableItems().size(), 2);
}
