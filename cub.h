// cub.h
#ifndef CLASS_CUB
#define CLASS_CUB

#include "material.h"
#include "shared_concepts.h"

class cub : public material
{
 private:
  struct_color color;
  int size;
  
 public:
  void setColor(struct_color color_);
  cub();
  ~cub();
  struct_color getColor();
  int getSize();
};

#endif
