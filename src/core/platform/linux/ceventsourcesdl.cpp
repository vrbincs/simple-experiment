#include <SDL.h>

#include "logging.h"
#include "ceventsourcesdl.h"

CEventSourceSDL::CEventSourceSDL()
{
}

CEventSourceSDL::~CEventSourceSDL()
{
}

void CEventSourceSDL::acquireEvents(std::list<CEvent *> &events)
{
   SDL_Event eventSdl;
   while(SDL_PollEvent(&eventSdl))
   {
      CEvent *event = createCEventFromSDLEvent(eventSdl);
      if(event)
      {
         events.push_back(event);
      }
      else
      {
         LOGGER_WARN("Unsupport event");
      }
   }
}

CEvent *CEventSourceSDL::createCEventFromSDLEvent(SDL_Event &sdlEvent)
{
   CEvent::UMessage msg;
   
   switch(sdlEvent.type)
   {
      case SDL_QUIT:
         return createEvent(CEvent::EventTypeTerminate, msg);
      break;
      default:
      break;
   }
   
   return NULL;
}
