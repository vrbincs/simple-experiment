#ifndef GMOCKCSENE_H
   #define GMOCKCSENE_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cscene.h>

using ::testing::_;
using ::testing::Invoke;

class GMockCScene : public CScene
{
public:
   GMockCScene(const CRectF &rect = CRectF(0,0,0,0)) : CScene(rect){}
   
   MOCK_METHOD1(updateItem, void(CSceneItem *));
};

#endif // GMOCKCSENE_H
