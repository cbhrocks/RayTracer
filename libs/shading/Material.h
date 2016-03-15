#ifndef __MATERIAL
#define __MATERIAL

#include "../vector/GenVector.h"

class Material{
  public:
    Material(){
      this->ambientCoefficient = Vector3(150.0f, 150.0f, 150.0f);
    }

    //all coefficients apply to a color
    Material(Vector3 ambientCoefficient, Vector3 specularCoefficient, Vector3 diffuseCoefficient, float shine){
      this->ambientCoefficient = ambientCoefficient.normalize();
      this->specularCoefficient = specularCoefficient.normalize();
      this->diffuseCoefficient = diffuseCoefficient.normalize();
      this->shine = shine;
    }

    Vector3 getAmbientCoefficient(){
      return this->ambientCoefficient;
    }

    Vector3 getSpecularCoefficient(){
      return this->specularCoefficient;
    }

    Vector3 getDiffuseCoefficient(){
      return this->diffuseCoefficient;
    }

  private:
    Vector3 ambientCoefficient;
    Vector3 specularCoefficient;
    Vector3 diffuseCoefficient;
    float shine;
};

#endif

