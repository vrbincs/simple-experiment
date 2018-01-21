#ifndef IEVENTFACTORY_H
   #define IEVENTFACTORY_H

#include <vector>

#include <ieventlistener.h>
#include <cevent.h>

class IEventFactory
{
   friend class IEventListener;
   
public:
   virtual ~IEventFactory(){}
   
   /**
    * \brief Should be called on every cycle in order to poll events
    * from the source (device) and dispatch them to the listeners.
    * 
    * It should normally be called from the engine's main even loop.
    */
   virtual void poll() = 0;

   /**
    * \brief Add listener to the list of listeners. The dispatch function
    * will travers over the list of listeners and call 
    * IEventListener::onEvent().
    * 
    * \param[in] listener: a pointer to a listener.
    */
   inline void addListener(IEventListener *listener);
   
   /**
    * \brief remove the listener of the list of listeners.
    */
   inline void removeListener(const IEventListener *listener);
protected:
   /**
    * \brief A helper function that creates an event with the given
    * parameters. A derive class may or may not use it.
    */
   inline CEvent *createEvent(int type, 
                              const CEvent::UMessage &message,
                              uint32_t timestamp) const;

   /**
    * \brief This function should be used by all derived class for 
    * dispatching events to the listeners.
    * 
    * \param[in] event: A pointer to an event which can be anything.
    */
   inline void dispatch(const CEvent *event);
private:
   std::vector<IEventListener *> m_listeners;
};

CEvent *IEventFactory::createEvent(int type, 
                                   const CEvent::UMessage &message,
                                   uint32_t timestamp) const
{
   return new CEvent(type, message, timestamp);
}

inline void IEventFactory::addListener(IEventListener *listener)
{
   m_listeners.push_back(listener);
}

inline void IEventFactory::removeListener(const IEventListener *listener)
{
   for(auto it = m_listeners.begin(); it != m_listeners.end(); it++)
   {
      if(*it == listener)
      {
         m_listeners.erase(it);
         break;
      }
   }
}

inline void IEventFactory::dispatch(const CEvent *event)
{
   for(auto it = m_listeners.begin(); it != m_listeners.end(); it++)
   {
      if((*it)->onEvent(event))
      {
         break;
      }
   }
   
   delete event;
}

#endif // IEVENTFACTORY_H
