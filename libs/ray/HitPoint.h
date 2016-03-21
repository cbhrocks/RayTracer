#ifndef __HITPOINT
#define __HITPOINT

#include "../vector/GenVector.h"
#include "../shading/Material.h"

class HitPoint{
  public:
    HitPoint(){
      this->normal = Vector3(0,0,0);
      this->t = -1;
    }

    HitPoint(float t, Vector3 normal, Vector3 location){
      this->normal = normal.normalize();
      this->location = location + (normal * .001);
      this->t = t;
    }

    HitPoint(float t, Vector3 normal, Vector3 location, Material *material){
      this->normal = normal.normalize();
      this->location = location + (normal * .001);
      this->t = t;
      this->material = material;
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

  private:
    Vector3 normal;
    Vector3 location;
    float t;
    Material *material;
};

#endif
