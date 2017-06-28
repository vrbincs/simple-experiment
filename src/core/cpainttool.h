#ifndef CPAINTTOOL_H
   #define CPAINTTOOL_H

#include <crect.h>
#include <cpoint.h>
#include <ccolour.h>

class IPaintDevice;
class CPixmap;
class CPaintToolPriv;
class CTransform;

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
   void restore();
   
   void setPaintSettings(const SPaintSettings &paintSettings);
   void setClipArea(const CRectI &clip);
   
   void drawRect(const CRectI &rect);
   void drawPixmap(const CPixmap &pixmap, const CPointI &pos, const CRectI *srcRect = NULL);
   void drawText(const std::string &text,
                 const CRectI &rect);

   void setTransform(const CTransform &transform);
   CTransform getTransform() const;
   CTransform &getTransform();
private:
   IPaintDevice *m_pPaintDevice;
   CPaintToolPriv *m_paintToolPriv;
};

#endif // CPAINTTOOL_H
