#ifndef __LIGHT
#define __LIGHT

#include "../vector/GenVector.h"
#include "Material.h"

class Light {
  public:
    Light(){
      this->location = Vector3(0,0,0);
    }

    Light(Material* material){
      this->location = Vector3(0,0,0);
      this->material = material;
    }

    Light(Vector3 location, Material* material){
      this->location = location;
      this->material = material;
    }

    virtual void setMaterial(Material* material){
      this->material = material;
    }

    virtual Vector3 getAmbientIntensity(float distance){
      return this->material->getAmbientCoefficient();
    }

    virtual Vector3 getSpecularIntensity(float distance){
      return this->material->getSpecularCoefficient();
    }

    virtual Vector3 getDiffuseIntensity(float distance){
      return this->material->getDiffuseCoefficient();
    }

    virtual Vector3 getDirection(Vector3 hitLoc){
      return Vector3(0,0,0);
    }

    virtual Vector3 getLocation(){
      return this->location;
    }

  protected:
    Vector3 location;
    Material* material;
};

#endif
