#ifndef CEVENT_H
   #define CEVENT_H

#include <stdint.h>

class CEvent
{
public:
   enum
   {
      EventTypeTerminate = 0,
      EventTypeKeyDown,
      EventTypeKeyUp,
      
      EventTypeSceneAdded,
      EventTypeSceneRemoved
   };
   
   enum
   {
      KeyEscape       = 41,
      KeySpace        = 44,
      KeyArrowRight   = 79,
      KeyArrowLeft    = 80,
      KeyArrowDown    = 81,
      KeyArrowUp      = 82,
   };
   
   union UMessage
   {
      int keyCode;
      void *customType;
   };
   
   const int UserEventType;
   
   /**
    * \brief constructor
    */
   CEvent(int type, const UMessage &message, uint32_t timestamp);
   
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
   
   uint32_t getTimestamp() const;
protected:
private:
   int m_type;
   UMessage m_message;
   uint32_t m_timestamp;
   
   friend class IEventFactory;
};

#endif // CEVENT_H
