#ifndef __TRIANGLE
#define __TRIANGLE

#include "Primitive.h"
#include <math.h>

class Triangle : public Primitive {
  public:
    Triangle() : Primitive(){
    }

    Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Shader* shader, Material* material) 
      : Primitive(v1, v2, v3, shader, material){
        //this->normal = (v2-v1).cross(v3-v1).normalize();
        this->center = (v1 + v2 + v3)/3;
      }

    virtual HitPoint getHitPoint(Ray* ray){
      //Vector3 normal = (this->v1 - this->v2).cross(this->v2 - this->v3); 
      Vector3 normal = ((v2-v1).cross(v3-v1)).normalize();
      float t = ((this->center - ray->getOrigin()).dot(normal)) /
        (ray->getDirection().dot(normal));
      Vector3 hitLoc = ray->getOrigin() + ray->getDirection() * t;

      if ((this->v2 - this->v1).cross(hitLoc - this->v1).dot(normal) > 0 &&
          (this->v3 - this->v2).cross(hitLoc - this->v2).dot(normal) > 0 &&
          (this->v1 - this->v3).cross(hitLoc - this->v3).dot(normal) > 0){
        return HitPoint(t, normal, hitLoc, this->material, this->shader, ray);
      }
      else {
        return HitPoint();
      }
    }

    virtual Vector3 getCenter(){
      return this->center;
    }

    virtual Vector3 getMin(){
      Vector3 min = v1;
      for (int i = 0; i < 3; i++){
        if (v2[i] < min[i]){
          min[i] = v2[i];
        }
        if (v3[i] < min[i]){
          min[i] = v3[i];
        }
      }
      return min;
    }

    virtual Vector3 getMax(){
      Vector3 max = v1;
      for (int i = 0; i < 3; i++){
        if (v2[i] > max[i]){
          max[i] = v2[i];
        }
        if (v3[i] > max[i]){
          max[i] = v3[i];
        }
      }
      return max;
    }

    virtual char* getName(){
      return "triangle";
    }

  private:
    Vector3 center;

    bool pointInTriangle(Vector3 A, Vector3 B, Vector3 C, Vector3 P){
      Vector3 u = B - A;
      Vector3 v = C - A;
      Vector3 w = P - A;

      Vector3 vXw = v.cross(w);
      Vector3 vXu = v.cross(u);

      if (vXw.dot(vXu) < 0){
        return false;
      }

      Vector3 uXw = u.cross(w);
      Vector3 uXv = u.cross(v);

      if (uXw.dot(uXv) < 0){
        return false;
      }

      //printf("passed both those tests\n");

      float denom = uXv.length();
      float r = vXw.length()/denom;
      float t = uXw.length()/denom;

      if (r + t <= 1){
        return true;
      }

      return false;
    }
};

#endif
