#include <gtest/gtest.h>

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
      : m_device(NULL)
   {
      m_device = CEngine2d::createDevice(IVideoDevice::DeviceTypePseudo,
                                         CSizeI(800, 600));

      assertRequirements();
   }
   
   ~TestCSpriteQueue()
   {
      if(m_device)
      {
         m_device->exit();
      }
   }

   void assertRequirements()
   {
      ASSERT_TRUE((m_device != NULL));
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
};

TEST_F(TestCSpriteQueue, TestSpriteCount)
{
   CPixmap *pixmap = loadRawImageFromFile(RESOURCE_CHECKER_PATH, 
                                          RESOURCE_CHECKER_WIDTH,
                                          RESOURCE_CHECKER_HEIGHT,
                                          RESOURCE_CHECKER_DEPTH);
   ASSERT_TRUE((pixmap != NULL));
   ASSERT_TRUE(!pixmap->isNull());
   
   CSpriteQueue spriteQueue(pixmap, 100, 100);
   
   ASSERT_TRUE(spriteQueue.isValid());
   ASSERT_EQ(spriteQueue.spriteCount(), 6);
}
