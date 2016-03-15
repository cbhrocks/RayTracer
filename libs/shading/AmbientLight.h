#ifndef __AMBIENTLIGHT
#define __AMBIENTLIGHT

#include "Light.h"
//#include "../vector/GenVector.h"
//#include "Material.h"

class AmbientLight: public Light {
  public:
    AmbientLight() : Light(){}

    AmbientLight(float intensity){
      this->intensity = intensity;
    }

    virtual Vector3 calculateShading(Material m){
      return this->intensity * m.getAmbientCoefficient();
    }

  private:
};

#endif

