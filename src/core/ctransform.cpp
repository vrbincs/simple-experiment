#include "ctransform.h"


CTransfrom::CTransfrom()
{
}

CTransfrom::~CTransfrom()
{
}

void CTransfrom::translate(int32_t dx, int32_t dy)
{
   m_position.m_x += dx;
   m_position.m_y += dy;
}

void CTransfrom::translate(const CPointI &pos)
{
   m_position += pos;
}

void CTransfrom::setPosition(const CPointI &pos)
{
   m_position = pos;
}

CPointI CTransfrom::getPosition() const
{
   return m_position;
}

CPointI &CTransfrom::getPosition()
{
   return m_position;
}

void CTransfrom::clear()
{
   m_position = CPointI();
}
