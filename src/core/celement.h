#ifndef CELEMENT_H
   #define CELEMENT_H

#include <vector>

class IEventListener;

class CElement
{
public:
   CElement();
   virtual ~CElement();
   
   std::string getId() const;
   
   void addListener(IEventListener *listener);
   void removeListener(IEventListener *listener);

private:   
   std::vector<IEventListener *> m_listeners;
   
   void clearListener(IEventListener *listener);
   void clearAllListeners();
};

#endif // CELEMENT_H
