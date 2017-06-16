#include "cevent.h"

#define USER_TYPE 4096

CEvent::CEvent(int type, const UMessage &message)
   : UserEventType(USER_TYPE),
     m_type(type),
     m_message(message)
{
}

CEvent::~CEvent()
{
}

int CEvent::type() const
{
   return m_type;
}

CEvent::UMessage CEvent::message() const
{
   return m_message;
}
