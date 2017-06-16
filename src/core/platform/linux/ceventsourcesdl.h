#ifndef CEVENTSOURCESDL_H
   #define CEVENTSOURCESDL_H

#include <SDL.h>

#include <ieventsource.h>

class CEventSourceSDL : public IEventSource
{
public:
   CEventSourceSDL();
   ~CEventSourceSDL();
   
   void acquireEvents(std::list<CEvent *> &events);
   CEvent *createCEventFromSDLEvent(SDL_Event &sdlEvent);
};

#endif // CEVENTSOURCESDL_H
