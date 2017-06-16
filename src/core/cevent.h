#ifndef CEVENT_H
   #define CEVENT_H

class CEvent
{
public:
   enum
   {
      EventTypeTerminate = 0,
      EventTypeKeyboard = 1,
   };
   
   union UMessage
   {
      int keyCode;
      void *customType;
   };
   
   const int UserEventType;
   
   /**
    * \brief virtual destructor
    */
   virtual ~CEvent();
   
   /**
    * \brief The type of the event
    */
   virtual int type() const;
   
   /**
    * \brief Message associated with the event.
    * 
    */
   virtual UMessage message() const;
protected:
   /**
    * \brief constructor
    */
   CEvent(int type, const UMessage &message);
private:
   int m_type;
   UMessage m_message;
   
   friend class IEventSource;
};

#endif // CEVENT_H
