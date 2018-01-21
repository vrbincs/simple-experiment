#ifndef IEVENTLISTENER_H
   #define IEVENTLISTENER_H

class CEvent;
class CElement;
class IEngineDevice;
class IEventFactory;

class IEventListener
{
   friend class CElement;
   friend class IEventFactory;
   
public:
   virtual ~IEventListener(){}

protected:
   /**
    * \brief This function is called from the CEventManager when an
    * event has arrived. If a listener is not interested in the event
    * it should ignore it and return false. An event will no longer be
    * processed by any other listener, if this funciton returns true.
    */
   virtual bool onEvent(const CEvent *event) = 0;

   virtual void connect() = 0;
   virtual void disconnect() = 0;
};

#endif // IEVENTLISTENER_H
