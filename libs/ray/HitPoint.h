#ifndef __HITPOINT
#define __HITPOINT

#include "../vector/GenVector.h"

class HitPoint{
  public:
    HitPoint(Vector3 normal, double t){
      this->normal = normal;
      this->t = t;
    }

  private:
    Vector3 normal;
    double t;
};

#endif
