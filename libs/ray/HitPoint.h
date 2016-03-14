#ifndef __HITPOINT
#define __HITPOINT

#include "../vector/GenVector.h"

class HitPoint{
  public:
    HitPoint(){
      this->normal = Vector3(0,0,0);
      this->t = -1;
    }

    HitPoint(double t, Vector3 normal){
      this->normal = normal;
      this->t = t;
    }

    float getT(){
      return this->t;
    }

    Vector3 getNormal(){
      return this->normal;
    }

  private:
    Vector3 normal;
    double t;
};

#endif
