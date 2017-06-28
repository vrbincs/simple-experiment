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
   CBallItem ball0("ball_big.bmp");
   CBallItem ball1("ball_big.bmp");
   CBallItem ball2("ball_big.bmp");
   CBallItem ball3("ball_big.bmp");
   CBallItem ballChild1("ball_small.bmp", &ball0);
   CBallItem ballChild2("ball_small.bmp", &ball1);
   ball0.setPosition(CPointI(-100,-100));
   ball1.setPosition(CPointI(-100, 600));
   ball2.setPosition(CPointI( 600, 600));
   ball3.setPosition(CPointI( 600,-100));
   
   ballChild1.setPosition(CPointI(100,0));
   ballChild2.setPosition(CPointI(0,100));
   
   scene.addItem(&ball0);
   scene.addItem(&ball1);
   scene.addItem(&ball2);
   scene.addItem(&ball3);
   
   scene.setBackgroundColor(CColour(0,0,100,255));
   CColour background(CColour(0,0,0,255));
   int speed = 1;
   while(engineDevice->run())
   {
      if(ball0.getPosition().getX() == 600)
      {
         speed = -1;
      }
      else if(ball0.getPosition().getX() == -100)
      {
         speed = 1;
      }

      videoDevice->start(&background);
      scene.redraw();
      
      ball0.move(speed,speed);
      ball1.move(speed,-speed);
      ball2.move(-speed,-speed);
      ball3.move(-speed,speed);
      
      engineDevice->drawFps();
      videoDevice->end();
   }
   
   return 0;
}
