// cub.cpp
#include <stdio.h>
#include "cub.h"
#include "material.h"

void cub::setColor(struct_color color_)
{
  printf("\n set cub color");
  this->color.blue = color_.blue;
  this->color.green = color_.green;
  this->color.red = color_.red;
  this->color.transparent = color_.transparent;

}

cub::cub()
{
  printf("\ncub constructor");
  this->size = 0;
}

cub::~cub()
{
  printf("\ncub destructor");
}

struct_color cub::getColor()
{
  return this->color;
}

int cub::getSize()
{
  return this->size;
}
