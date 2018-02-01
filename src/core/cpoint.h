#ifndef CPOINT_H
   #define CPOINT_H

#include <iostream>

template<typename T>
class CPoint
{
public:
   CPoint(T x = 0, T y = 0) : m_x(x), m_y(y) { }
   ~CPoint() {}
   
   void operator+=(const CPoint<T> &pos)
   {
      m_x += pos.m_x;
      m_y += pos.m_y;
   }
   
   void operator-=(const CPoint<T> &pos)
   {
      m_x -= pos.m_x;
      m_y -= pos.m_y;
   }
   
   friend CPoint<T> operator+(const CPoint<T> &pos1, const CPoint<T> &pos2)
   {
      CPoint<T> point = pos1;
      point += pos2;
      
      return point;
   }
   
   friend CPoint<T> operator-(const CPoint<T> &pos1, const CPoint<T> &pos2)
   {
      CPoint<T> point = pos1;
      point -= pos2;
      
      return point;
   }
   
   inline T getX() const { return m_x; }
   inline T getY() const { return m_y; }
   
   inline CPoint<float> toFloat() const
   {
      return CPoint<float>(m_x, m_y);
   }
   
   inline CPoint<int32_t> toInt() const
   {
      return CPoint<int32_t>(m_x, m_y);
   }
   
   inline void move(T x, T y)
   {
      m_x += x;
      m_y += y;
   }
   
   friend std::ostream &operator<<(std::ostream &os, const CPoint<T> &point)
   {
      os << "CPoint(" << point.m_x << "," << point.m_y << ")";
      return os;
   }
   
   T m_x;
   T m_y;
};

typedef CPoint<int> CPointI;
typedef CPoint<float> CPointF;
typedef CPoint<double> CPointD;

#endif // CPOINT_H
