#ifndef __SPHERE
#define __SPHERE

#include "Primitive.h"
#include "../vector/GenVector.h"
#include "../ray/Ray.h"
#include "../ray/HitPoint.h"
#include <math.h>

class Sphere: public Primitive {
  public:
    Sphere() : Primitive(){}

    Sphere(Vector3 loc, Vector3 up, Vector3 direction) : Primitive(loc, up, direction){
      this->radius = this->up.length();
    }

    virtual HitPoint getHitPoint(Ray ray){
      float a = ray.getDirection().dot(ray.getDirection());
      float b = ray.getDirection().dot((ray.getOrigin() - this->location));
      float c = (ray.getOrigin() - this->location).dot(ray.getOrigin() - this->location) - pow(this->radius, 2);
      float discriminant = pow(b, 2) - a * c;
      if (discriminant < 0){
        //return nullptr;
        return HitPoint();
      } else {
        float t = (-b + sqrt(discriminant))/a;
        Vector3 normal = (this->location - (ray.getOrigin() + ray.getDirection()*t)).normalize();
        //Vector3 normal = Vector3(0,0,0);
        //HitPoint hp = HitPoint(Vector3(0,0,0), t);
        return HitPoint(t, normal);
      }
    }

  private:
    float radius;
};

#endif
