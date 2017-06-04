#ifndef CPIXMAP_H
   #define CPIXMAP_H

class CPixmap
{
public:
   virtual ~CPixmap(){}
private:
   CPixmap(void *surface){}
   
   friend class IPaintDevice;
};

#endif // CPIXMAP
