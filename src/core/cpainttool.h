#ifndef CPAINTTOOL_H
   #define CPAINTTOOL_H

#include <crect.h>
#include <cpoint.h>
#include <ccolour.h>

class IPaintDevice;
class CPixmap;
class CPaintToolPriv;
class CTransfrom;

class CPaintTool
{
public:
   struct SPaintSettings
   {
      CColour bgColour;
      CColour fgColour;
   };

   CPaintTool(CPixmap *pixmap);
   CPaintTool(IPaintDevice *paintDevice);
   virtual ~CPaintTool();
   
   bool start(CPixmap *pixmap);
   bool end();
   
   void save();
   void reset();
   
   void setPaintSettings(const SPaintSettings &paintSettings);
   
   void drawRect(const CRectI &rect);
   void drawPixmap(const CPixmap &pixmap, const CPointI &pos, const CRectI *srcRect = NULL);
   void drawText(const std::string &text,
                 const CRectI &rect);

   void setTransform(const CTransfrom &transform);
   CTransfrom getTransform() const;
   CTransfrom &getTransform();
private:
   IPaintDevice *m_pPaintDevice;
   CPaintToolPriv *m_paintToolPriv;
};

#endif // CPAINTTOOL_H
