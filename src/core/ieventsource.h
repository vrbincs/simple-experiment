#ifndef IEVENTSOURCE_H
   #define IEVENTSOURCE_H

#include <list>

#include <cevent.h>

class IEventSource
{
public:
   virtual ~IEventSource(){}

protected:
   /**
    * \brief Acquires events from the source. This function is
    * exclusively meant to be used by CEventManager.
    * 
    * \param[out] events - The function moves fresh events to the list.
    */
   virtual void acquireEvents(std::list<CEvent *> &events) = 0;
   
   inline CEvent *createEvent(int type, 
                              const CEvent::UMessage &message,
                              uint32_t timestamp) const;
   
   friend class CEventManager;
};

CEvent *IEventSource::createEvent(int type, 
                                  const CEvent::UMessage &message,
                                  uint32_t timestamp) const
{
   return new CEvent(type, message, timestamp);
}

#endif // IEVENTSOURCE_H
