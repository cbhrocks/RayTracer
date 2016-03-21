#ifndef __DIRECTIONALLIGHT
#define __DIRECTIONALLIGHT

#include "../vector/GenVector.h"
#include "Material.h"

class DirectionalLight : public Light {
  public:
    DirectionalLight() : Light(){
      this->direction = Vector3(-1.0f, 1.0f, 1.0f).normalize();
    }

    DirectionalLight(Material* material) 
      : Light(material){
      this->direction = Vector3(-1.0f, 1.0f, 1.0f).normalize();
    }

    DirectionalLight(
        Material* material,
        Vector3 direction) 
      : Light(material){
      this->direction = direction.normalize();
    }

    virtual Vector3 getDirection(Vector3 hitLoc){
      return this->direction;
    }

  private:
    Vector3 direction;
};

#endif
