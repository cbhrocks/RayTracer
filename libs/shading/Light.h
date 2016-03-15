#ifndef __LIGHT
#define __LIGHT

#include "../vector/GenVector.h"
#include "Material.h"

class Light {
  public:
    Light(){
      this->intensity = 10;
    }

    Light(float intensity){
      this->intensity = intensity;
    }

    virtual Vector3 calculateShading(Material m){
      return Vector3(0,0,0);
    }

  protected:
    float intensity;

    float max(float a, float b){
      if (a > b){
        return a;
      }
      else {
        return b;
      }
    }
};

#endif
