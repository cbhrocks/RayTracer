#ifndef __HITPOINT
#define __HITPOINT

#include "../vector/GenVector.h"
#include "../shading/Shader.h"
#include "../shading/Material.h"

class Shader;

class HitPoint{
  public:
    HitPoint(){
      this->normal = Vector3(0,0,0);
      this->t = -1;
      this->ray = 0;
    }

    HitPoint(float t, Vector3 normal, Vector3 location){
      this->normal = normal.normalize();
      this->location = location;// + (normal * .000000001);
      this->t = t;
      this->ray = 0;
    }

    HitPoint(float t, Vector3 normal, Vector3 location, Material *material, Shader* shader, Ray *ray){
      this->normal = normal.normalize();
      this->location = location;// + (normal * .000000001);
      this->t = t;
      this->material = material;
      this->shader = shader;
      if (ray == 0){
        printf("NULL RAY DETECTED\n");
      }
      this->ray = ray;
    }

    float getT(){
      return this->t;
    }

    Vector3 getNormal(){
      return this->normal;
    }

    Material* getMaterial(){
      return this->material;
    }

    void setMaterial(Material* m){
      this->material = m;
    }

    Vector3 getLocation(){
      return this->location;
    }

    Ray* getRay(){
      return this->ray;
    }

    void setShader(Shader* s){
      this->shader = s;
    }

    Shader* getShader(){
      return this->shader;
    }

  private:
    Vector3 normal;
    Vector3 location;
    float t;
    Material *material;
    Shader* shader;
    Ray *ray;
};

#endif
