#ifndef __POINTLIGHT
#define __POINTLIGHT

#include "../vector/GenVector.h"
#include "Light.h"

class PointLight: public Light{
  public:
    PointLight() : Light(){}

    PointLight(float intensity){
      this->intensity = intensity;
    }

    virtual Vector3 calculateShading(Material m){
      //Vector3 direction = 
      //return this->intensity * m.getDiffuseCoefficient() * max(0, m.getNormal().dot(;
    }

  private:          
    float intensity;  
};

#endif

