#include <logging.h>

#include "testcsceneitemfactory.h"

#include "gmockcsceneitem.h"

CSceneItem *TestCSceneItemFactory::createItem(const std::string &itemName)
{
   CSceneItem *item = NULL;
   
   if(itemName == "GMockCSceneItem")
   {
      item = new GMockCSceneItem();
   }
   else
   {
      LOGGER_WARN("Unable to create item '" << itemName << "'");
   }
   
   return item;
}
