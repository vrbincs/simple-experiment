#ifndef CTRANSFORM_H
   #define CTRANSFORM_H

#include <cstdint>

#include <cpoint.h>

class CTransform
{
public:
   CTransform();
   CTransform(const CPointF &position);
   virtual ~CTransform();
   
   void translate(int32_t dx, int32_t dy);
   void translate(const CPointF &pos);
   
   void setPosition(const CPointF &pos);
   CPointF getPosition() const;
   CPointF &getPosition();
   
   void clear();
private:
   CPointF m_position;
};


#endif // CTRANSFORM
