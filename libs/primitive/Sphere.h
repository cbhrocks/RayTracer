#ifndef __SPHERE
#define __SPHERE

#include "Primitive.h"
#include <math.h>

class Sphere: public Primitive {
  public:
    Sphere() : Primitive(){
      this->radius = 1.0f;
    }

    /* Sphere class
     * 
     * v1 = loc
     * v2 = upVector
     * v3 = equator normal / radius
     */
    Sphere(Vector3 loc, Vector3 up, Vector3 direction, Shader* shader, Material* material)
      : Primitive(loc, up, direction, shader, material){
        this->radius = up.length();
        printf("radius: %f\n", this->radius);
      }

    virtual HitPoint getHitPoint(Ray ray){
      float a = ray.getDirection().dot(ray.getDirection());
      float b = ray.getDirection().dot((ray.getOrigin() - this->v1));
      float c = (ray.getOrigin() - this->v1).dot(ray.getOrigin() - this->v1) - pow(this->radius, 2);
      float discriminant = pow(b, 2) - a * c;
      if (discriminant < 0){
        return HitPoint();
      } 
      else {
        //float t = min((-b - sqrt(discriminant)),(-b + sqrt(discriminant)))/a;
        float t = (-b - sqrt(discriminant))/a;
        Vector3 normal;
        Vector3 hitLoc;
        if (t < 0){
          t = (-b + sqrt(discriminant))/a;
          hitLoc = ray.getOrigin() + ray.getDirection()*t;
          normal = (this->v1 - hitLoc).normalize();
        }
        else {
          hitLoc = ray.getOrigin() + ray.getDirection()*t;
          normal = (hitLoc - this->v1).normalize();
        }
        return HitPoint(t, normal, hitLoc, this->material, &ray);
      }
    }

  private:
    float radius;

    float min(float x, float y){
      if (x < y)
        return x;
      else
        return y;
    }
};

#endif
