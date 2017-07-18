#include <gtest/gtest.h>

#include "gmockcsceneitem.h"
#include "csceneitemtestfactory.h"

class TestCGObject : public ::testing::Test
{
public:
   CSceneItemTestFactory m_itemFactory;
};

TEST_F(TestCGObject, TestParentIsSet)
{
   auto parent = m_itemFactory.createMockItem();
   auto child1 = m_itemFactory.createMockItem(parent);
   auto child2 = m_itemFactory.createMockItem();
   
   m_itemFactory.m_rootItems.erase(child2);
   
   EXPECT_TRUE(child2->setParent(child1));
   EXPECT_TRUE((child2->getParent() == child1));
   EXPECT_TRUE((child1->getParent() == parent));
   EXPECT_TRUE((parent->getParent() == NULL));
}
