#ifndef CEVENTMANAGER_H
   #define CEVENTMANAGER_H

#include <list>

class IEventListener;
class IEventSource;
class CEvent;

class CEventManager
{
public:
   CEventManager();
   virtual ~CEventManager();
   
   /**
    * \brief this function will traverse over all event systems and post
    * all events to the listeners. A call has to be made on every
    * iteration.
    */
   void pollEvents();
   
   /**
    * \brief added an event system that generates events.
    * \return returns true if the system has been successdully added
    * to the list, false otherwise.
    */
   void registerEventSource(IEventSource *);
   
   bool unregisterEventSource(IEventSource *);
   
   /**
    * \brief register a listener to which events will be posted to.
    * \return return true is the listener has been successfully added to
    * the list; false otherwise.
    */
   void registerListener(IEventListener *listener);
   
   /**
    * \brief unlike registerListener(), this function remove a listener
    * from the list.
    */
   bool unregisterListener(IEventListener *listener);
private:
   std::list<IEventListener *> m_listenersList;
   std::list<IEventSource *> m_eventSources;
   
   void disposeEvent(CEvent *event);
};

#endif // CEVENTMANAGER_H
