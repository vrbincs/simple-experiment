#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "gmockcscene.h"
#include "gmockcsceneitem.h"
#include "csceneitemtestfactory.h"

using ::testing::AtLeast;
using ::testing::_;

class TestCSceneItem : public ::testing::Test
{
public:
   CSceneItemTestFactory m_itemFactory;
};

TEST_F(TestCSceneItem, TestOnEvent)
{
   GMockCScene scene;
   
   auto item0  = m_itemFactory.createMockItem();
   auto child0 = m_itemFactory.createMockItem(item0);
   auto child1 = m_itemFactory.createMockItem(item0);
   auto child3 = m_itemFactory.createMockItem(child0);
   auto child4 = m_itemFactory.createMockItem(child3);
   
   EXPECT_CALL(scene, updateItem(_)).Times(1);
   EXPECT_CALL(*item0, onEvent(_)).Times(1);
   EXPECT_CALL(*child0, onEvent(_)).Times(1);
   EXPECT_CALL(*child1, onEvent(_)).Times(1);
   EXPECT_CALL(*child3, onEvent(_)).Times(1);
   EXPECT_CALL(*child4, onEvent(_)).Times(1);
   
   scene.addItem(item0);
}
