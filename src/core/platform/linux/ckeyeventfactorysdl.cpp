#include <SDL.h>

#include "logging.h"
#include "ckeyeventfactorysdl.h"

static int getKeyCode(int sdlScanCode);

IEventFactory *CKeyEventFactorySDL::m_instance = NULL;

CKeyEventFactorySDL::CKeyEventFactorySDL()
{
   
}

void CKeyEventFactorySDL::poll()
{
   SDL_Event eventSdl;
   
   while(SDL_PollEvent(&eventSdl))
   {
      CEvent *event = createCEventFromSDLEvent(eventSdl);
      if(event)
      {
         dispatch(event);
      }
      else
      {
         LOGGER_WARN("Unsupported event. eventType=" << eventSdl.type);
      }
   }
}

IEventFactory *CKeyEventFactorySDL::instance()
{
   if(!m_instance)
   {
      m_instance = new CKeyEventFactorySDL();
   }
   
   return m_instance;
}

CEvent *CKeyEventFactorySDL::createCEventFromSDLEvent(SDL_Event &sdlEvent)
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
   
   return createEvent(type, msg, timestamp);
}

int getKeyCode(int sdlScanCode)
{
   switch(sdlScanCode)
   {
      case SDL_SCANCODE_ESCAPE:
         return CEvent::Key_Escape;
      break;
      case SDL_SCANCODE_SPACE:
         return CEvent::Key_Space;
      break;
      case SDL_SCANCODE_RIGHT:
         return CEvent::Key_ArrowRight;
      break;
      case SDL_SCANCODE_LEFT:
         return CEvent::Key_ArrowLeft;
      break;
      case SDL_SCANCODE_DOWN:
         return CEvent::Key_ArrowDown;
      break;
      case SDL_SCANCODE_UP:
         return CEvent::Key_ArrowUp;
      break;
   }
   return sdlScanCode;
}
