#include "cevent.h"

#define USER_TYPE 4096

CEvent::CEvent(int type, const UMessage &message, uint32_t timestamp)
   : UserEventType(USER_TYPE),
     m_type(type),
     m_message(message),
     m_timestamp(timestamp)
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

uint32_t CEvent::getTimestamp() const
{
   return m_timestamp;
}
