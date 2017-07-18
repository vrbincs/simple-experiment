#ifndef CSCENEITEMTESTFACTORY_H
   #define CSCENEITEMTESTFACTORY_H

#include <string>
#include <set>

#include <gmock/gmock.h>

#include <csceneitem.h>
#include <crect.h>

#include "gmockcsceneitem.h"

using ::testing::NiceMock;

class CSceneItemTestFactory
{
public:
   virtual ~CSceneItemTestFactory();

   NiceMock<GMockCSceneItem> *createMockItem(CSceneItem *parent = NULL,
                                             const CRectF &rect = CRectF(0,0,0,0));
   

   std::set<NiceMock<GMockCSceneItem> *> m_rootItems;
};

#endif //CSCENEITEMTESTFACTORY_H
