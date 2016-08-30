// main.cpp
#include <stdio.h>
#include "vehicle.h"
#include "material.h"
#include "cub.h"

int main(int argc, char* argv[])
{
  material* m = new material();
  cub* c = new cub();
  cub* c2 = new cub();

  struct_color color;
  color.blue = 55;
  color.red = 44;
  color.green = 33;
  color.transparent = 0;

  m->setColor(color);
  c->material::setColor(color);

  color.transparent = 1;  
  c->setColor(color);

  color.transparent = 2;  
  c2->setColor(color);

  printf("\n material color trasparent: %d", m->getColor().transparent);
  printf("\n cub  color trasparent: %d", c->getColor().transparent);
  printf("\n cub2 color trasparent: %d", c2->getColor().transparent);

  c->setSize(1);

  printf("\nmaterial size: %d", m->getSize());
  printf("\ncub size: %d", c->getSize());
  printf("\ncub2 size: %d", c2->getSize());
  printf("\ncub->material:: size: %d", c->material::getSize());

  delete m;
  delete c;
  delete c2;
  
  printf("\nGoodBy!\n");
  
}
