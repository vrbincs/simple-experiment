#include <string>
#include <cassert>
#include <cmath>
#include <memory>

#include "logging.h"

#include <cengine2d.h>

#define PI 3.14159

static CScene *scene = new CScene(CRectF(300,300,1200,1200), CPointF(0,0));

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
      
      update();
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

class CBackground : public CSceneItem
{
public:
   CBackground(const std::string &bmpPath)
   {
      m_pixmap = new CPixmap(bmpPath, "bmp");
      
      if(m_pixmap)
      {
         m_rect = CRectF(CPointF(0,0), m_pixmap->getSize().toFloat());
      }
   }
   
   CRectF itemRegion() const
   {
      return m_rect;
   }
protected:
   CPixmap *m_pixmap;
   CRectF m_rect;
   
   void repaint(CPaintTool *paintTool, const CRectF &updateRegion)
   {
      paintTool->save();
      paintTool->drawPixmap(*m_pixmap, CPointF(0,0), NULL);
      paintTool->restore();
   }
};

static bool m_exitProgram = false;
static bool m_leftDown  = false;
static bool m_rightDown = false;
static bool m_upDown    = false;
static bool m_downDown  = false;

class CTestEventListener : public IEventListener
{
public:
   bool onEvent(const CEvent &event)
   {
      bool isKeyDown = (event.type() == CEvent::EventTypeKeyDown);
      
      if(isKeyDown || event.type() == CEvent::EventTypeKeyUp )
      {
         if(event.message().keyCode == CEvent::KeyEscape)
         {
            m_exitProgram = true;
         }
         else if(event.message().keyCode == CEvent::KeyArrowLeft)
         {
            m_leftDown = isKeyDown;
         }
         else if(event.message().keyCode == CEvent::KeyArrowRight)
         {
            m_rightDown = isKeyDown;
         }
         else if(event.message().keyCode == CEvent::KeyArrowUp)
         {
            m_upDown = isKeyDown;
         }
         else if(event.message().keyCode == CEvent::KeyArrowDown)
         {
            m_downDown = isKeyDown;
         }
      }
      
      return false;
   }
};

int main(int argc, char *argv[])
{
   IEngineDevice *engineDevice = CEngine2d::createDevice(IVideoDevice::DeviceTypeSdl);
   assert(engineDevice != NULL);
   
   engineDevice->showFps();
   
   CBackground backgroundChecker("background.bmp");
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
   
   backgroundChecker.setZIndex(-1);
   scene->addItem(&backgroundChecker);
   scene->addItem(&ball0);
   scene->addItem(&ball1);
   scene->addItem(&ball2);
   scene->addItem(&ball3);
   
   std::shared_ptr<CTestEventListener> eventListenerPtr(new CTestEventListener());
   engineDevice->getEventManager()->registerListener(eventListenerPtr.get());
   
   scene->setBackgroundColor(CColour(0,50,50,255));
   
   CColour background(CColour(0,0,0,255));
   double speed = 1;
   double scenePosX = 0;
   double scenePosY = 0;
   while(engineDevice->run())
   {
      if(m_exitProgram)
      {
         break;
      }
      
      double ticks = ((double)engineDevice->getDeltaTicks()*0.00015);
      
      if(m_leftDown)
      {
         scenePosX -= (ticks);
      }
      else if(m_rightDown)
      {
         scenePosX += (ticks);
      }
      
      if(m_upDown)
      {
         scenePosY -= (ticks);
      }
      else if(m_downDown)
      {
         scenePosY += (ticks);
      }
      
      scene->setScenePosition(CPointF(scenePosX, scenePosY));
      
      if(ball0.getPosition().getX() >= 600)
      {
         speed = -1;
      }
      else if(ball0.getPosition().getX() <= -100)
      {
         speed = 1;
      }

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
      
      scene->redraw();
   }
   
   return 0;
}
