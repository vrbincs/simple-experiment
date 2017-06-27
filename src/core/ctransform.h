#ifndef CTRANSFORM_H
   #define CTRANSFORM_H

#include <cstdint>

#include <cpoint.h>

class CTransfrom
{
public:
   CTransfrom();
   virtual ~CTransfrom();
   
   void translate(int32_t dx, int32_t dy);
   void translate(const CPointI &pos);
   
   void setPosition(const CPointI &pos);
   CPointI getPosition() const;
   CPointI &getPosition();
   
   void clear();
private:
   CPointI m_position;
};


#endif // CTRANSFORM
