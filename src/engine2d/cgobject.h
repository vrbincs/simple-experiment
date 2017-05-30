#ifndef CGOBJECT_H
   #define CGOBJECT_H

#include <engine2d.h>
#include <cscene.h>
#include <crect.h>

class CDrawingTool;
class CGObjectPriv;
class CEvent;

/**
 * \class The base class that represents a graphical item. It allows to
 * build a tree of items in child parent manner. It implements the
 * composite pattern.
 */
class CGObject
{
public:
   /**
    * \brief constructor
    */
   CGObject(CGObject *parent = NULL);
   
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
   
   /**
    * \brief return a pointer to the parent object;
    * \return return a pointer to the parent object;
    */
   CGObject *getParent() const;
protected:
   /**
    * \brief This is the exciting part of the object where all painting
    * is carried out. Make sure that drawing is confined inside the 
    * region returned by objectRegion()
    */
   virtual void repaint(CDrawingTool *drawingTool) = 0;
   
   /**
    * \brief This tells the scene that this object needs to be
    * re-painted. This will add the object to the list of object that
    * needs to be repained only if it is in the current scene view.
    */
   void update();
   
   /**
    * \brief Get the pointer to the scene.
    */
   CScene *getScene() const;
   
   virtual void onEvent(CEvent &event);
private:
   CGObject *m_parent;
   CGObjectPriv *m_cgobjectPriv;
   
   friend class CScene;
   /**
    * \brief Copy constructor is disable as we do not want an object to be part
    * two different composite objects
    */
   CGObject(const CGObject &copyObj);
   
   void setScene(CScene *scene);
};

#endif // CGOBJECT
