#ifndef CEVENT_H
   #define CEVENT_H

class CEvent
{
public:
   enum
   {
      EventTypeTerminate = 0,
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
protected:
   /**
    * \brief constructor
    */
   CEvent();
};

#endif // CEVENT_H
