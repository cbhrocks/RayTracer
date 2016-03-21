#ifndef __CAMERA
#define __CAMERA

#include "../vector/GenVector.h"

class Camera {
  public:
    Camera(){
      this->up = Vector3(0, 1, 0);
      this->location = Vector3(0,1,2);
      this->direction = Vector3(0,0,-1);
      this->w = -this->direction;
      this->u = (up.cross(this->w)).normalize();
      this->v = (this->w.cross(this->u)).normalize();
    }

    Camera(Vector3 location, Vector3 direction, Vector3 up){
      this->location = location;
      this->up = up.normalize();
      this->direction = direction.normalize();
      this->w = -this->direction/this->direction.length();
      this->u = ((up.cross(this->w))/(up.cross(this->w)).length()).normalize();
      this->v = (this->w.cross(this->u)).normalize();
    }

    Vector3 getLocation(){
      return this->location;
    }

    void updatePosition(Vector3 e){
      this->location = e;
    }

    Vector3 getDirection(){
      return this->direction;
    }

    Vector3 getW(){
      return this->w;
    }

    Vector3 getU(){
      return this->u;
    }

    Vector3 getV(){
      return this->v;
    }

  private:
    Vector3 w;
    Vector3 u;
    Vector3 v;
    Vector3 up;
    Vector3 direction;
    Vector3 location;
};

#endif
