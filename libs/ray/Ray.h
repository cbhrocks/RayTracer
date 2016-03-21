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
    }

    Vector3 getDirection(){
      return this->direction;
    }

    Vector3 getOrigin(){
      return this->origin;
    }

  private:
    Vector3 direction;
    Vector3 origin;
};

#endif
