#ifndef IGAMEDELEGATE_H
   #define IGAMEDELEGATE_H

#include <cstdint>

class IGameDelegate
{
public:
   /**
    * \brief The client should implement game logic in this function.
    */
   virtual void processLogic(uint32_t delta) = 0;

   /**
    * \brief All routines for rendering graphics should be here.
    */
   virtual void render() = 0;
};

#endif // IGAMEDELEGATE_H
