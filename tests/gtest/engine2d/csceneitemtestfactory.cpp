#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "csceneitemtestfactory.h"

CSceneItemTestFactory::~CSceneItemTestFactory()
{
   for(auto it0=m_rootItems.begin(); it0!=m_rootItems.end(); it0++)
   {
      delete *it0;
   }
}


NiceMock<GMockCSceneItem> *CSceneItemTestFactory::createMockItem(CSceneItem *parent,
                                                                 const CRectF &rect)
{
   auto item = new NiceMock<GMockCSceneItem>(rect, parent);
   
   item->delegateToFake();
   if(parent == NULL)
   {
      m_rootItems.insert(item);
   }
   
   return item;
}
