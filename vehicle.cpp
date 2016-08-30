//vehicle.cpp
#include "vehicle.h"
#include <stdio.h>
#include <string>

vehicle::vehicle(const char * brand_)
{
  printf("\nvehicle constructor");
  this->brand.assign(brand_);
  printf("\n brand: %s", this->brand.data());
}

vehicle::~vehicle()
{
  printf("\nvehicle destructor");
}

void vehicle::setColor(const char* color)
{
  this->color.assign(color);
  printf("\n color-> %s", this->color.data());
}
