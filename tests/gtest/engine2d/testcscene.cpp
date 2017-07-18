#include <string>
#include <deque>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <logging.h>
#include <cscene.h>
#include <csceneitem.h>

#include "gmockcsceneitem.h"
#include "testcsceneitemfactory.h"

using ::testing::AtLeast;
using ::testing::NiceMock;

class TestCScene : public CScene, public ::testing::Test
{
public:
   TestCScene(const CRectF &sceneRect = CRectF(0,0,800,600))
      : CScene(sceneRect)
   {
   }
   
   ~TestCScene()
   {
      for(auto it0=m_rootItems.begin(); it0!=m_rootItems.end(); it0++)
      {
         delete *it0;
      }
   }
   
   NiceMock<GMockCSceneItem> *createCSceneItem(CSceneItem *parent = NULL, const CRectF & rect = CRectF(0,0,0,0))
   {
      auto ret = new NiceMock<GMockCSceneItem>(rect, parent);
      ret->DelegateToFake();
      
      if(parent == NULL)
      {
         m_rootItems.push_back(ret);
      }
      
      return ret;
   }
   
   TestCSceneItemFactory m_itemFactory;
   std::deque<NiceMock<GMockCSceneItem> *> m_rootItems;
};

TEST_F(TestCScene, TestAddItem)
{
   auto sceneItem0      = createCSceneItem();
   auto sceneChildItem1 = createCSceneItem(sceneItem0);
   auto sceneChildItem2 = createCSceneItem(sceneItem0);
   
   EXPECT_CALL(*sceneItem0, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneChildItem1, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneChildItem2, itemRegion()).Times(AtLeast(1));
   
   addItem(sceneItem0);
   
   EXPECT_EQ(getItems().size(), 1);
}

TEST_F(TestCScene, TestViewableItems)
{
   auto sceneItem0      = createCSceneItem();
   auto sceneChildItem1 = createCSceneItem(sceneItem0);
   auto sceneChildItem2 = createCSceneItem(sceneItem0);
   
   auto sceneItem1      = createCSceneItem();;
   auto sceneChildItem3 = createCSceneItem(sceneItem1);
   auto sceneChildItem4 = createCSceneItem(sceneItem1);

   sceneItem0->setRect(100, 100, 100, 100);
   sceneChildItem1->setRect(-200, -200, 100, 100);
   sceneChildItem2->setRect(100, 100, 100, 100);
   
   sceneItem1->setRect(-100, -100, 100, 100);
   sceneChildItem1->setRect(0, 0, 10, 10);
   sceneChildItem2->setRect(0, 0, 100, 100);
   
   EXPECT_CALL(*sceneItem0, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneItem1, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneChildItem3, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneChildItem4, itemRegion()).Times(AtLeast(1));
   
   addItem(sceneItem0);
   addItem(sceneItem1);
   
   EXPECT_EQ(getViewableItems().size(), 1);
}

TEST_F(TestCScene, TestViewableItemsWithSceneOffset)
{
}

TEST_F(TestCScene, TestZIndex)
{
   auto sceneItem0 = createCSceneItem();
   auto sceneItem1 = createCSceneItem();
   auto sceneItem2 = createCSceneItem();
   
   EXPECT_CALL(*sceneItem0, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneItem1, itemRegion()).Times(AtLeast(2));
   EXPECT_CALL(*sceneItem2, itemRegion()).Times(AtLeast(1));
   
   sceneItem0->setRect(0, 0, 10, 10);
   sceneItem1->setRect(0, 0, 10, 10);
   sceneItem2->setRect(0, 0, 10, 10);
   
   addItem(sceneItem0);
   addItem(sceneItem1);
   addItem(sceneItem2);
   
   sceneItem1->setZIndex(10);
   
   ASSERT_EQ(getViewableItems().size(), 2);
   
   auto itemLayer10 = getViewableItems().find(10);
   ASSERT_TRUE((itemLayer10 != getViewableItems().end()));
   EXPECT_TRUE((itemLayer10->second.find(sceneItem1) != itemLayer10->second.end()));
   
   auto itemLayer0 = getViewableItems().find(0);
   ASSERT_TRUE((itemLayer0 != getViewableItems().end()));
   EXPECT_TRUE((itemLayer0->second.find(sceneItem0) != itemLayer0->second.end()));
   EXPECT_TRUE((itemLayer0->second.find(sceneItem2) != itemLayer0->second.end()));
}

TEST_F(TestCScene, TestGetCollisionItems)
{
   auto sceneItem0 = createCSceneItem(NULL, CRectF(0,0,100,100));
   auto sceneItem1 = createCSceneItem(NULL, CRectF(50,50,100,100));
   auto sceneItem2 = createCSceneItem(NULL, CRectF(-50,-50,100,100));
   auto sceneItem3 = createCSceneItem(NULL, CRectF(100,100,100,100));
   auto sceneItem4 = createCSceneItem(NULL, CRectF(100,100,100,100));
   auto sceneItem5 = createCSceneItem(NULL, CRectF(50,50,100,100));
   
   EXPECT_CALL(*sceneItem0, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneItem1, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneItem2, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneItem3, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneItem4, itemRegion()).Times(AtLeast(1));
   EXPECT_CALL(*sceneItem5, itemRegion()).Times(AtLeast(1));
   
   sceneItem5->setZIndex(5);
   
   addItem(sceneItem0);
   addItem(sceneItem1);
   addItem(sceneItem2);
   addItem(sceneItem3);
   addItem(sceneItem4);
   addItem(sceneItem5);
   
   std::deque<CSceneItem *> collisionList0 = getCollisionItems(sceneItem0);
   std::deque<CSceneItem *> collisionList1 = getCollisionItems(sceneItem1);
   std::deque<CSceneItem *> collisionList2 = getCollisionItems(sceneItem2);
   
   ASSERT_EQ(collisionList0.size(), 2);
   ASSERT_EQ(collisionList1.size(), 3);
   ASSERT_EQ(collisionList2.size(), 1);
   
   for(auto it0=collisionList0.begin(); it0 != collisionList0.end(); it0++)
   {
      EXPECT_TRUE((*it0 = sceneItem1) || (*it0 = sceneItem2));
   }
   
   for(auto it0=collisionList1.begin(); it0 != collisionList1.end(); it0++)
   {
      EXPECT_TRUE((*it0 = sceneItem0) || (*it0 = sceneItem3) || (*it0 = sceneItem4));
   }
   
   for(auto it0=collisionList2.begin(); it0 != collisionList2.end(); it0++)
   {
      EXPECT_TRUE((*it0 = sceneItem0));
   }
}

TEST_F(TestCScene, TestSetScenePosition)
{
   auto sceneItem0 = createCSceneItem(NULL, CRectF(0,0,100,100));
   auto sceneItem1 = createCSceneItem(NULL, CRectF(100,100,100,100));
   auto sceneItem2 = createCSceneItem(NULL, CRectF(200,200,100,100));
   auto sceneItem3 = createCSceneItem(NULL, CRectF(800,600,100,100));
   
   addItem(sceneItem0);
   addItem(sceneItem1);
   addItem(sceneItem2);
   addItem(sceneItem3);
   
   EXPECT_EQ(getViewableItems(0).size(), 3);
   
   setScenePosition(CPointF(50,50));
   EXPECT_EQ(getViewableItems(0).size(), 4);
   
   setScenePosition(CPointF(100,100));
   EXPECT_EQ(getViewableItems(0).size(), 3);
   
   setScenePosition(CPointF(300,300));
   EXPECT_EQ(getViewableItems(0).size(), 1);
}
