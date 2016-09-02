#include <stdio.h>

class O {
public:
  virtual void name2() {
    printf("\n name2 O");
  }
};

class A {
public:
  virtual ~A() {};
  virtual void name() {
    printf("\n class A");
  }
  virtual void name2() {
    printf("\n name2 A");
  }
  void nameA() {
    printf("\n nameA");
  }
};

class B : A, O {
public:
  virtual void name() {
    printf("\n class B");
  }
  virtual void name2() {
    printf("\n name2 B");
  }
  void nameB() {
    printf("\n nameB");
  }
};

class C : A, O {
public:
  virtual void name() {
    printf("\n class C");
  }
  virtual void name2() {
    printf("\n name2 C");
  }
  void nameC() {
    printf("\n nameC");
  }
};

int main()
{
  A a;
  B b;
  C c;

  A *p[3];
  p[0] = &a;
  p[1] = (A*)&b;
  p[2] = (A*)&c;

  for (int i = 0; i < 3; i++)
    {
      p[i]->name();
      p[i]->name2();
    }

  printf("\nGoodBy!\n");
}
