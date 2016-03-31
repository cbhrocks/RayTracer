#ifndef __PRIMITIVE
#define __PRIMITIVE

#include "Prmimitive.h"

// Axis Aligned Bounding Box
class AABB : Primitive {
  public:
    AABB() : Primitive(){}

    //v1 = min
    //v2 = max
    //v3 = center
    AABB(Vector3 min, Vector3 max) : Primitive(min, max){
      this->v3 = (min + max)*.5
    }

    //using the direction of the ray get the closest sides of the bb and determine whether the ray hits them or not.
    //it would be good to calculat ethe division in the ray.
    virtual HitPoint getHitPoint(Ray r){
      Vector3 rayDirection = r.getDirection();
      // ray coming from right side.
      if (rayDirection[0] < 0){
        //ray coming from above
        if (rayDirection[1] < 0){
          //ray coming from in front
          if (rayDirection[2] < 0){
            checkSides(1, r, );
          }
          //ray coming from behind
          else{
            checkSides(2, r);
          }
        }
        //ray coming from below
        else{
          //ray coming from in front
          if (rayDirection[2] < 0){
            checkSides(3, r);
          }
          //ray coming from behind
          else{
            checkSides(4, r);
          }
        }
      }
      // ray coming from left side.
      else{
        //ray coming from above
        if (rayDirection[1] < 0){
          //ray coming from in front
          if (rayDirection[2] < 0){
            checkSides(5, r);
          }
          //ray coming from behind
          else{
            checkSides(6, r);
          }
        }
        //ray coming from below
        else{
          //ray coming from in front
          if (rayDirection[2] < 0){
            checkSides(7, r);
          }
          //ray coming from behind
          else{
            checkSides(8, r);
          }
        }
      }
    }

  private:
    //check sides based on the closest corner to the ray origin.
    //1:right top front
    //2:right top back
    //3:right bottom front
    //4:right bottom back
    //5:left top front
    //6:left top back
    //7:left bottom front
    //8:left bottom back
    HitPoint checkSides(int corner, Ray r){
      float t;
      int directionChance = r.maxMagnitudeComponent();
      if (corner == 1){
        if (directionChance == 0){
          t = (v2[0] - r.getOrigin()[0])/r.getDirection();
          pos = t*r.getDirection();
          if (pos[2] > max[2] && pos[2] > (max[2] - min[2]) && pos[1] < max[1] && pos[1] > (max[1] - min[1])){
            return HitPoint(t, Vector3(1,0,0), pos, this->material, &r);
          }
          else if (r.getDirection()[1] > r.getDirection()[2]){
            if (pos[2] > max[2] && pos[2] > (max[2] - min[2]) && pos[0] < max[0] && pos[0] > (max[0] - min[0])){
              return HitPoint(t, Vector3(1,0,0), pos, this->material, &r);
            }
            
        }
      }
      if (corner == 2){
      }
      if (corner == 3){
      }
      if (corner == 4){
      }
      if (corner == 5){
      }
      if (corner == 6){
      }
      if (corner == 7){
      }
      else{
      }
    }

#endif
