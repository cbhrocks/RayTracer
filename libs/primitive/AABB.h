#ifndef __AABB
#define __AABB

#include "../vector/GenVector.h"

// Axis Aligned Bounding Box
class AABB{
  public:
    AABB(){}

    AABB(Vector3 minCorner, Vector3 maxCorner){
      this->minCorner = minCorner;
      this->maxCorner = maxCorner;
      //printf("minCorner: ");
      //minCorner.print();
      //printf("maxCorner: ");
      //maxCorner.print();
    }

    //using the direction of the ray get the closest sides of the bb and determine whether the ray hits them or not.
    //it would be good to calculat ethe division in the ray.
    bool checkIntersect(Ray* r){
      //printf("checking an intersection\n");
      float t1 = (this->minCorner[0] - r->getOrigin()[0])/r->getDirection()[0];
      float t2 = (this->maxCorner[0] - r->getOrigin()[0])/r->getDirection()[0];

      float tmin = min(t1, t2);
      float tmax = max(t1, t2);

      for (int i = 1; i < 3; i++){
          float t1 = (this->minCorner[i] - r->getOrigin()[i])/r->getDirection()[i];
          float t2 = (this->maxCorner[i] - r->getOrigin()[i])/r->getDirection()[i];

          tmin = max(tmin, min(t1, t2));
          tmax = min(tmax, max(t1, t2));
      }

      return tmax >= tmin;//max(tmin, 0.0);
    }

    Vector3 checkIntersectNormal(Ray* r){
      //printf("checking an intersection\n");
      float t1 = (this->minCorner[0] - r->getOrigin()[0])/r->getDirection()[0];
      float t2 = (this->maxCorner[0] - r->getOrigin()[0])/r->getDirection()[0];

      float tmin = min(t1, t2);
      float tmax = max(t1, t2);

      for (int i = 1; i < 3; i++){
          float t1 = (this->minCorner[i] - r->getOrigin()[i])/r->getDirection()[i];
          float t2 = (this->maxCorner[i] - r->getOrigin()[i])/r->getDirection()[i];

          tmin = max(tmin, min(t1, t2));
          tmax = min(tmax, max(t1, t2));
      }

      Vector3 normal = Vector3(0,0,0);

      for (int i = 0; i < 3; i++){
        //printf("minCorner[i]: %f\n", this->minCorner[i]);
        //printf("tmin: %f\n", tmin);
        if (tmin == (this->minCorner[i] - r->getOrigin()[i])/r->getDirection()[i]){
          normal[i] = 1;
        }
        else if (tmin == (this->maxCorner[i] - r->getOrigin()[i])/r->getDirection()[i]){
          normal[i] = 1;
        }
      }

      if (tmax >= tmin){
        return normal;
      }
      else{
        return Vector3(0,0,0);
      }
    }

  private:
    Vector3 minCorner;
    Vector3 maxCorner;

    float min(float x, float y){
      if (x < y){
        return x;
      }
      else{
        return y;
      }
    }

    float max(float x, float y){
      if (x > y){
        return x;
      }
      else{
        return y;
      }
    }
};

#endif
