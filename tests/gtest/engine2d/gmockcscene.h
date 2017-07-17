#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cscene.h>

using ::testing::_;
using ::testing::Invoke;

class GMockCScene : public CScene
{
public:
   GMockCScene(const CRectI &rect = CRectI(0,0,0,0)) : CScene(rect){}
   
   MOCK_METHOD1(updateItem, void(CSceneItem *));
};
