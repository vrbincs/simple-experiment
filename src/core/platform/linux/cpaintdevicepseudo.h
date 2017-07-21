#ifndef CPAINTDEVICEPSEUDO_H
   #define CPAINTDEVICEPSEUDO_H

#include <ipaintdevice.h>

class CPaintDevicePseudo : public IPaintDevice
{
public:
   bool start(IPaintSurface *destSurface) override;
   void drawRect(const CRectF &rect,
                         const CColour &colour) override;
   void drawSurface(const IPaintSurface &paintSurface,
                            const CPointF &pos,
                            const CRectF *srcRect) override;

   void drawText(const std::string &text,
                         const CRectF &rect,
                         const CColour &colour) override;
   bool end() override;
};

#endif // CPAINTDEVICEPSEUDO_H
