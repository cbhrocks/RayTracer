#ifndef __PRIMITIVE
#define __PRIMITIVE

#include "../vector/GenVector.h"
#include "../ray/Ray.h"
#include "../ray/HitPoint.h"
#include "../shading/Shader.h"
#include "../shading/Material.h"

#include <utility>

class Shader;

class Primitive {
  public:
    Primitive(){
      this->v1 = Vector3(0,0,0);
      this->v2 = Vector3(0,0,0);
      this->v3 = Vector3(0,0,0);
    }

    Primitive(Vector3 v1, Vector3 v2, Vector3 v3 = Vector3(0,0,0)){
      this->v1 = v1;
      this->v2 = v2;
      this->v3 = v3;
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

    virtual HitPoint getHitPoint(Ray* r){
      return HitPoint();
    }

    virtual float getDistance(Ray* r){
      return -1.0f;
    }

    virtual Vector3 getNormal(){
      return Vector3(0,0,0);
    }

    virtual Vector3 getCenter(){
      return Vector3(0,0,0);
    }

    virtual Vector3 getMin(){
      return Vector3(0,0,0);
    }

    virtual Vector3 getMax(){
      return Vector3(0,0,0);
    }

    virtual char* getName(){
      return "primitive";
    }
  protected:
    Vector3 v1;
    Vector3 v2;
    Vector3 v3;
    Shader *shader;
    Material *material;
};

#endif
