#ifndef __POINTLIGHT
#define __POINTLIGHT

#include "../vector/GenVector.h"
#include "Light.h"

class PointLight: public Light{
  public:
    PointLight() : Light(){
    }

    PointLight(Vector3 location, Material* material)
      : Light(location, material){
        this->constantAttenuation = 1.0;
        this->linearAttenuation = 0;
        this->exponentialAttenuation = 0;
      }

    PointLight(
        Vector3 location,
        Material* material,
        float constantAttenuation, 
        float linearAttenuation, 
        float exponentialAttenuation
        )
      : Light(location, material){
        this->constantAttenuation = constantAttenuation;
        this->linearAttenuation = linearAttenuation;
        this->exponentialAttenuation = exponentialAttenuation;
      }

    virtual Vector3 getAmbientIntensity(float distance){
      return this->material->getAmbientCoefficient()*getAttenuation(distance);
    }

    virtual Vector3 getSpecularIntensity(float distance){
      return this->material->getSpecularCoefficient()*getAttenuation(distance);
    }

    virtual Vector3 getDiffuseIntensity(float distance){
      return this->material->getDiffuseCoefficient()*getAttenuation(distance);
    }

    virtual Vector3 getDirection(Vector3 hitLoc){
      return (hitLoc - this->location).normalize();
      //return (this->location - hitLoc).normalize();
    }

  private:
    float constantAttenuation;
    float linearAttenuation;
    float exponentialAttenuation;

    float getAttenuation(float distance){
      return 1/(constantAttenuation + 
          linearAttenuation * distance + 
          exponentialAttenuation * (distance * distance));
    }
};

#endif

