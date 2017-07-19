#ifndef CEVENTSOURCESDL_H
   #define CEVENTSOURCESDL_H

#include <SDL.h>

#include <ieventfactory.h>

class CEventSourceSDL : public IEventFactory
{
public:
   CEventSourceSDL();
   ~CEventSourceSDL();
   
   void acquireEvents(std::list<CEvent *> &events);
private:
   CEvent *createCEventFromSDLEvent(SDL_Event &sdlEvent);
   int getKeyCode(int sdlScanCode);
};

#endif // CEVENTSOURCESDL_H
