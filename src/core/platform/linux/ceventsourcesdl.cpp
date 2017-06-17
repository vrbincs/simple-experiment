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
         LOGGER_WARN("Unsupported event. eventType=" << eventSdl.type);
      }
   }
}

CEvent *CEventSourceSDL::createCEventFromSDLEvent(SDL_Event &sdlEvent)
{
   CEvent::UMessage msg;
   int type;
   uint32_t timestamp = 0;
   
   switch(sdlEvent.type)
   {
      case SDL_QUIT:
         type = CEvent::EventTypeTerminate;
      break;
      case SDL_KEYUP:
         type = CEvent::EventTypeKeyUp;
         msg.keyCode = getKeyCode(sdlEvent.key.keysym.scancode);
      break;
      case SDL_KEYDOWN:
         type = CEvent::EventTypeKeyDown;
         msg.keyCode = getKeyCode(sdlEvent.key.keysym.scancode);
      break;
      default:
         return NULL;
      break;
   }
   
   CEvent *event = createEvent(type, msg, timestamp);
   return event;
}

int CEventSourceSDL::getKeyCode(int sdlScanCode)
{
   switch(sdlScanCode)
   {
      case SDL_SCANCODE_ESCAPE:
         return CEvent::KeyEscape;
      break;
      case SDL_SCANCODE_SPACE:
         return CEvent::KeySpace;
      break;
      case SDL_SCANCODE_RIGHT:
         return CEvent::KeyArrowRight;
      break;
      case SDL_SCANCODE_LEFT:
         return CEvent::KeyArrowLeft;
      break;
      case SDL_SCANCODE_DOWN:
         return CEvent::KeyArrowDown;
      break;
      case SDL_SCANCODE_UP:
         return CEvent::KeyArrowUp;
      break;
   }
   return sdlScanCode;
}
