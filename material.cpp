// material.cpp
#include <stdio.h>
#include "material.h"
#include "shared_concepts.h"

void material::setColor(struct_color color_)
{
  printf("\n set material color");
  this->color.blue = color_.blue;
  this->color.green = color_.green;
  this->color.red = color_.red;
  this->color.transparent = color_.transparent;
}

material::material()
{
  printf("\nmaterial constructor");
  this->size = 0;
}

material::~material()
{
  printf("\nmaterial destructor");
}
  
struct_color material::getColor()
{
  return this->color;
}

void material::setSize(int size_)
{
  printf("\n set material size: %d", size_);
  this->size = size_;
}

int material::getSize()
{
  return this->size;
}
