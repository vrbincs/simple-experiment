#include "cevent.h"

#define USER_TYPE 4096

CEvent::CEvent()
   : UserEventType(USER_TYPE)
{
   
}

CEvent::~CEvent()
{
}

int CEvent::type() const
{
   return -1;
}
