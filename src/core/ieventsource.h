#ifndef IEVENTSOURCE_H
   #define IEVENTSOURCE_H

#include <list>

class CEvent;

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
   
   friend class CEventManager;
};

#endif // IEVENTSOURCE_H
