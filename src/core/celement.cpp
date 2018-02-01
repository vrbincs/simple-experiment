#include <cassert>
#include <string>

#include <logging.h>
LOGGING_INIT("CEngine2D")

#include "ienginedevice.h"
#include "ieventlistener.h"

#include "celement.h"

CElement::CElement()
{
   assert(IEngineDevice::instance() != NULL);
}

CElement::~CElement()
{
   clearAllListeners();
}

std::string CElement::getId() const
{
}

void CElement::addListener(IEventListener *listener)
{
   LOGGER_TRACE("Adding listener. listener=" << listener);
   m_listeners.push_back(listener);
   listener->connect();
}

void CElement::removeListener(IEventListener *listener)
{
   clearListener(listener);
}

void CElement::clearListener(IEventListener *listener)
{
   if(listener)
   {
      for(auto it=m_listeners.begin(); it != m_listeners.end(); it++)
      {
         if(*it == listener)
         {
            listener->disconnect();
            m_listeners.erase(it);
            
            break;
         }
      }
   }
   else
   {
      LOGGER_ERROR("Pointer to listener is NULL.");
   }
}

void CElement::clearAllListeners()
{
   for(auto it=m_listeners.begin(); it != m_listeners.end();)
   {
      (*it)->disconnect();
      it = m_listeners.erase(it);
   }
}
