#ifndef __PRIMITIVE
#define __PRIMITIVE

#include "../vector/GenVector.h"
#include "../ray/Ray.h"
#include "../ray/HitPoint.h"

class Primitive {
  public:
    Primitive(){
      this->location = Vector3(0,0,0);
    }

    Primitive(Vector3 loc, Vector3 direction, Vector3 up){
      this->location = loc;
      this->direction = direction;
      this->up = up;
    }

    virtual HitPoint getHitPoint(Ray r){
      return HitPoint();
    }

  protected:
    Vector3 location;
    Vector3 direction;
    Vector3 up;
};

#endif
