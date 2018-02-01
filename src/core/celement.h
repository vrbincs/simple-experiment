#ifndef CELEMENT_H
   #define CELEMENT_H

#include <vector>
#include <string>

class IEventListener;

class CElement
{
public:
   CElement();
   virtual ~CElement();
   
   std::string getId() const;
   
   void addListener(IEventListener *listener);
   void removeListener(IEventListener *listener);

   virtual void cycle(uint32_t delta){}
private:   
   std::vector<IEventListener *> m_listeners;
   
   void clearListener(IEventListener *listener);
   void clearAllListeners();
};

#endif // CELEMENT_H
