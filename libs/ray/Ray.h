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
      for (int i = 0; i < 3; i++){
        this->directionInv[i] = 1/this->direction[i];
      }
      this->refract = 1.0f;
    }

    Ray(Vector3 origin, Vector3 direction, float refract){
      this->origin  = origin;
      this->direction = direction.normalize();
      for (int i = 0; i < 3; i++){
        this->directionInv[i] = 1/this->direction[i];
      }
      this->refract = refract;
    }

    void setDirection(Vector3 direction){
      this->direction = direction;
      for (int i = 0; i < 3; i++){
        this->directionInv[i] = 1/direction[i];
      }
    }

    Vector3 getDirection(){
      return this->direction;
    }

    Vector3 getDirectionInv(){
      return this->directionInv;
    }

    void setOrigin(Vector3 origin){
      this->origin = origin;
    }

    Vector3 getOrigin(){
      return this->origin;
    }

    float getRefract(){
      return this->refract;
    }

    void setRefract(float refract){
      this->refract = refract;
    }

  private:
    Vector3 direction;
    Vector3 directionInv;
    Vector3 origin;
    float refract;
};

#endif
