#ifndef CGOBJECT_H
   #define CGOBJECT_H

#include <engine2d.h>
#include <crect.h>

class CDrawingTool;
class CGObjectPriv;

/**
 * \class The base class that represents a graphical item. It allows to
 * build a tree of items in child parent manner. It implements the
 * composite pattern.
 */
class CGObject
{
   /**
    * \brief constructor
    */
   CGObject(CGObject *parent);
   
   /**
    * \brief virtual destructor
    */
   virtual ~CGObject();
   
   /**
    * \brief Every object has position and size. This is the essential
    * information for the optimizer to only updates certain parts of
    * the visible drawing region and not the entire one.
    */
   virtual CRectI objectRegion() const = 0;
   
   /**
    * \brief set parent
    * \return return true if the child was added successfully to the
    * parent; false, otherwise.
    */
   bool setParent(CGObject *parent);
protected:
   /**
    * \brief This is the exciting part of the object where all painting
    * is carried out. Make sure that drawing is confined inside the 
    * region returned by objectRegion()
    */
   virtual void repaint(CDrawingTool *drawingTool) = 0;
private:
   CGObject *m_parent;
   CGObjectPriv *m_cgobjectPriv;
   
   /**
    * \brief Copy constructor is disable as we do not want an object to be part
    * two different composite objects
    */
   CGObject(const CGObject &copyObj);
};

#endif // CGOBJECT
