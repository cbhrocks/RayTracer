#ifndef __MATERIAL
#define __MATERIAL

#include "../vector/GenVector.h"

class Material{
  public:
    Material(){
      this->name = "default";
      this->ambientCoefficient = Vector3(0.2f, 0.2f, 0.2f);
      this->diffuseCoefficient = Vector3(0.4f, 0.4f, 0.4f);
      this->specularCoefficient = Vector3(0.8f, 0.8f, 0.8f);
      this->reflect = 0;
      this->translucent = 0;
      this->glossy = 0;
      this->shine = 100;
      this->refract = 0;
      this->texture = "";
    }

    Material(
        Vector3 ambientCoefficient, 
        Vector3 diffuseCoefficient,
        Vector3 specularCoefficient
        ){
      this->name = "light";
      this->ambientCoefficient = ambientCoefficient;
      this->diffuseCoefficient = diffuseCoefficient;
      this->specularCoefficient = specularCoefficient;
    }

    //all coefficients apply to a color
    Material(
        char* name,
        Vector3 ambientCoefficient, 
        Vector3 diffuseCoefficient, 
        Vector3 specularCoefficient, 
        float reflect,
        float translucent,
        int glossy,
        int shine,
        float refract,
        char* texture
        ){
      this->name = name;
      this->ambientCoefficient = ambientCoefficient;
      this->diffuseCoefficient = diffuseCoefficient;
      this->specularCoefficient = specularCoefficient;
      this->reflect = reflect;
      this->translucent = translucent;
      this->glossy = glossy;
      this->shine = shine;
      this->refract = refract;
      this->texture = texture;
    }

    Vector3 getAmbientCoefficient(){
      return this->ambientCoefficient;
    }

    Vector3 getDiffuseCoefficient(){
      return this->diffuseCoefficient;
    }

    Vector3 getSpecularCoefficient(){
      return this->specularCoefficient;
    }

    int getShine(){
      return this->shine;
    }

    float getReflect(){
      return this->reflect;
    }

    float getTranslucent(){
      return this->translucent;
    }

    float getRefract(){
      return this->refract;
    }

    char* getName(){
      return this->name;
    }

  private:
    char* name;
    Vector3 ambientCoefficient;
    Vector3 diffuseCoefficient;
    Vector3 specularCoefficient;
    float reflect;
    float translucent;
    int glossy;
    int shine;
    float refract;
    char* texture;
};

#endif

