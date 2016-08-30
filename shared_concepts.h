// shared_concepts.h

#ifndef SHARED_CONCEPTS
#define SHARED_CONCEPTS

struct struct_coord_2d
{
  int x;
  int y;
};

struct struct_coord_3d
{
  int x;
  int y;
  int z;
};

typedef unsigned char BYTE;

struct struct_color
{
  BYTE red;
  BYTE green;
  BYTE blue;
  BYTE transparent;
};

#endif
