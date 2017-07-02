#include <list>

#include "logging.h"

#include "ieventsource.h"
#include "ieventlistener.h"
#include "cevent.h"
#include "ceventmanager.h"

CEventManager::CEventManager()
{
}

CEventManager::~CEventManager()
{
}

void CEventManager::pollEvents()
{
   std::list<CEvent *> eventListTmp;
   
   // First we get a list of events from all sources.
   for(auto it = m_eventSources.begin(); it != m_eventSources.end(); it++)
   {
      (*it)->acquireEvents(eventListTmp);
   }
   
   // we post the events to the listeners.
   for(auto it1 = eventListTmp.begin(); it1 != eventListTmp.end(); it1++)
   {
      for(auto it2 = m_listenersList.begin(); it2 != m_listenersList.end(); it2++)
      {
         if((*it2)->onEvent(*(*it1)))
         {
            // we break the loop if a listener does not want any other
            // listener to process the same event.
            break;
         }
      }
      
      // We want to clean-up the event.
      disposeEvent(*it1);
   }
}

void CEventManager::registerEventSource(IEventSource *eventSource)
{
   if(eventSource)
   {
      m_eventSources.insert(eventSource);
   }
   else
   {
      LOGGER_WARN("Invalid event source.");
   }
}

bool CEventManager::unregisterEventSource(IEventSource *eventSource)
{
   for(auto it = m_eventSources.begin(); it != m_eventSources.end(); it++)
   {
      if(*it == eventSource)
      {
         m_eventSources.erase(it);
         return true;
      }
   }
   
   return false;
}

void CEventManager::registerListener(IEventListener *listener)
{
   if(listener)
   {
      m_listenersList.insert(listener);
   }
   else
   {
      LOGGER_WARN("Invalid event listener.");
   }
}

bool CEventManager::unregisterListener(IEventListener *listener)
{
   for(auto it = m_listenersList.begin(); it != m_listenersList.end(); it++)
   {
      if(*it == listener)
      {
         m_listenersList.erase(it);
         return true;
      }
   }
   
   return false;
}

void CEventManager::disposeEvent(CEvent *event)
{
   delete event;
}
