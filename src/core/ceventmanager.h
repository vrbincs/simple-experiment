#ifndef CEVENTMANAGER_H
   #define CEVENTMANAGER_H

#include <set>

class IEventListener;
class IEventFactory;
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
    * \brief registers a source where events are generated.
    * \param[in] eventFactory - a pointer the source where events are 
    * generated
    */
   void registerEventSource(IEventFactory *eventFactory);
   
   /**
    * \brief unregister an event source.
    * \param[in] eventFactory - a pointer the source where events are 
    * generated
    * \return returns true if the system has been successdully removed
    * from the list, false otherwise.
    */
   bool unregisterEventSource(IEventFactory *);
   
   /**
    * \brief register a listener to which events will be posted to.
    * \param[in] listener - a pointer to the listener that will start
    * receiving events.
    */
   void registerListener(IEventListener *listener);
   
   /**
    * \brief unlike registerListener(), this function remove a listener
    * \param[in] listener - a pointer to the listener that will stop
    * receiving events.
    * * \return return true is the listener has been successfully
    * removed from the list; false otherwise.
    */
   bool unregisterListener(IEventListener *listener);
private:
   std::set<IEventListener *> m_listenersList;
   std::set<IEventFactory *> m_eventSources;
   
   void disposeEvent(CEvent *event);
};

#endif // CEVENTMANAGER_H
