#ifndef __PRIMITIVE
#define __PRIMITIVE

#include "../vector/GenVector.h"
#include "../ray/Ray.h"
#include "../ray/HitPoint.h"
#include "../shading/Shader.h"
#include "../shading/Material.h"

class Shader;

class Primitive {
  public:
    Primitive(){
      this->v1 = Vector3(0,0,0);
      this->v2 = Vector3(0,0,0);
      this->v3 = Vector3(0,0,0);
    }

    Primitive(Vector3 v1, Vector3 v2, Vector3 v3, Shader* shader, Material *material){
      this->v1 = v1;
      this->v2 = v2;
      this->v3 = v3;
      this->shader = shader;
      this->material = material;
    }

    void setShader(Shader *shader){
      this->shader = shader;
    }

    Shader* getShader(){
      return this->shader;
    }

    void setMaterial(Material *material){
      this->material = material;
    }

    Material* getMaterial(){
      return this->material;
    }

    virtual HitPoint getHitPoint(Ray r){
      return HitPoint();
    }

  protected:
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;
    Shader *shader;
    Material *material;
};

#endif
