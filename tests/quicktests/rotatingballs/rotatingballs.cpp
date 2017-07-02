#include <string>
#include <cassert>
#include <cmath>

#include "logging.h"

#include <cengine2d.h>

#define PI 3.14159

class CBallItem : public CSceneItem
{
public:
   CBallItem(const std::string &filePath, CSceneItem *parent = NULL, double angleOffset = 0)
      : CSceneItem(parent),
        m_pixmap(NULL),
        m_angle(angleOffset)
   {
      m_pixmap = new CPixmap(filePath, "bmp");
      
      if(parent && m_pixmap)
      {
         CSizeF parentSize = parent->itemRegion().getSize();
         m_centerPos = CSizeF(((parentSize.getWidth()/2) - m_pixmap->getWidth()/2),
                              ((parentSize.getHeight()/2) - m_pixmap->getHeight()/2));
      }
   }
   
   ~CBallItem()
   {
      delete m_pixmap;
   }
   
   CRectF itemRegion() const
   {
      CPointF position = getPosition();
      return CRectF(position.getX(),
                    position.getY(),
                    m_pixmap->getWidth(),
                    m_pixmap->getHeight());
   }
   
   void move(float dx, float dy)
   {
      CPointF &pos = getPosition();
      pos.m_x += dx;
      pos.m_y += dy;
      
      update();
   }
   
   void rotate(int distance, float angleRad)
   {
      m_angle = (m_angle + angleRad);
      if(m_angle >= (2*PI))
      {
         m_angle = 0;
      }
      
      CPointF &pos = getPosition();
      pos.m_x = (cos(m_angle) * distance) + (m_centerPos.getWidth());
      pos.m_y = (sin(m_angle) * distance) + (m_centerPos.getHeight());
   }
   
   CPixmap *m_pixmap;
   float m_angle;
   CSizeF m_centerPos;
protected:
   void repaint(CPaintTool *paintTool, const CRectF &updateRegion)
   {
      paintTool->save();
      paintTool->drawPixmap(*m_pixmap, getPosition(), NULL);
      paintTool->restore();
   }
private:

};
#include <unistd.h>
int main(int argc, char *argv[])
{
   IEngineDevice *engineDevice = CEngine2d::createDevice(IVideoDevice::DeviceTypeSdl,
                                                         CSizeI(1920, 1200));
   assert(engineDevice != NULL);
   
   engineDevice->showFps();
   
   CScene scene0(CRectI(200,200,700,700));
   CScene scene1(CRectI(1000,200,700,700));
   CBallItem ball0("ball_big.bmp");
   CBallItem ball1("ball_big.bmp");
   CBallItem ball2("ball_big.bmp");
   CBallItem ball3("ball_big.bmp");
   CBallItem ballChild1("ball_small.bmp", &ball0);
   CBallItem ballChild2("ball_small.bmp", &ball1);
   CBallItem ballChild3("ball_small.bmp", &ball2);
   CBallItem ballChild4("ball_small.bmp", &ball3);
   CBallItem ballChild5("ball_small.bmp", &ball0, ((2*PI)/3));
   CBallItem ballChild6("ball_small.bmp", &ball1, ((2*PI)/3));
   CBallItem ballChild7("ball_small.bmp", &ball2, ((2*PI)/3));
   CBallItem ballChild8("ball_small.bmp", &ball3, ((2*PI)/3));
   CBallItem ballChild9("ball_small.bmp", &ball0, ((4*PI)/3));
   CBallItem ballChild10("ball_small.bmp", &ball1,((4*PI)/3));
   CBallItem ballChild11("ball_small.bmp", &ball2,((4*PI)/3));
   CBallItem ballChild12("ball_small.bmp", &ball3,((4*PI)/3));
   
   ball0.setPosition(CPointF(-100,-100));
   ball1.setPosition(CPointF(-100, 600));
   ball2.setPosition(CPointF( 600, 600));
   ball3.setPosition(CPointF( 600,-100));
   
   scene0.addItem(&ball0);
   scene0.addItem(&ball1);
   scene0.addItem(&ball2);
   scene0.addItem(&ball3);
   
   scene1.addItem(&ball0);
   scene1.addItem(&ball1);
   scene1.addItem(&ball2);
   scene1.addItem(&ball3);
   
   scene0.setBackgroundColor(CColour(0,0,100,255));
   scene1.setBackgroundColor(CColour(0,50,50,255));
   
   CColour background(CColour(0,0,0,255));
   double speed = 1;
   while(engineDevice->run())
   {
      double ticks = ((double)engineDevice->getDeltaTicks()*0.00015);
      
      if(ball0.getPosition().getX() >= 600)
      {
         speed = -1;
      }
      else if(ball0.getPosition().getX() <= -100)
      {
         speed = 1;
      }

      scene0.redraw();
      scene1.redraw();
      
      double moveStep = (ticks * speed);
      ball0.move(moveStep,moveStep);
      ball1.move(moveStep,-moveStep);
      ball2.move(-moveStep,-moveStep);
      ball3.move(-moveStep,moveStep);
      
      double rotationTick = ((float)engineDevice->getDeltaTicks()/(1000000))*PI;
      
      ballChild1.rotate(150, rotationTick);
      ballChild2.rotate(150, rotationTick);
      ballChild3.rotate(150, rotationTick);
      ballChild4.rotate(150, rotationTick);
      ballChild5.rotate(150, rotationTick);
      ballChild6.rotate(150, rotationTick);
      ballChild7.rotate(150, rotationTick);
      ballChild8.rotate(150, rotationTick);
      ballChild9.rotate(150, rotationTick);
      ballChild10.rotate(150, rotationTick);
      ballChild11.rotate(150, rotationTick);
      ballChild12.rotate(150, rotationTick);
   }
   
   return 0;
}
