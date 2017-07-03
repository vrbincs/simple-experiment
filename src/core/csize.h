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
   
   inline bool isZero() const
   {
      if(!m_width || !m_height)
      {
         return true;
      }
      return false;
   }
   
   inline CSize<float> toFloat() const
   {
      return CSize<float>(m_width, m_height);
   }
private:
   T m_width;
   T m_height;
};

typedef CSize<int> CSizeI;
typedef CSize<float> CSizeF;

#endif // CSIZE_H
