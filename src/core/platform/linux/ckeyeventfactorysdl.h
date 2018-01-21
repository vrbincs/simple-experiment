#ifndef CKEYEVENTFACTORYSDL_H
   #define CKEYEVENTFACTORYSDL_H

#include <ieventfactory.h>

class CKeyEventFactorySDL : public IEventFactory
{
public:
   CKeyEventFactorySDL();
   
   virtual void poll() override;

   static IEventFactory *instance();
private:
   static IEventFactory *m_instance;
   
   CEvent *createCEventFromSDLEvent(SDL_Event &sdlEvent);
};

#endif // CKEYEVENTFACTORYSDL_H
