#include <string>
#include <cassert>

#include "logging.h"

#include <cengine2d.h>

class CBallItem : public CSceneItem
{
public:
   CBallItem(const std::string &filePath, CSceneItem *parent = NULL)
      : CSceneItem(parent),
        m_pixmap(NULL),
        m_x(0),
        m_y(0)
   {
      m_pixmap = new CPixmap(filePath, "bmp");
   }
   
   ~CBallItem()
   {
      delete m_pixmap;
   }
   
   CRectI itemRegion() const
   {
      CPointI position = getPosition();
      return CRectI(position.getX(),
                    position.getY(),
                    m_pixmap->getWidth(),
                    m_pixmap->getHeight());
   }
   
   void move(int dx, int dy)
   {
      CPointI &pos = getPosition();
      pos.m_x += dx;
      pos.m_y += dy;
      
      update();
   }
   CPixmap *m_pixmap;
   int m_x;
   int m_y;   
protected:
   void repaint(CPaintTool *paintTool, const CRectI &updateRegion)
   {
      paintTool->drawPixmap(*m_pixmap, getPosition(), NULL);
   }
private:

};

int main(int argc, char *argv[])
{
   IEngineDevice *engineDevice = CEngine2d::createDevice(IVideoDevice::DeviceTypeSdl,
                                                         CSizeI(1920, 1200));
   assert(engineDevice != NULL);
   
   IVideoDevice *videoDevice = engineDevice->getVideoDevice();
   assert(videoDevice != NULL);
   
   CScene scene(CRectI(200,200,700,700));
   CBallItem ballMain("ball_big.bmp");
   CBallItem ballChild1("ball_small.bmp", &ballMain);
   CBallItem ballChild2("ball_small.bmp", &ballMain);
   ballMain.setPosition(CPointI(-200,-200));
   
   ballChild1.setPosition(CPointI(100,0));
   ballChild2.setPosition(CPointI(0,100));
   
   scene.addItem(&ballMain);
   scene.setBackgroundColor(CColour(0,0,100,255));
   CColour background(CColour(0,0,0,255));
   
   
   while(engineDevice->run())
   {
      //if(ballMain.getPosition().getX() <= 200)
      {
         videoDevice->start(&background);
         scene.redraw();
         
         ballMain.move(1,1);
         
         engineDevice->drawFps();
         videoDevice->end();
      }
   }
   
   return 0;
}
