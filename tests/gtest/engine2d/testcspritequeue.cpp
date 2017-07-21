#include <gtest/gtest.h>

#include <logging.h>
#include <cengine2d.h>
#include <cpixmap.h>
#include <extra/cspritequeue.h>


#include <tools/cxbmloader.h>

#define XSTR(x) #x
#define STR(x) XSTR(x)

#define RESOURCE_CHECKER_PATH STR(RESOURCE_PATH)"/resources/colour_checker.data"
#define RESOURCE_CHECKER_WIDTH   300
#define RESOURCE_CHECKER_HEIGHT  200
#define RESOURCE_CHECKER_DEPTH   24

class TestCSpriteQueue : public ::testing::Test
{
public:
   TestCSpriteQueue()
      : m_device(NULL),
        m_testPixmap(NULL),
        m_testSpriteQueue(NULL)
        
   {
      m_device = CEngine2d::createDevice(IVideoDevice::DeviceTypePseudo,
                                         CSizeI(800, 600));
      
      init();
   }
   
   ~TestCSpriteQueue()
   {
      if(m_device)
      {
         m_device->exit();
      }
      
      delete m_testSpriteQueue;
      delete m_testPixmap;
   }

   void init()
   {
      ASSERT_TRUE((m_device != NULL));
      
      m_testPixmap = loadRawImageFromFile(RESOURCE_CHECKER_PATH, 
                                          RESOURCE_CHECKER_WIDTH,
                                          RESOURCE_CHECKER_HEIGHT,
                                          RESOURCE_CHECKER_DEPTH);
      ASSERT_TRUE((m_testPixmap != NULL));
      ASSERT_TRUE(!m_testPixmap->isNull());
      
      m_testSpriteQueue = new CSpriteQueue(m_testPixmap, 100, 100);
      ASSERT_TRUE(m_testSpriteQueue->isValid());
   }
   
   CPixmap * loadRawImageFromFile(const std::string &filePath,
                                  uint32_t width,
                                  uint32_t height,
                                  uint8_t depth)
   {
      return imageLoader.loadRawImageFromFile(filePath,
                                              width,
                                              height,
                                              depth);
   }
   
   CXBMLoader imageLoader;
   IEngineDevice *m_device;
   CPixmap *m_testPixmap;
   CSpriteQueue *m_testSpriteQueue;
};

TEST_F(TestCSpriteQueue, TestSpriteCount)
{
   ASSERT_EQ(m_testSpriteQueue->spriteCount(), 6);
}
