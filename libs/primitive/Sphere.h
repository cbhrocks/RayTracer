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
     * v1 = center
     * v2 = upVector
     * v3 = equator normal / radius
     */
    Sphere(Vector3 loc, Vector3 up, Vector3 direction, Shader* shader, Material* material)
      : Primitive(loc, up, direction, shader, material){
        this->radius = up.length();
        printf("radius: %f\n", this->radius);
      }

    virtual HitPoint getHitPoint(Ray *ray){
      float b = ray->getDirection().dot((ray->getOrigin() - this->v1));
      float c = (ray->getOrigin() - this->v1).dot(ray->getOrigin() - this->v1) - pow(this->radius, 2);
      float discriminant = pow(b, 2) - c;
      if (discriminant < 0){
        return HitPoint();
      } 
      else {
        float t;
        Vector3 normal;
        Vector3 hitLoc;
        if (ray->getOrigin().distance(this->v1) < this->radius){
          t = (-b + sqrt(discriminant));
          hitLoc = ray->getOrigin() + ray->getDirection()*t;
          normal = (this->v1 - hitLoc).normalize();
        }
        else {
          t = (-b - sqrt(discriminant));
          hitLoc = ray->getOrigin() + ray->getDirection()*t;
          normal = (hitLoc - this->v1).normalize();
        }
        return HitPoint(t, normal, this->material, this->shader, ray);
      }
    }

    virtual Vector3 getCenter(){
      return this->v1;
    }

    virtual Vector3 getMin(){
      Vector3 min = Vector3(v1[0] - radius, v1[1] - radius, v1[2] - radius);
      return min;
    }

    virtual Vector3 getMax(){
      Vector3 max = Vector3(v1[0] + radius, v1[1] + radius, v1[2] + radius);
      return max;
    }

    virtual char* getName(){
      return "sphere";
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
