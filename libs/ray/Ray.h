#ifndef __RAY
#define __RAY

#include "../vector/GenVector.h"

class Ray
{
  public:
    Ray(){
    }

    Ray(Vector3 origin, Vector3 direction){
      this->origin  = origin;
      this->direction = direction.normalize();
      this->refract = 1.0f;
    }

    Ray(Vector3 origin, Vector3 direction, float refract){
      this->origin  = origin;
      this->direction = direction.normalize();
      this->refract = refract;
    }

    Vector3 getDirection(){
      return this->direction;
    }

    Vector3 getOrigin(){
      return this->origin;
    }

    float getRefract(){
      return this->refract;
    }

  private:
    Vector3 direction;
    Vector3 origin;
    float refract;
};

#endif
