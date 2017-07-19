#ifndef TESTCSCENEITEMFACTORY_H
   #define TESTCSCENEITEMFACTORY_H

#include <string>

class CSceneItem;

class TestCSceneItemFactory
{
public:
   CSceneItem *createItem(const std::string &itemName);
};

#endif //TESTCSCENEITEMFACTORY_H
