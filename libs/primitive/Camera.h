#ifndef __CAMERA
#define __CAMERA

#include "../vector/GenVector.h"

class Camera {
  public:
    Camera(){
      this->w = Vector3(0,0,1);
      this->u = Vector3(1,0,0);
      this->v = Vector3(0,1,0);
      this->up = Vector3(0, 1, 0);
      this->location = Vector3(0,0,0);
      this->direction = -this->w;
    }

    Camera(Vector3 location, Vector3 direction, Vector3 up){
      this->location = location;
      this->up = up.normalize();
      this->direction = direction.normalize();
      this->w = -direction;
      this->u = up.cross(this->w);
      this->v = this->w.cross(this->u);
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
