#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "gmockcscene.h"
#include "gmockcsceneitem.h"

using ::testing::AtLeast;
using ::testing::_;

TEST(TestCSceneItem, TestOnEvent)
{
   GMockCScene scene;
   GMockCSceneItem item0;
   GMockCSceneItem child0(&item0);
   GMockCSceneItem child1(&item0);
   GMockCSceneItem child3(&child0);
   GMockCSceneItem child4(&child3);
   
   EXPECT_CALL(scene, updateItem(_)).Times(1);
   EXPECT_CALL(item0, onEvent(_)).Times(1);
   EXPECT_CALL(child0, onEvent(_)).Times(1);
   EXPECT_CALL(child1, onEvent(_)).Times(1);
   EXPECT_CALL(child3, onEvent(_)).Times(1);
   EXPECT_CALL(child4, onEvent(_)).Times(1);
   
   scene.addItem(&item0);
}
