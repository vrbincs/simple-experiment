#ifndef CSIZE_H
   #define CSIZE_H

template<typename T>
class CSize
{
public:
   CSize(T width = 0, T height = 0)
      : m_width(width),
        m_height(height)
   {
   }
   
   virtual ~CSize(){}
   
   inline T getWidth() const
   {
      return m_width;
   }
   
   inline T getHeight() const
   {
      return m_height;
   }
private:
   T m_width;
   T m_height;
};

typedef CSize<int> CSizeI;

#endif // CSIZE_H
