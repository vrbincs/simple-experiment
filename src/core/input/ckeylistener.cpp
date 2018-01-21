#include "ienginedevice.h"
#include "ieventfactory.h"

#include "logging.h"
#include "ckeylistener.h"

CKeyListener::~CKeyListener()
{
   disconnect();
}

bool CKeyListener::onEvent(const CEvent *event)
{
   if(event->type() == CEvent::EventTypeKeyDown)
   {
      return keyDown(event);
   }
   else if(event->type() == CEvent::EventTypeKeyUp)
   {
      return keyUp(event);
   }
   
   LOGGER_ERROR("Unknown event type." << event->type());
   return false;
}

void CKeyListener::connect()
{
   IEngineDevice::instance()->getKeyEventFactory()->addListener(this);
}

void CKeyListener::disconnect()
{
   IEngineDevice::instance()->getKeyEventFactory()->removeListener(this);
}
