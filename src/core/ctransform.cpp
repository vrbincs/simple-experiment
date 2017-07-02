#include "ctransform.h"


CTransform::CTransform()
   : m_angle(0)
{
}

CTransform::CTransform(const CPointF &position)
   : m_position(position),
     m_angle(0)
{
}

CTransform::~CTransform()
{
}

void CTransform::translate(int32_t dx, int32_t dy)
{
   m_position.m_x += dx;
   m_position.m_y += dy;
}

void CTransform::translate(const CPointF &pos)
{
   m_position += pos;
}

void CTransform::rotate(float angle)
{
   m_angle = angle;
}

void CTransform::setPosition(const CPointF &pos)
{
   m_position = pos;
}

CPointF CTransform::getPosition() const
{
   return m_position;
}

CPointF &CTransform::getPosition()
{
   return m_position;
}

void CTransform::clear()
{
   m_position = CPointF();
}
