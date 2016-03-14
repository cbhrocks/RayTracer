#ifndef __TRIANGLE
#define __TRIANGLE

#include "Primitive.h"
#include "../vector/GenVector.h"
#include "../ray/Ray.h"
#include "../ray/HitPoint.h"
#include <math.h>

class Triangle: public Primitive {
  public:
    Triangle() : Primitive(){}

    Triangle(Vector3 v1, Vector3 v2, Vector3 v3) {
      this->a = v1;
      this->b = v2;
      this->c = v3;
      this->normal = (a-c).cross(b-c);
    }

    virtual float getHitPoint(Ray ray){
      float t = (this->a - ray.getOrigin()).dot(this->normal) /
        ray.getDirection().dot(this->normal);
      Vector3 x = ray.getDirection() * t;
      //return t;
      if ((b-a).cross(x-a).dot(this->normal) > 0 &&
          (c-b).cross(x-b).dot(this->normal) > 0 &&
          (a-c).cross(x-c).dot(this->normal) > 0){
        return t;
      }
      else {
        return -1;
      }
    }

  private:
    Vector3 a;
    Vector3 b;
    Vector3 c;
    Vector3 normal;
};

#endif

