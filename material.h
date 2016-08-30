// material.h

#include "shared_concepts.h"

#ifndef CLASS_MATERIAL
#define CLASS_MATERIAL

class material
{
 private:
  struct_color color;
  int size;
  
 public:
  virtual void setColor(struct_color color_);
  virtual void setSize(int size_);
  virtual int getSize();

  struct_color getColor();

  material();
  virtual ~material();
  
};

#endif
