#ifndef __TRIANGLE
#define __TRIANGLE

#include "Primitive.h"
#include <math.h>

class Triangle : public Primitive {
  public:
    Triangle() : Primitive(){
      this->normal = (this->v1-this->v3).cross(this->v2-this->v3).normalize();
    }

    Triangle(Vector3 v1, Vector3 v2, Vector3 v3, Shader* shader, Material* material) 
      : Primitive(v1, v2, v3, shader, material){
        this->normal = (v2-v1).cross(v3-v1).normalize();
      }

    virtual HitPoint getHitPoint(Ray ray){
      Vector3 centerOfTriangle = (v1 + v2 + v3)/3;
      float t = ((centerOfTriangle - ray.getOrigin()).dot(this->normal)) /
        (ray.getDirection().dot(this->normal));
      Vector3 hitLoc = ray.getOrigin() + ray.getDirection() * t;

      if ((this->v2 - this->v1).cross(hitLoc - this->v1).dot(this->normal) > 0 &&
          (this->v3 - this->v2).cross(hitLoc - this->v2).dot(this->normal) > 0 &&
          (this->v1 - this->v3).cross(hitLoc - this->v3).dot(this->normal) > 0){
        return HitPoint(t, this->normal, hitLoc, this->material);
      }
      //if (pointInTriangle(v1, v2, v3, hitLoc)){
      ////printf("found point in triangle for: \n");
      ////hitLoc.print();
      ////v1.print();
      ////v2.print();
      ////v3.print();
      //return HitPoint(t, this->normal, hitLoc, this->material, this->shader);
      //}
      else {
        return HitPoint();
      }
    }

  private:
    Vector3 normal;

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
