#ifndef IEVENTFACTORY_H
   #define IEVENTFACTORY_H

#include <list>

#include <cevent.h>

class IEventFactory
{
public:
   virtual ~IEventFactory(){}

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

CEvent *IEventFactory::createEvent(int type, 
                                   const CEvent::UMessage &message,
                                   uint32_t timestamp) const
{
   return new CEvent(type, message, timestamp);
}

#endif // IEVENTFACTORY_H
