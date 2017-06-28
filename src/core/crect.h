#ifndef CRECT_H
   #define CRECT_H

#include <cmath>
#include <iostream>

#include <cpoint.h>

template<typename T>
class CRect
{
public:
   CRect(T x = 0, T y = 0, T width = 0, T height = 0);
   CRect(const CPoint<T> &p1, const CPoint<T> &p2);
   
   void setPosition(T x, T y);
   void setPosition(const CPoint<T> &position);
   
   void setSize(T width, T height);
   
   void translate(T dx, T dy);
   void translate(const CPoint<T> &point);
   
   bool intersects(const CRect<T> &rect) const;
   CRect intersection(const CRect<T> &rect) const;
   
   void join(const CRect<T> &rect);
   
   CPoint<T> getPosition() const;
   inline T getWidth() const;
   inline T getHeight() const;
   
   inline T getX() const { return m_p1.m_x; }
   inline T getY() const { return m_p1.m_y; }
   
   void normalize();
   
   //void operator+(const CPoint<T> &point);
   void operator+=(const CRect<T> &rect);
   bool operator==(const CRect<T> &rect);
   
   friend CRect<T> operator+(const CRect<T> &rect, const CPoint<T> &point)
   {
      CRect<T> ret = rect;
      ret.translate(point.m_x, point.m_y);
      
      return ret;
   }
   
   friend std::ostream &operator<<(std::ostream &os, const CRect<T> &rect)
   {
      os << "CRect(" << rect.m_p1.m_x << "," << rect.m_p1.m_y << ") (" 
         << rect.m_p2.m_x << "," << rect.m_p2.m_y << ")}";
      return os;
   }
   
   CPoint<T> m_p1;
   CPoint<T> m_p2;
};

typedef CRect<int> CRectI;
typedef CRect<float> CRectF;
typedef CRect<double> CRectD;
typedef CRect<unsigned int> CRectU;

#include <iostream>
template<typename T>
CRect<T>::CRect(T x, T y, T width, T height) 
{
   m_p1.m_x = x;
   m_p1.m_y = y;
   m_p2.m_x = x+width;
   m_p2.m_y = y+height;
   
   normalize();
}

template<typename T>
CRect<T>::CRect(const CPoint<T> &p1, const CPoint<T> &p2)
{
   m_p1 = p1;
   m_p2 = p2;
   
   normalize();
}

template<typename T>
void CRect<T>::setPosition(T x, T y)
{
   T w = getWidth();
   T h = getHeight();
   
   m_p1.m_x = x;
   m_p1.m_y = y;
   m_p2.m_x = (x + w);
   m_p2.m_y = (y + h);
}

template<typename T>
void CRect<T>::setPosition(const CPoint<T> &position)
{
   m_p1 += position;
   m_p2 += position;
}

template<typename T>
void CRect<T>::setSize(T width, T height)
{
   m_p2.m_x = m_p1.m_x+width;
   m_p2.m_y = m_p2.m_y+height;
}

template<typename T>
void CRect<T>::translate(T dx, T dy)
{
   m_p1.m_x += dx;
   m_p1.m_y += dy;
   m_p2.m_x += dx;
   m_p2.m_y += dy;
}

template<typename T>
void CRect<T>::translate(const CPoint<T> &point)
{
   translate(point.getX(), point.getY());
}

template<typename T>
bool CRect<T>::intersects(const CRect<T> &rect) const
{
   if( (m_p2.m_x <= rect.m_p1.m_x) || (m_p1.m_x >= rect.m_p2.m_x) ||
       (m_p2.m_y <= rect.m_p1.m_y) || (m_p1.m_y >= rect.m_p2.m_y) )
   {
      return false;
   }
   else
   {
      return true;
   }
}
#include <logging.h>
template<typename T>
CRect<T> CRect<T>::intersection(const CRect<T> &rect) const
{
   CRect<T> interRect;
   
   if(!intersects(rect))
   {
      return interRect;
   }
   
   interRect = *this;
   if(rect.m_p1.m_x > interRect.m_p1.m_x)
   {
      interRect.m_p1.m_x = rect.m_p1.m_x;
   }
   if(rect.m_p1.m_y > interRect.m_p1.m_y)
   {
      interRect.m_p1.m_y = rect.m_p1.m_y;
   }
   if(rect.m_p2.m_x < interRect.m_p2.m_x)
   {
      interRect.m_p2.m_x = rect.m_p2.m_x;
   }
   if(rect.m_p2.m_y < interRect.m_p2.m_y)
   {
      interRect.m_p2.m_y = rect.m_p2.m_y;
   }
   
   interRect.normalize();
   
   return interRect;
}

template<typename T>
void CRect<T>::join(const CRect<T> &rect)
{
   if(rect.m_p1.m_x < m_p1.m_x)
   {
      m_p1.m_x = rect.m_p1.m_x;
   }
   if(rect.m_p1.m_y < m_p1.m_y)
   {
      m_p1.m_y = rect.m_p1.m_y;
   }
   if(rect.m_p2.m_x > m_p2.m_x)
   {
      m_p2.m_x = rect.m_p2.m_x;
   }
   if(rect.m_p2.m_y > m_p2.m_y)
   {
      m_p2.m_y = rect.m_p2.m_y;
   }
}

template<typename T>
void CRect<T>::operator+=(const CRect<T> &rect)
{
   join(rect);
}

template<typename T>
bool CRect<T>::operator==(const CRect<T> &rect)
{
   if(rect.m_p1.m_x == m_p1.m_x &&
      rect.m_p1.m_y == m_p1.m_y &&
      rect.m_p2.m_x == m_p2.m_x &&
      rect.m_p2.m_y == m_p2.m_y)
   {
      return true;
   }
   
   return false;
}

template<typename T>
CPoint<T> CRect<T>::getPosition() const
{
   return m_p1;
}

template<typename T>
inline T CRect<T>::getWidth() const
{
   return (m_p2.m_x - m_p1.m_x);
}

template<typename T>
inline T CRect<T>::getHeight() const
{
   return (m_p2.m_y - m_p1.m_y);
}

template<typename T>
void CRect<T>::normalize()
{
   if(m_p2.m_x < m_p1.m_x)
   {
      T x = m_p2.m_x;
      m_p2.m_x = m_p1.m_x;
      m_p1.m_x = x;
   }
   
   if(m_p2.m_y < m_p1.m_y)
   {
      T y = m_p2.m_y;
      m_p2.m_y = m_p1.m_y;
      m_p1.m_y = y;
   }
}

#endif // CRECT_H
