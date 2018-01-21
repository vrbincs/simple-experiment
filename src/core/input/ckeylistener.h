#ifndef CKEYLISTENER_H
   #define CKEYLISTENER_H

#include <ieventlistener.h>

class CKeyListener : public IEventListener
{
public:
   ~CKeyListener();
   virtual bool keyDown(const CEvent *event) = 0;
   virtual bool keyUp(const CEvent *event) = 0;
protected:
   bool onEvent(const CEvent *event) override;
   
   void connect() override;
   void disconnect() override;
};

#endif // CKEYLISTENER_H
