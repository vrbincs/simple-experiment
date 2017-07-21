#include "cpaintdevicepseudo.h"

bool CPaintDevicePseudo::start(IPaintSurface *destSurface)
{
   return false;
}

void CPaintDevicePseudo::drawRect(const CRectF &rect,
                                  const CColour &colour)
{
}

void CPaintDevicePseudo::drawSurface(const IPaintSurface &paintSurface,
                                     const CPointF &pos,
                                     const CRectF *srcRect)
{
}

void CPaintDevicePseudo::drawText(const std::string &text,
                                  const CRectF &rect,
                                  const CColour &colour)
{
}

bool CPaintDevicePseudo::end()
{
   return false;
}
