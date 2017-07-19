#ifndef CXBMLOADER_H
   #define CXBMLOADER_H

#include <string>


class CPixmap;
class CColour;

class CXBMLoader
{
public:
   CXBMLoader(const CColour &colour = CColour(0,0,0,0));
   CPixmap *loadXBM(const std::string &file);
   CPixmap *loadFromBuffer(void *buffer, int32_t width, int32_t height);
   
   CPixmap *loadRawImageFromFile(const std::string &file,
                                 int32_t width,
                                 int32_t height,
                                 int32_t depth);
private:
   CColour m_colour;
};

#endif // CXBMLOADER_H
