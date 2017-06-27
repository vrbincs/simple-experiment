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
      return CRectI(m_x,m_y,m_pixmap->getWidth(),m_pixmap->getHeight());
   }
   
   void move(int dx, int dy)
   {
      m_x += dx;
      m_y += dy;
      
      update();
   }
protected:
   void repaint(CPaintTool *paintTool, const CRectI &updateRegion)
   {
      paintTool->drawPixmap(*m_pixmap, CPointI(m_x,m_y), NULL);
      LOGGER_INFO("HUMPH");
   }
private:
   CPixmap *m_pixmap;
   int m_x;
   int m_y;
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
   ballMain.setPosition(CPointI(300,300));
   
   scene.addItem(&ballMain);
   
   while(engineDevice->run())
   {
      videoDevice->start();
      scene.redraw();
      
      ballMain.move(2,2);
      
      videoDevice->end();
   }
   
   return 0;
}
