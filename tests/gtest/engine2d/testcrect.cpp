#include <gtest/gtest.h>

#include <crect.h>

TEST(TestCRect, TestsClipping1)
{
   CRectI rect1(0,0,200,200);
   CRectI rect2(150,150,100,100);
   
   CRectI rect3 = rect1.intersection(rect2);
   
   EXPECT_EQ(rect3.getX(), 150);
   EXPECT_EQ(rect3.getY(), 150);
   EXPECT_EQ(rect3.getWidth(), 50);
   EXPECT_EQ(rect3.getHeight(), 50);
}

TEST(TestCRect, TestsClipping2)
{
   CRectI rect1(0,0,200,200);
   CRectI rect2(150,150,100,100);
   
   CRectI rect3 = rect2.intersection(rect1);
   
   EXPECT_EQ(rect3.getX(), 150);
   EXPECT_EQ(rect3.getY(), 150);
   EXPECT_EQ(rect3.getWidth(), 50);
   EXPECT_EQ(rect3.getHeight(), 50);
}

TEST(TestCRect, TestsClipping3)
{
   CRectI rect1(755,755,200,200);
   CRectI rect2(200,200,700,700);
   
   CRectI rect3 = rect1.intersection(rect2);
   
   EXPECT_EQ(rect3.getX(), 755);
   EXPECT_EQ(rect3.getY(), 755);
   EXPECT_EQ(rect3.getWidth(), 145);
   EXPECT_EQ(rect3.getHeight(), 145);
}

TEST(TestCRect, TestsClipping4)
{
   CRectI rect1(1,1,200,200);
   CRectI rect2(200,200,700,700);
   
   CRectI rect3 = rect1.intersection(rect2);
   
   EXPECT_EQ(rect3.getX(), 200);
   EXPECT_EQ(rect3.getY(), 200);
   EXPECT_EQ(rect3.getWidth(), 1);
   EXPECT_EQ(rect3.getHeight(), 1);
}
